/*
 * Copyright (c) 2002 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/tgt-gen'.
 */

#ident "$XORP$"


#include "finder_base.hh"

const XrlCmdError
XrlFinderTargetBase::handle_common_0_1_get_target_name(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 0) { 
	XLOG_ERROR("Wrong number of arguments (%u != 0) handling common/0.1/get_target_name", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string name; 
    try {
	XrlCmdError e = common_0_1_get_target_name(
	    name);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for common/0.1/get_target_name failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("name", name);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlFinderTargetBase::handle_common_0_1_get_version(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 0) { 
	XLOG_ERROR("Wrong number of arguments (%u != 0) handling common/0.1/get_version", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string version; 
    try {
	XrlCmdError e = common_0_1_get_version(
	    version);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for common/0.1/get_version failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("version", version);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlFinderTargetBase::handle_finder_0_1_register_finder_client(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 1) { 
	XLOG_ERROR("Wrong number of arguments (%u != 1) handling finder/0.1/register_finder_client", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string instance_id; 
    try {
	XrlCmdError e = finder_0_1_register_finder_client(
	    xrl.const_args().get_string("target_name"), 
	    instance_id);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for finder/0.1/register_finder_client failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("instance_id", instance_id);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlFinderTargetBase::handle_finder_0_1_unregister_finder_client(const Xrl& xrl, XrlArgs* /* args */)
{
    if (xrl.const_args().size() != 0) { 
	XLOG_ERROR("Wrong number of arguments (%u != 0) handling finder/0.1/unregister_finder_client", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = finder_0_1_unregister_finder_client();
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for finder/0.1/unregister_finder_client failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlFinderTargetBase::handle_finder_0_1_add_xrl(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 3) { 
	XLOG_ERROR("Wrong number of arguments (%u != 3) handling finder/0.1/add_xrl", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string resolved_xrl_method_name; 
    try {
	XrlCmdError e = finder_0_1_add_xrl(
	    xrl.const_args().get_string("xrl"), 
	    xrl.const_args().get_string("protocol_name"), 
	    xrl.const_args().get_string("protocol_args"), 
	    resolved_xrl_method_name);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for finder/0.1/add_xrl failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("resolved_xrl_method_name", resolved_xrl_method_name);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlFinderTargetBase::handle_finder_0_1_remove_xrl(const Xrl& xrl, XrlArgs* /* args */)
{
    if (xrl.const_args().size() != 1) { 
	XLOG_ERROR("Wrong number of arguments (%u != 1) handling finder/0.1/remove_xrl", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = finder_0_1_remove_xrl(
	    xrl.const_args().get_string("xrl"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for finder/0.1/remove_xrl failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlFinderTargetBase::handle_finder_0_1_get_xrl_targets(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 0) { 
	XLOG_ERROR("Wrong number of arguments (%u != 0) handling finder/0.1/get_xrl_targets", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    XrlAtomList target_names; 
    try {
	XrlCmdError e = finder_0_1_get_xrl_targets(
	    target_names);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for finder/0.1/get_xrl_targets failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("target_names", target_names);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlFinderTargetBase::handle_finder_0_1_get_xrls_registered_by(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 1) { 
	XLOG_ERROR("Wrong number of arguments (%u != 1) handling finder/0.1/get_xrls_registered_by", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    XrlAtomList xrls; 
    try {
	XrlCmdError e = finder_0_1_get_xrls_registered_by(
	    xrl.const_args().get_string("target_name"), 
	    xrls);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for finder/0.1/get_xrls_registered_by failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("xrls", xrls);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlFinderTargetBase::handle_finder_0_1_get_all_xrls(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 0) { 
	XLOG_ERROR("Wrong number of arguments (%u != 0) handling finder/0.1/get_all_xrls", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    XrlAtomList xrls; 
    try {
	XrlCmdError e = finder_0_1_get_all_xrls(
	    xrls);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for finder/0.1/get_all_xrls failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("xrls", xrls);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

