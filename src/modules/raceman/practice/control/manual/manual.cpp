/***************************************************************************

    file                 : manual.cpp
    created              : Tue Feb 22 21:28:51 CET 2000
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
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <racemantools.h>
#include <osspec.h>

#include <practicectrl.h>

static void		*prMainMenuHandle = NULL;
static void		*PractParam;


#ifdef _WIN32
BOOL WINAPI DllEntryPoint (HINSTANCE hDLL, DWORD dwReason, LPVOID Reserved)
{
    return TRUE;
}
#endif

static void
prStartSess(void *vf)
{
    tfPractice run = (tfPractice)vf;
    PractParam = GfParmReadFile(PRACTICE_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    GfParmSetStr(PractParam, RM_SECT_RACE, RM_ATTR_SHOW_RACE, "yes");

    GfuiScreenDeactivate();
    run();

}

static void
prStartSessBlind(void *vf)
{
    tfPractice run = (tfPractice)vf;
    PractParam = GfParmReadFile(PRACTICE_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    GfParmSetStr(PractParam, RM_SECT_RACE, RM_ATTR_SHOW_RACE, "no");

    GfuiScreenDeactivate();
    run();

}

static void
prResults(tRingListHead *res)
{
    char	*trackName;

    PractParam = GfParmReadFile(PRACTICE_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    trackName = GfParmGetStr(PractParam, "Race", "track", "");
    trackName = RmGetTrackName(trackName);

    RmPracticeResults(prMainMenuHandle, trackName, res);
}


/*
 * Function
 *	
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	
 */
static void
prStart(tPracticeFct *prf)
{
    char	buf[256];
    char	*trackName;

    /* Init the menu */
    if (prMainMenuHandle != NULL) {
	GfuiScreenRelease(prMainMenuHandle);
    }
    prMainMenuHandle = GfuiScreenCreateEx((float*)NULL, 
					  NULL, NULL, 
					  NULL, NULL, 
					  1);
    GfuiScreenAddBgImg(prMainMenuHandle, "data/img/splash-prsess.png");

    GfuiMenuDefaultKeysAdd(prMainMenuHandle);
    sprintf(buf, "Torcs Practice Session");
    GfuiTitleCreate(prMainMenuHandle, buf, strlen(buf));
    PractParam = GfParmReadFile(PRACTICE_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    trackName = GfParmGetStr(PractParam, "Race", "track", "");
    trackName = RmGetTrackName(trackName);
    GfuiLabelCreate(prMainMenuHandle, trackName, GFUI_FONT_LARGE, 320, 420, GFUI_ALIGN_HC_VB, 0);

    GfuiMenuButtonCreate(prMainMenuHandle,
			 "Start In Normal Mode",
			 "Start a Session with the display on",
			 (void*)prf->run,
			 prStartSess);

    GfuiMenuButtonCreate(prMainMenuHandle,
			 "Start In Blind Mode",
			 "Start a Session with no display",
			 (void*)prf->run,
			 prStartSessBlind);
    
    GfuiMenuBackQuitButtonCreate(prMainMenuHandle,
				 "Back", "Return to TORCS Practice Menu",
				 prf->backMenu, GfuiScreenActivate);

    GfuiScreenActivate(prMainMenuHandle);
}

static int
prInit(int index, void *p)
{
    tPractCtrlItf *itf = (tPractCtrlItf *)p;
    
    itf->startCtrl = prStart;
    itf->results = prResults;
    
    return 0;
}

extern "C" int
manual(tModInfo *modInfo)
{
    modInfo->name = "Start Practice Session";		/* name of the module (short) */
    modInfo->desc = "Menu Driven Practice Session";	/* description of the module (can be long) */
    modInfo->fctInit = prInit;	/* init function */
    modInfo->gfId = 0;		/* always loaded  */
    modInfo->index = 0;
    modInfo->prio = 10;	/* in order to be listed at the begining */
    
    return 0;
}


