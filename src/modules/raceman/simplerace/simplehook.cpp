/***************************************************************************

    file        : simplehook.cpp
    created     : Tue Dec  3 22:54:03 CET 2002
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

/** @file   
    		
    @author	<a href=mailto:eric.espie@torcs.org>Eric Espie</a>
    @version	$Id$
*/

#include <stdlib.h>
#include <stdio.h>
#include <tgf.h>
#include <raceman.h>
#include <racemantools.h>

#include "simplerace.h"
#include "simpleconfig.h"

#include "simplehook.h"

/***************************************************************/
/* Callback hooks used only to run the automaton on activation */
static void	*configHookHandle = 0;

static void
configHookActivate(void * /* dummy */)
{
    SrConfigRunState();
}

void *
SrConfigHookInit(void)
{
    if (configHookHandle) {
	return configHookHandle;
    }

    configHookHandle = GfuiHookCreate(0, configHookActivate);

    return configHookHandle;
}

void
SrConfigHookShutdown(void)
{
    if (configHookHandle) {
	GfuiHookRelease(configHookHandle);
	configHookHandle = 0;
    }
}


/***************************************************************/
/* BACK TO RACE HOOK */

static void	*BackToRaceHookHandle = 0;

static void
BackToRaceHookActivate(void * /* dummy */)
{
    RmInfo->_reState = RE_STATE_RACE;
    GfuiScreenActivate(RmInfo->_reGameScreen);
}

void *
SrBackToRaceHookInit(void)
{
    if (BackToRaceHookHandle) {
	return BackToRaceHookHandle;
    }

    BackToRaceHookHandle = GfuiHookCreate(0, BackToRaceHookActivate);

    return BackToRaceHookHandle;
}

void
SrBackToRaceHookShutdown(void)
{
    if (BackToRaceHookHandle) {
	GfuiHookRelease(BackToRaceHookHandle);
	BackToRaceHookHandle = 0;
    }
}


/***************************************************************/
/* Config Back Hook */

static void	*ConfigBackHookHandle = 0;

static void
ConfigBackHookActivate(void * /* dummy */)
{
    SrConfigBack();
}

void *
SrConfigBackHookInit(void)
{
    if (ConfigBackHookHandle) {
	return ConfigBackHookHandle;
    }

    ConfigBackHookHandle = GfuiHookCreate(0, ConfigBackHookActivate);

    return ConfigBackHookHandle;
}

void
SrConfigBackHookShutdown(void)
{
    if (ConfigBackHookHandle) {
	GfuiHookRelease(ConfigBackHookHandle);
	ConfigBackHookHandle = 0;
    }
}

/***************************************************************/
/* RESTART RACE */

static void	*RestartRaceHookHandle = 0;

static void
RestartRaceHookActivate(void * /* dummy */)
{
    RmInfo->_reState = RE_STATE_PRE_RACE;    
    GfuiScreenActivate(RmInfo->_reGameScreen);
}

static void *
SrRestartRaceHookInit(void)
{
    if (RestartRaceHookHandle) {
	return RestartRaceHookHandle;
    }

    RestartRaceHookHandle = GfuiHookCreate(0, RestartRaceHookActivate);

    return RestartRaceHookHandle;
}

/***************************************************************/
/* RACE AGAIN ? */

static void	*RaceAgainHookHandle = 0;

static void
RaceAgainHookActivate(void * /* dummy */)
{
    RmConfirmScreen("Restart Race ?",
		    "Yes", "Restart the Same Race", SrRestartRaceHookInit(),
		    "No", "Return to main menu", RmInfo->_reGameScreen,
		    0);
}

void *
SrRaceAgainHookInit(void)
{
    if (RaceAgainHookHandle) {
	return RaceAgainHookHandle;
    }

    RaceAgainHookHandle = GfuiHookCreate(0, RaceAgainHookActivate);

    return RaceAgainHookHandle;
}

void
SrRaceAgainHookShutdown(void)
{
    if (RaceAgainHookHandle) {
	GfuiHookRelease(RaceAgainHookHandle);
	RaceAgainHookHandle = 0;
    }
}

/***************************************************************/
/* ERROR HOOK */

static void	*errorHookHandle = 0;


static void
errorHookActivate(void * /* dummy */)
{
    RmInfo->_reState = RE_STATE_SHUTDOWN;
    GfuiScreenActivate(RmInfo->_reMenuScreen);
}


void *
SrErrorHookInit(void)
{
    if (errorHookHandle) {
	return errorHookHandle;
    }

    errorHookHandle = GfuiHookCreate(0, errorHookActivate);

    return errorHookHandle;
}


void
SrErrorHookShutdown(void)
{
    if (errorHookHandle) {
	GfuiHookRelease(errorHookHandle);
	errorHookHandle = 0;
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
SrHookInit(void)
{
    if (HookHandle) {
	return HookHandle;
    }

    HookHandle = GfuiHookCreate(0, HookActivate);

    return HookHandle;
}

void
SrHookShutdown(void)
{
    if (HookHandle) {
	GfuiHookRelease(HookHandle);
	HookHandle = 0;
    }
}

#endif
