/***************************************************************************

    file                 : qracemain.cpp
    created              : Sun Jan 30 22:41:27 CET 2000
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


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <racemantools.h>
#include <robottools.h>

#include "qracemain.h"

#define QR_CFG "config/quickrace/qrace.xml"

#define QR_CONFIG_NONE		0
#define QR_CONFIG_TRACK		1
#define QR_CONFIG_DRIVERS	2
#define QR_CONFIG_RACE		3
#define QR_CONFIG_END		4

static int		qrConfigState = QR_CONFIG_NONE;
static tRmTrackSelect	ts;
static tRmDrvSelect	ds;
static tRmRaceParam	rp;

/***************************************************************/
/* Config HOOK */

static void	*ConfigHookHandle = 0;

static void
ConfigHookActivate(void * /* dummy */)
{
    qrConfigRunState(0);
}

static void *
qrConfigHookInit(void)
{
    if (ConfigHookHandle) {
	return ConfigHookHandle;
    }

    ConfigHookHandle = GfuiHookCreate(0, ConfigHookActivate);

    return ConfigHookHandle;
}

void
qrConfigHookShutdown(void)
{
    if (ConfigHookHandle) {
	GfuiHookRelease(ConfigHookHandle);
	ConfigHookHandle = 0;
    }
}

/***************************************************************/
/* ConfigBack HOOK */

static void
qrConfigBack(void)
{
    switch (qrConfigState) {
    case QR_CONFIG_RACE:
	qrConfigState = QR_CONFIG_TRACK;
	qrConfigRunState(0);
	break;
	
    case QR_CONFIG_END:
	qrConfigState = QR_CONFIG_DRIVERS;
	qrConfigRunState(0);
	break;

    default:
	qrConfigState = QR_CONFIG_TRACK;
	qrMenuRun();
	break;
    }
}

static void	*ConfigBackHookHandle = 0;

static void
ConfigBackHookActivate(void * /* dummy */)
{
    qrConfigBack();
}

static void *
qrConfigBackHookInit(void)
{
    if (ConfigBackHookHandle) {
	return ConfigBackHookHandle;
    }

    ConfigBackHookHandle = GfuiHookCreate(0, ConfigBackHookActivate);

    return ConfigBackHookHandle;
}

void
qrConfigBackHookShutdown(void)
{
    if (ConfigBackHookHandle) {
	GfuiHookRelease(ConfigBackHookHandle);
	ConfigBackHookHandle = 0;
    }
}


/***************************************************************/
void
qrConfigInit(void)
{
    RmInfo->params = GfParmReadFile(QR_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    RmInfo->_reName = "Quick Race";
    
    qrConfigState = QR_CONFIG_TRACK;
    qrMenuRun();
}

/***************************************************************/
/* Quick Race Configuration Automaton */
void
qrConfigRunState(void * /* dummy */)
{
    switch (qrConfigState) {
    case QR_CONFIG_TRACK:
	ts.nextScreen = qrConfigHookInit();
	ts.prevScreen = qrConfigBackHookInit();
	ts.param = RmInfo->params;
	ts.trackItf = RmInfo->_reTrackItf;
	RmTrackSelect(&ts);
	qrConfigState = QR_CONFIG_DRIVERS; /* next state */
	break;
	
    case QR_CONFIG_DRIVERS:
	ds.nextScreen = qrConfigHookInit();
	ds.prevScreen = qrConfigBackHookInit();
	ds.param = RmInfo->params;
	RmDriversSelect(&ds);
	qrConfigState = QR_CONFIG_RACE;
	break;
	
    case QR_CONFIG_RACE:
	rp.nextScreen = qrConfigHookInit();
	rp.prevScreen = qrConfigBackHookInit();
	rp.param = RmInfo->params;
	rp.title = "Quick Race Options";
	rp.confMask = RM_CONF_RACE_LEN;
	RmRaceParamMenu(&rp);
	qrConfigState = QR_CONFIG_END;
	break;

    case QR_CONFIG_END:
	GfParmWriteFile(QR_CFG, RmInfo->params, RmInfo->_reName, GFPARM_PARAMETER, "../params.dtd");
	qrConfigState = QR_CONFIG_TRACK;
	qrMenuRun();
	break;

    default:
	RmInfo->_reState = RE_STATE_SHUTDOWN;
	GfuiScreenActivate(RmInfo->_reMenuScreen);
	break;
    }
}



#if 0

/***************************************************************/
/* HOOK TEMPLATE */

static void	*HookHandle = 0;

static void
HookActivate(void * /* dummy */)
{
}

void *
qrHookInit(void)
{
    if (HookHandle) {
	return HookHandle;
    }

    HookHandle = GfuiHookCreate(0, HookActivate);

    return HookHandle;
}

void
qrHookShutdown(void)
{
    if (HookHandle) {
	GfuiHookRelease(HookHandle);
	HookHandle = 0;
    }
}

#endif
