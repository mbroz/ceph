// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*- 
// vim: ts=8 sw=2 smarttab
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2004-2006 Sage Weil <sage@newdream.net>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software 
 * Foundation.  See file COPYING.
 * 
 */

#ifndef __MDS_EANCHORCLIENT_H
#define __MDS_EANCHORCLIENT_H

#include <assert.h>
#include "config.h"
#include "include/types.h"

#include "../LogEvent.h"
#include "../Anchor.h"

class EAnchorClient : public LogEvent {
protected:
  __u32 op;
  version_t atid; 

 public:
  EAnchorClient() : LogEvent(EVENT_ANCHORCLIENT) { }
  EAnchorClient(int o, version_t at) :
    LogEvent(EVENT_ANCHORCLIENT),
    op(o), atid(at) { }

  void encode(bufferlist &bl) const {
    ::encode(op, bl);
    ::encode(atid, bl);
  }
  void decode(bufferlist::iterator &bl) {
    ::decode(op, bl);
    ::decode(atid, bl);
  }

  void print(ostream& out) {
    out << "EAnchorClient " << get_anchor_opname(op);
    if (atid) out << " atid " << atid;
  }  

  void replay(MDS *mds);
  
};

#endif
