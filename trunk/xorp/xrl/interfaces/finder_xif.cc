/*
 * Copyright (c) 2002 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/clnt-gen'.
 */

#ident "$XORP$"

#include "finder_xif.hh"

bool
XrlFinderV0p1Client::send_register_finder_client(
	const char*	the_tgt, 
	const string&	target_name, 
	const CB0&	cb
)
{
    Xrl x(the_tgt, "finder/0.1/register_finder_client");
    x.args().add("target_name", target_name);
    return _router->send(x, callback(this, &XrlFinderV0p1Client::unmarshall0, cb));
}


/* Unmarshall register_finder_client */
void
XrlFinderV0p1Client::unmarshall0(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB0		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0);
	return;
    } else if (a && a->size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != 1)", (uint32_t)a->size());
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    string instance_id;
    try {
	a->get("instance_id", instance_id);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &instance_id);
}

bool
XrlFinderV0p1Client::send_unregister_finder_client(
	const char*	the_tgt, 
	const CB1&	cb
)
{
    Xrl x(the_tgt, "finder/0.1/unregister_finder_client");
    return _router->send(x, callback(this, &XrlFinderV0p1Client::unmarshall1, cb));
}


/* Unmarshall unregister_finder_client */
void
XrlFinderV0p1Client::unmarshall1(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB1		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != 0)", (uint32_t)a->size());
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlFinderV0p1Client::send_add_xrl(
	const char*	the_tgt, 
	const string&	xrl, 
	const string&	protocol_name, 
	const string&	protocol_args, 
	const CB2&	cb
)
{
    Xrl x(the_tgt, "finder/0.1/add_xrl");
    x.args().add("xrl", xrl);
    x.args().add("protocol_name", protocol_name);
    x.args().add("protocol_args", protocol_args);
    return _router->send(x, callback(this, &XrlFinderV0p1Client::unmarshall2, cb));
}


/* Unmarshall add_xrl */
void
XrlFinderV0p1Client::unmarshall2(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB2		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0);
	return;
    } else if (a && a->size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != 1)", (uint32_t)a->size());
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    string resolved_xrl_method_name;
    try {
	a->get("resolved_xrl_method_name", resolved_xrl_method_name);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &resolved_xrl_method_name);
}

bool
XrlFinderV0p1Client::send_remove_xrl(
	const char*	the_tgt, 
	const string&	xrl, 
	const CB3&	cb
)
{
    Xrl x(the_tgt, "finder/0.1/remove_xrl");
    x.args().add("xrl", xrl);
    return _router->send(x, callback(this, &XrlFinderV0p1Client::unmarshall3, cb));
}


/* Unmarshall remove_xrl */
void
XrlFinderV0p1Client::unmarshall3(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB3		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != 0)", (uint32_t)a->size());
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlFinderV0p1Client::send_get_xrl_targets(
	const char*	the_tgt, 
	const CB4&	cb
)
{
    Xrl x(the_tgt, "finder/0.1/get_xrl_targets");
    return _router->send(x, callback(this, &XrlFinderV0p1Client::unmarshall4, cb));
}


/* Unmarshall get_xrl_targets */
void
XrlFinderV0p1Client::unmarshall4(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB4		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0);
	return;
    } else if (a && a->size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != 1)", (uint32_t)a->size());
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    XrlAtomList target_names;
    try {
	a->get("target_names", target_names);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &target_names);
}

bool
XrlFinderV0p1Client::send_get_xrls_registered_by(
	const char*	the_tgt, 
	const string&	target_name, 
	const CB5&	cb
)
{
    Xrl x(the_tgt, "finder/0.1/get_xrls_registered_by");
    x.args().add("target_name", target_name);
    return _router->send(x, callback(this, &XrlFinderV0p1Client::unmarshall5, cb));
}


/* Unmarshall get_xrls_registered_by */
void
XrlFinderV0p1Client::unmarshall5(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB5		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0);
	return;
    } else if (a && a->size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != 1)", (uint32_t)a->size());
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    XrlAtomList xrls;
    try {
	a->get("xrls", xrls);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &xrls);
}

bool
XrlFinderV0p1Client::send_get_all_xrls(
	const char*	the_tgt, 
	const CB6&	cb
)
{
    Xrl x(the_tgt, "finder/0.1/get_all_xrls");
    return _router->send(x, callback(this, &XrlFinderV0p1Client::unmarshall6, cb));
}


/* Unmarshall get_all_xrls */
void
XrlFinderV0p1Client::unmarshall6(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB6		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0);
	return;
    } else if (a && a->size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != 1)", (uint32_t)a->size());
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    XrlAtomList xrls;
    try {
	a->get("xrls", xrls);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &xrls);
}
