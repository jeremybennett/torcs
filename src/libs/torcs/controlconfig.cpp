/***************************************************************************

    file        : controlconfig.cpp
    created     : Wed Mar 12 21:20:34 CET 2003
    copyright   : (C) 2003 by Eric Espié                        
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tgf.h>
#include <track.h>
#include <robot.h>
#include "joystickconfig.h"
#include "mouseconfig.h"
#include <playerpref.h>

#include "controlconfig.h"

static float LabelColor[] = {1.0, 0.0, 1.0, 1.0};

typedef struct
{
    char	*dispName;
    char	*parmName;
    void	*handle;
} tCtrl;


static tCtrl	controlList[] = {
    {"Joystick", HM_VAL_JOYSTICK, NULL},
    {"Keyboard", HM_VAL_KEYBOARD, NULL},
    {"Mouse",    HM_VAL_MOUSE,    NULL}
};

static const int dfltCtrl = 2;
static const int nbControl = sizeof(controlList) / sizeof(controlList[0]);
static int	curControl = 0;

static void	*scrHandle = NULL;
static void	*PrefHdle;
static int	ctrlLabelId;

static char	buf[1024];

static void
updateLabelText(void)
{
    GfuiLabelSetText (scrHandle, ctrlLabelId, controlList[curControl].dispName);
}

static void
ctrlPrevNext(void *vdelta)
{
    int delta = (int)vdelta;

    curControl += delta;
    if (curControl < 0) {
	curControl = nbControl - 1;
    } else {
	if (curControl >= nbControl) {
	    curControl = 0;
	}
    }
    if (!controlList[curControl].handle) {
	ctrlPrevNext(vdelta);
    }
    
    updateLabelText();
}

static void
initFromConf(void)
{
    char	*ctrl;

    sprintf(buf, "%s%s", GetLocalDir(), HM_PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_REREAD | GFPARM_RMODE_CREAT);

    ctrl = GfParmGetStr(PrefHdle, HM_SECT_PREF, HM_ATT_CONTROL, HM_VAL_MOUSE);
    for (curControl = 0; curControl < nbControl; curControl++) {
	if ((!strcmp(controlList[curControl].parmName, ctrl)) &&
	    controlList[curControl].handle) {
	    break;
	}
    }
    if (curControl == nbControl) {
	curControl = dfltCtrl;
    }
}

static void
saveAndConf(void * /* dummy */)
{
    GfParmSetStr(PrefHdle, HM_SECT_PREF, HM_ATT_CONTROL, controlList[curControl].parmName);
    GfuiScreenActivate(controlList[curControl].handle);
}

static void
onActivate(void * /* dummy */)
{
    initFromConf();
    updateLabelText();
}

void *
TorcsControlMenuInit(void *prevMenu)
{
    int		y, x1, x2;

    if (scrHandle) {
	return scrHandle;
    }

    scrHandle = GfuiScreenCreateEx((float*)NULL, NULL, onActivate, NULL, (tfuiCallback)NULL, 1);
    GfuiTitleCreate(scrHandle, "Control Configuration", 0);

    GfuiScreenAddBgImg(scrHandle, "data/img/splash-ctrlconf.png");

    x1 = 200;
    x2 = 440;
    y = 380;

    GfuiLabelCreate(scrHandle,
		    "Control",
		    GFUI_FONT_LARGE,
		    320, y, GFUI_ALIGN_HC_VB,
		    0);   

    y -= 30;
    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-left.png",
		       "data/img/arrow-left.png",
		       "data/img/arrow-left.png",
		       "data/img/arrow-left-pushed.png",
		       x1, y, GFUI_ALIGN_HC_VB, 0,
		       (void*)-1, ctrlPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_LEFT, "Previous Control", (void*)-1, ctrlPrevNext, NULL);

    ctrlLabelId = GfuiLabelCreate(scrHandle,
				  "",
				  GFUI_FONT_LARGE_C,
				  320, y, GFUI_ALIGN_HC_VB,
				  30);

    GfuiLabelSetColor(scrHandle, ctrlLabelId, LabelColor);

    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right-pushed.png",
		       x2, y, GFUI_ALIGN_HC_VB, 0,
		       (void*)1, ctrlPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_RIGHT, "Next Control", (void*)1, ctrlPrevNext, NULL);

    GfuiAddKey(scrHandle, 13, "Configure Control", NULL, saveAndConf, NULL);
    GfuiButtonCreate(scrHandle, "Configure", GFUI_FONT_LARGE, 210, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, saveAndConf, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiAddKey(scrHandle, 27, "Cancel", prevMenu, GfuiScreenActivate, NULL);
    GfuiButtonCreate(scrHandle, "Back", GFUI_FONT_LARGE, 430, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     prevMenu, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);


    controlList[0].handle = TorcsJoystick1MenuInit(prevMenu);
    controlList[2].handle = TorcsMouseMenuInit(prevMenu);

    return scrHandle;
}
