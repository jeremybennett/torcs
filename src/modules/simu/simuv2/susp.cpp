/***************************************************************************

    file                 : susp.cpp
    created              : Sun Mar 19 00:08:41 CET 2000
    copyright            : (C) 2000 by Eric Espie
    email                : torcs@free.fr
    version              : $Id$

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include "sim.h"

/*
 * b2 and b3 calculus
 */
static void
initDamper(tSuspension *susp)
{
}

/*
 * get damper force
 */
static tdble
damperForce(tSuspension *susp)
{
    tDamperDef *dampdef;
    tdble     f;
    tdble     av;
    tdble     v;

    v = susp->v;

    if (fabs(v) > 10.0) {
	v = SIGN(v) * 10.0;
    }
    
    if (v > 0) {
	/* rebound */
	dampdef = &(susp->damper.rebound);
    } else {
	/* bump */
	dampdef = &(susp->damper.bump);
    }
    
    av = fabs(v);
    f = (dampdef->C1 * av + dampdef->b1);
    f *= SIGN(v);

    return f;
}

/*
 * get spring force
 */
static tdble
springForce(tSuspension *susp)
{
    tSpring *spring = &(susp->spring);
    tdble f;

    /* K is < 0 */
    f = spring->K * (susp->x - spring->x0) + spring->F0;
    if (f < 0) {
	f = 0;
    }

    return f;
}


void
SimSuspCheckIn(tSuspension *susp)
{
    susp->state = 0;
    susp->x *= susp->spring.bellcrank;
    if (susp->x > susp->spring.xMax) {
	susp->x = susp->spring.xMax;
	susp->state = SIM_SUSP_EXT;
    } else if (susp->x < susp->spring.packers) {
	susp->x = susp->spring.packers;
	susp->state = SIM_SUSP_COMP;
    }    
}

void
SimSuspUpdate(tSuspension *susp)
{
    susp->force = (springForce(susp) + damperForce(susp)) * susp->spring.bellcrank;
}


void
SimSuspConfig(void *hdle, char *section, tSuspension *susp, tdble F0, tdble X0)
{
    susp->spring.K          = GfParmGetNum(hdle, section, PRM_SPR, (char*)NULL, 175000);
    susp->spring.xMax       = GfParmGetNum(hdle, section, PRM_SUSPCOURSE, (char*)NULL, 0.5);
    susp->spring.bellcrank  = GfParmGetNum(hdle, section, PRM_BELLCRANK, (char*)NULL, 1.0);
    susp->spring.packers    = GfParmGetNum(hdle, section, PRM_PACKERS, (char*)NULL, 0);
    susp->damper.bump.C1    = GfParmGetNum(hdle, section, PRM_SLOWBUMP, (char*)NULL, 0);
    susp->damper.rebound.C1 = GfParmGetNum(hdle, section, PRM_SLOWREBOUND, (char*)NULL, 0);

    susp->spring.x0 = susp->spring.bellcrank * X0;
    susp->spring.F0 = F0 / susp->spring.bellcrank;
    susp->spring.K = - susp->spring.K;
    susp->damper.bump.b1 = 0;
    susp->damper.rebound.b1 = 0;

    initDamper(susp);
}

