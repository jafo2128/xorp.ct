// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2003 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

#ident "$XORP: xorp/rtrmgr/main_rtrmgr.cc,v 1.18 2003/05/28 19:02:30 mjh Exp $"

#include <signal.h>

#include "rtrmgr_module.h"
#include "libxorp/xlog.h"
#include "libxorp/debug.h"
#include "libxorp/eventloop.hh"

#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>

#include "libxipc/sockutil.hh"
#include "libxipc/finder.hh"
#include "libxipc/finder_tcp_messenger.hh"
#include "libxipc/finder_xrl_target.hh"
#include "libxipc/permits.hh"
#include "libxipc/xrl_std_router.hh"

#include "template_tree_node.hh"
#include "template_commands.hh"
#include "template_tree.hh"
#include "master_conf_tree.hh"
#include "module_manager.hh"
#include "task.hh"
#include "userdb.hh"
#include "xrl_rtrmgr_interface.hh"
#include "randomness.hh"
#include "main_rtrmgr.hh"

//
// Defaults
//
static bool 	   default_do_exec 	       = true;
static const char* default_config_boot	       = "config.boot";
static const char* default_config_template_dir = "../etc/templates";
static const char* default_xrl_dir 	       = "../xrl/targets";

static bool running;

static void signalhandler(int) {
    running = false;
}

void
usage()
{
    fprintf(stderr,
	"usage: rtrmgr [-n] [-b config.boot] [-t cfg_dir] [-x xrl_dir]\n");
    fprintf(stderr, "options:\n");

    fprintf(stderr, 
	    "\t-n		do not execute XRLs		[ %s ]\n",
	    default_do_exec ? "false" : "true");

    fprintf(stderr, 
	    "\t-b config.boot	specify boot file 		[ %s ]\n",
	    default_config_boot);
	    
    fprintf(stderr, 
	    "\t-t cfg_dir	specify config directory	[ %s ]\n",
	    default_config_template_dir);

    fprintf(stderr, 
	    "\t-x xrl_dir	specify xrl directory		[ %s ]\n",
	    default_xrl_dir);

    exit(-1);
}


static bool
valid_interface(const IPv4& addr)
{
    uint32_t naddr = if_count();
    uint16_t any_up = 0;

    for (uint32_t n = 1; n <= naddr; n++) {
        string name;
        in_addr if_addr;
        uint16_t flags;

        if (if_probe(n, name, if_addr, flags) == false)
            continue;

        any_up |= (flags & IFF_UP);

        if (IPv4(if_addr) == addr && flags & IFF_UP) {
            return true;
        }
    }

    if (IPv4::ANY() == addr && any_up)
        return true;

    return false;
}

