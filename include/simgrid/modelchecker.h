/* simgrid/modelchecker.h - Formal Verification made possible in SimGrid    */

/* Copyright (c) 2008-2012. The SimGrid Team. All rights reserved.          */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include <simgrid_config.h> /* HAVE_MC ? */
#include <xbt.h>
#include "xbt/automaton.h"

#ifndef SIMGRID_MODELCHECKER_H
#define SIMGRID_MODELCHECKER_H

#ifdef HAVE_MC

extern int _sg_do_model_check; /* please don't use directly: we inline MC_is_active, but that's what you should use */

#define MC_is_active() _sg_do_model_check

XBT_PUBLIC(void) MC_assert(int);
XBT_PUBLIC(int) MC_random(void);
XBT_PUBLIC(void) MC_automaton_new_propositional_symbol(const char* id, void* fct);
XBT_PUBLIC(void *) MC_snapshot(void);
XBT_PUBLIC(int) MC_compare_snapshots(void *s1, void *s2);

#else

#define MC_assert(a) xbt_assert(a)
#define MC_is_active() 0

#endif



#endif /* SIMGRID_MODELCHECKER_H */
