/***************************************************************************

    file        : control.cpp
    created     : Thu Mar  6 22:01:33 CET 2003
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
    		Human control (joystick, mouse and keyboard).
    @author	<a href=mailto:eric.espie@torcs.org>Eric Espie</a>
    @version	$Id$
    @ingroup	ctrl
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <js.h>

#include <tgf.h>

static int gfctrlJoyPresent = GFCTRL_JOY_UNTESTED;
static jsJoystick *js[NUM_JOY] = {NULL};


static void
gfJoyFirstInit(void)
{
    int index;
    
    gfctrlJoyPresent = GFCTRL_JOY_NONE;

    for (index = 0; index < NUM_JOY; index++) {
	if (js[index] == NULL) {
	    js[index] = new jsJoystick(index);
	}
    
	if (js[index]->notWorking()) {
	    /* don't configure the joystick */
	    js[index] = NULL;
	} else {
	    gfctrlJoyPresent = GFCTRL_JOY_PRESENT;
	}
    }
}

/** Initialize the joystick control
    @ingroup	ctrl
    @return	pointer on a tCtrlJoyInfo structure
		<br>0 .. if no joystick present
    @note	call GfctrlJoyRelease to free the tCtrlJoyInfo structure
    @see	GfctrlJoyRelease
    @see	tCtrlJoyInfo
*/
tCtrlJoyInfo *
GfctrlJoyInit(void)
{
    tCtrlJoyInfo	*joyInfo = NULL;

    if (gfctrlJoyPresent == GFCTRL_JOY_UNTESTED) {
	gfJoyFirstInit();
    }

    if (gfctrlJoyPresent == GFCTRL_JOY_PRESENT) {
	joyInfo = (tCtrlJoyInfo *)calloc(1, sizeof(tCtrlJoyInfo));
    }

    return joyInfo;
}

/** Release the tCtrlJoyInfo structure
    @ingroup	ctrl
    @param	joyInfo	joystick structure
    @return	none
*/
void
GfctrlJoyRelease(tCtrlJoyInfo *joyInfo)
{
    FREEZ(joyInfo);
}


/** Check if a joystick is present
    @ingroup	ctrl
    @return	GFCTRL_JOY_NONE	if no joystick
		<br>GFCTRL_JOY_PRESENT if a joystick is present
*/
int
GfctrlJoyIsPresent(void)
{
    if (gfctrlJoyPresent == GFCTRL_JOY_UNTESTED) {
	gfJoyFirstInit();
    }

    return gfctrlJoyPresent;
}


/** Get the joystick current values
    @ingroup	ctrl
    @param	joyInfo	joystick structure
    @return	<tt>0 ... </tt>Ok
		<br><tt>-1 .. </tt>Error
    @note	The tCtrlJoyInfo structure is updated with the new values
*/
int
GfctrlJoyGetCurrent(tCtrlJoyInfo *joyInfo)
{
    int			ind;
    int			i;
    int			b;
    unsigned int	mask;

    if (gfctrlJoyPresent == GFCTRL_JOY_PRESENT) {
    	for (ind = 0; ind < NUM_JOY; ind++) {
	    if (js[ind]) {
		js[ind]->read(&b, &(joyInfo->ax[MAX_AXES * ind]));

		/* Joystick buttons */
		for (i = 0, mask = 1; i < GFCTRL_JOY_MAXBUTTON; i++, mask *= 2) {
		    if (((b & mask) != 0) && ((joyInfo->oldb[ind] & mask) == 0)) {
			joyInfo->edgeup[i + GFCTRL_JOY_MAXBUTTON * ind] = 1;
		    } else {
			joyInfo->edgeup[i + GFCTRL_JOY_MAXBUTTON * ind] = 0;
		    }
		    if (((b & mask) == 0) && ((joyInfo->oldb[ind] & mask) != 0)) {
			joyInfo->edgedn[i + GFCTRL_JOY_MAXBUTTON * ind] = 1;
		    } else {
			joyInfo->edgedn[i + GFCTRL_JOY_MAXBUTTON * ind] = 0;
		    }
		    if ((b & mask) != 0) {
			joyInfo->levelup[i + GFCTRL_JOY_MAXBUTTON * ind] = 1;
		    } else {
			joyInfo->levelup[i + GFCTRL_JOY_MAXBUTTON * ind] = 0;
		    }
		}
		joyInfo->oldb[ind] = b;
	    }
	}
    } else {
	return -1;
    }

    return 0;
}




/** Initialize the mouse control
    @ingroup	ctrl
    @return	pointer on a tCtrlMouseInfo structure
		<br>0 .. if no mouse present
    @note	call GfctrlMouseRelease to free the tCtrlMouseInfo structure
    @see	GfctrlMouseRelease
*/
tCtrlMouseInfo *
GfctrlMouseInit(void)
{
    tCtrlMouseInfo	*mouseInfo = NULL;

    mouseInfo = (tCtrlMouseInfo *)calloc(1, sizeof(tCtrlMouseInfo));

    return mouseInfo;
}

/** Release the tCtrlMouseInfo structure
    @ingroup	ctrl
    @param	mouseInfo	mouse structure
    @return	none
*/
void
GfctrlMouseRelease(tCtrlMouseInfo *mouseInfo)
{
    FREEZ(mouseInfo);
}

static tMouseInfo refMouse;

/** Get the mouse current values
    @ingroup	ctrl
    @param	mouseInfo	mouse structure
    @return	<tt>0 ... </tt>Ok
		<br><tt>-1 .. </tt>Error
    @note	The tCtrlMouseInfo structure is updated with the new values
*/
int
GfctrlMouseGetCurrent(tCtrlMouseInfo *mouseInfo)
{
    float	mouseMove;
    tMouseInfo	*mouse;
    int		i;

    mouse = GfuiMouseInfo();

    mouseMove = (float)(refMouse.X - mouse->X);
    
    if (mouseMove < 0) {
	mouseInfo->ax[1] = -mouseMove;
	mouseInfo->ax[0] = 0;
    } else {
	mouseInfo->ax[0] = mouseMove;
	mouseInfo->ax[1] = 0;
    }
    mouseMove = (float)(refMouse.Y - mouse->Y);
    if (mouseMove < 0) {
	mouseInfo->ax[3] = -mouseMove;
	mouseInfo->ax[2] = 0;
    } else {
	mouseInfo->ax[2] = mouseMove;
	mouseInfo->ax[3] = 0;
    }
    for (i = 0; i < 3; i++) {
	if (mouseInfo->button[i] != mouse->button[i]) {
	    if (mouse->button[i]) {
		mouseInfo->edgedn[i] = 1;
		mouseInfo->edgeup[i] = 0;
	    } else {
		mouseInfo->edgeup[i] = 1;
		mouseInfo->edgedn[i] = 0;
	    }
	    mouseInfo->button[i] = mouse->button[i];
	} else {
	    mouseInfo->edgeup[i] = 0;
	    mouseInfo->edgedn[i] = 0;
	}
    }
    return 0;
}


/** Recentre the mouse on the screen and get the reference position.
    @ingroup	ctrl
    @return	none
*/
void
GfctrlMouseCenter(void)
{
    int sw, sh, vw, vh;

    GfScrGetSize(&sw, &sh, &vw, &vh);
    GfuiMouseSetPos(sw / 2, sh / 2);
}

/** Recentre the mouse on the screen and get the reference position.
    @ingroup	ctrl
    @return	none
*/
void
GfctrlMouseCalibrate(void)
{
    memcpy(&refMouse, GfuiMouseInfo(), sizeof(refMouse));
}