int
main(int argc, char* const argv[])
{
    int errcode = 0;

    //
    // Initialize and start xlog
    //
    xlog_init(argv[0], NULL);
    xlog_set_verbose(XLOG_VERBOSE_LOW);		// Least verbose messages
    // XXX: verbosity of the error messages temporary increased
    xlog_level_set_verbose(XLOG_LEVEL_ERROR, XLOG_VERBOSE_HIGH);
    xlog_add_default_output();
    xlog_start();
    running = true;

    RandomGen randgen;    

    bool do_exec = default_do_exec;
    const char*	config_template_dir = default_config_template_dir;
    const char*	xrl_dir 	    = default_xrl_dir;
    const char*	config_boot         = default_config_boot;
    IPv4	bind_addr = IPv4::ANY();
    uint16_t	bind_port = FINDER_NG_TCP_DEFAULT_PORT;
    int32_t     quit_time = -1;

    int c;

    while ((c = getopt (argc, argv, "t:b:x:i:p:q:n")) != EOF) {
	switch(c) {  
	case 't':
	    config_template_dir = optarg;
	    break;
	case 'b':
	    config_boot = optarg;
	    break;
	case 'x':
	    xrl_dir = optarg;
	    break;
	case 'q':
	    quit_time = atoi(optarg);
	    break;
	case 'n':
	    do_exec = false;
	    break;
	case 'p':
	    bind_port = static_cast<uint16_t>(atoi(optarg));
	    if (bind_port == 0) {
		fprintf(stderr, "0 is not a valid port.\n");
		exit(-1);
	    }
	    break;
	case 'i':
	    //
	    // User is specifying which interface to bind finder to
	    //
	    try {
		bind_addr = IPv4(optarg);
		if (valid_interface(bind_addr) == false) {
		    fprintf(stderr,
			    "%s is not the address of an active interface.\n",
			    optarg);
		    exit(-1);
		}
	    } catch (const InvalidString&) {
		fprintf(stderr, "%s is not a valid interface address.\n",
			optarg);
		usage();
		exit(-1);
	    }
	    break;
	case '?':
	default:
	    usage();
	}
    }

    //read the router config template files
    TemplateTree *tt;
    try {
	tt = new TemplateTree(config_template_dir, xrl_dir);
    } catch (const XorpException&) {
	printf("caught exception\n");
	xorp_unexpected_handler();
    }
#if 0
    tt->display_tree();
#endif

    //signal handlers so we can clean up when we're killed
    signal(SIGTERM, signalhandler);
    signal(SIGINT, signalhandler);
    //    signal(SIGBUS, signalhandler);
    //    signal(SIGSEGV, signalhandler);

    //initialize the event loop
    EventLoop eventloop; 
    randgen.add_eventloop(&eventloop);

    //
    // Add preferred ipc address on host
    //
    add_permitted_host(if_get_preferred());
    add_permitted_host(IPv4("127.0.0.1"));

    //Start the finder.
    //These are dynamically created so we have control over the
    //deletion order.
    Finder* finder;
    FinderTcpListener* listener;
    FinderXrlTarget* target;
    XorpUnexpectedHandler x(xorp_unexpected_handler);
    try {
	finder = new Finder(eventloop);
	listener = new FinderTcpListener(eventloop, *finder, 
					 finder->commands(), 
					 bind_addr, bind_port);
	target = new FinderXrlTarget(*finder);
    } catch (const InvalidPort& i) {
	fprintf(stderr, "%s: a finder may already be running.\n",
		i.why().c_str());
	delete tt;
	exit(-1);
    } catch (...) {
	xorp_catch_standard_exceptions();
	delete tt;
	exit(-1);
    }

    //start the module manager
    ModuleManager mmgr(eventloop, /*verbose = */true);

    UserDB userdb;
    userdb.load_password_file();

    try {
	//initialize the IPC mechanism
	XrlStdRouter xrlrouter(eventloop, "rtrmgr", bind_addr, bind_port);
	XorpClient xclient(eventloop, xrlrouter);

	//initialize the Task Manager
	TaskManager taskmgr(mmgr, xclient, do_exec);

	//read the router startup configuration file,
	//start the processes required, and initialize them
	MasterConfigTree ct(config_boot, tt, taskmgr);
	XrlRtrmgrInterface rtrmgr_target(xrlrouter, userdb,
					 ct, eventloop, randgen);

	//for testing, rtrmgr can terminate itself after some time.
	XorpTimer quit_timer;
	if (quit_time > 0) {
	    quit_timer = 
		eventloop.new_oneoff_after_ms(quit_time*1000,
					      callback(signalhandler, 0));
	}

	//loop while handling configuration events and signals
	while (running) {
	    printf("+");
	    fflush(stdout);
	    eventloop.run();
	}
    } catch (InitError& e) {
	XLOG_ERROR("rtrmgr shutting down due to error\n");
	fprintf(stderr, "rtrmgr shutting down due to error\n");
	errcode = 1;
    }


    /***********************************************************************/
    /** shutdown everything                                               **/
    /***********************************************************************/

    //Shut down child processes
    mmgr.shutdown();

    //Wait until child processes have terminated
    while (eventloop.timers_pending() && (!mmgr.shutdown_complete())) {
	eventloop.run();
    }

    //delete the template tree
    delete tt;

    //shutdown the finder
    delete target;
    delete listener;
    delete finder;

    //
    // Gracefully stop and exit xlog
    //
    xlog_stop();
    xlog_exit();

    return (errcode);
}











