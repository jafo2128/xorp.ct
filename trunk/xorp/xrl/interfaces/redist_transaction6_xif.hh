/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/redist_transaction6_xif.hh,v 1.2 2004/05/12 21:57:15 pavlin Exp $
 */

#ifndef __XRL_INTERFACES_REDIST_TRANSACTION6_XIF_HH__
#define __XRL_INTERFACES_REDIST_TRANSACTION6_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifRedistTransaction6"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlRedistTransaction6V0p1Client {
public:
    XrlRedistTransaction6V0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlRedistTransaction6V0p1Client() {}

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr StartTransactionCB;
    /**
     *  Send Xrl intended to:
     *
     *  Start transaction.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_start_transaction(
	const char*	target_name,
	const StartTransactionCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CommitTransactionCB;
    /**
     *  Send Xrl intended to:
     *
     *  Commit transaction.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param tid the transaction ID of this transaction.
     */
    bool send_commit_transaction(
	const char*	target_name,
	const uint32_t&	tid,
	const CommitTransactionCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AbortTransactionCB;
    /**
     *  Send Xrl intended to:
     *
     *  Abort transaction.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param tid the transaction ID of this transaction.
     */
    bool send_abort_transaction(
	const char*	target_name,
	const uint32_t&	tid,
	const AbortTransactionCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddRouteCB;
    /**
     *  Send Xrl intended to:
     *
     *  Add/delete a routing entry.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param tid the transaction ID of this transaction.
     *
     *  @param dst destination network.
     *
     *  @param nh nexthop router address.
     *
     *  @param ifname interface name associated with nexthop.
     *
     *  @param vifname virtual interface name with nexthop.
     *
     *  @param metric origin routing protocol metric for route.
     *
     *  @param ad administrative distance of origin routing protocol.
     *
     *  @param cookie value set be requestor to identify redistribution source.
     *  Typical value is the originating protocol name.
     *
     *  @param protocol_origin the name of the protocol that originated this
     *  entry.
     */
    bool send_add_route(
	const char*	target_name,
	const uint32_t&	tid,
	const IPv6Net&	dst,
	const IPv6&	nh,
	const string&	ifname,
	const string&	vifname,
	const uint32_t&	metric,
	const uint32_t&	ad,
	const string&	cookie,
	const string&	protocol_origin,
	const AddRouteCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeleteRouteCB;

    bool send_delete_route(
	const char*	target_name,
	const uint32_t&	tid,
	const IPv6Net&	network,
	const string&	cookie,
	const DeleteRouteCB&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall_start_transaction(
	const XrlError&	e,
	XrlArgs*	a,
	StartTransactionCB		cb
    );

    void unmarshall_commit_transaction(
	const XrlError&	e,
	XrlArgs*	a,
	CommitTransactionCB		cb
    );

    void unmarshall_abort_transaction(
	const XrlError&	e,
	XrlArgs*	a,
	AbortTransactionCB		cb
    );

    void unmarshall_add_route(
	const XrlError&	e,
	XrlArgs*	a,
	AddRouteCB		cb
    );

    void unmarshall_delete_route(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteRouteCB		cb
    );

};

#endif /* __XRL_INTERFACES_REDIST_TRANSACTION6_XIF_HH__ */
