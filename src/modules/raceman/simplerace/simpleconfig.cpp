/***************************************************************************

    file        : simpleconfig.cpp
    created     : Sun Nov 17 22:21:12 CET 2002
    copyright   : (C) 2002 by Eric Espié                        
    email       : eric.espie@torcs.org   
    version     : $Id$                                  

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/** @file   
    		
    @author	<a href=mailto:eric.espie@torcs.org>Eric Espie</a>
    @version	$Id$
*/

#include <stdlib.h>
#include <stdio.h>
#include <tgf.h>
#include <raceman.h>
#include <racemantools.h>

#include "simplehook.h"
#include "simplerace.h"

#include "simpleconfig.h"

#define SR_CFG "config/simplerace/simplerace.xml"

#define SR_CONFIG_NONE		0
#define SR_CONFIG_TRACK		1
#define SR_CONFIG_DRIVERS	2
#define SR_CONFIG_RACE		3
#define SR_CONFIG_END		4

static int		srConfigState = SR_CONFIG_NONE;
static tRmTrackSelect	ts;
static tRmDrvSelect	ds;
static tRmRaceParam	rp;

void
SrConfigInit(void)
{
    RmInfo->params = GfParmReadFile(SR_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    RmInfo->_reName = "Simple Race";
    
    srConfigState = SR_CONFIG_TRACK;
    SrConfigRunState();
}

/* Simple Race Configuration Automaton */
void
SrConfigRunState(void)
{
    switch (srConfigState) {
    case SR_CONFIG_TRACK:
	ts.nextScreen = SrConfigHookInit();
	ts.prevScreen = SrErrorHookInit();
	ts.param = RmInfo->params;
	ts.trackItf = RmInfo->_reTrackItf;
	RmTrackSelect(&ts);
	srConfigState = SR_CONFIG_DRIVERS; /* next state */
	break;
	
    case SR_CONFIG_DRIVERS:
	ds.nextScreen = SrConfigHookInit();
	ds.prevScreen = SrConfigBackHookInit();
	ds.param = RmInfo->params;
	RmDriversSelect(&ds);
	srConfigState = SR_CONFIG_RACE;
	break;
	
    case SR_CONFIG_RACE:
	rp.nextScreen = SrConfigHookInit();
	rp.prevScreen = SrConfigBackHookInit();
	rp.param = RmInfo->params;
	rp.title = SR_RACE_PARAM_MENU_TITLE;
	rp.confMask = RM_CONF_RACE_LEN | RM_CONF_QUALIFS;
	RmRaceParamMenu(&rp);
	srConfigState = SR_CONFIG_END;
	break;

    case SR_CONFIG_END:
	GfParmWriteFile(SR_CFG, RmInfo->params, RmInfo->_reName, GFPARM_PARAMETER, "../../config/params.dtd");
	GfuiScreenActivate(RmInfo->_reGameScreen);
	break;

    default:
	RmInfo->_reState = RE_STATE_SHUTDOWN;
	GfuiScreenActivate(RmInfo->_reMenuScreen);
	break;
    }
}

void
SrConfigBack(void)
{
    switch (srConfigState) {
    case SR_CONFIG_RACE:
	srConfigState = SR_CONFIG_TRACK;
	SrConfigRunState();
	break;
	
    case SR_CONFIG_END:
	srConfigState = SR_CONFIG_DRIVERS;
	SrConfigRunState();
	break;

    default:
	RmInfo->_reState = RE_STATE_SHUTDOWN;
	GfuiScreenActivate(RmInfo->_reMenuScreen);
	break;
    }
}
