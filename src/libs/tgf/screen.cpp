/***************************************************************************
                           screen.cpp -- screen init                           
                             -------------------                                         
    created              : Fri Aug 13 22:29:56 CEST 1999
    copyright            : (C) 1999, 2002 by Eric Espie                         
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

/** @file   
    Screen management.
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
    @ingroup	screen
*/

#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include <math.h>
#ifndef WIN32
#include <unistd.h>
#else
#include <process.h>
#endif /* WIN32 */

#include <tgf.h>

#ifdef DMALLOC
#include "dmalloc.h"
#endif

static int GfScrWidth;
static int GfScrHeight;
static int GfViewWidth;
static int GfViewHeight;
static int GfScrCenX;
static int GfScrCenY;

void
gfScreenInit(void)
{
}

static void Reshape(int width, int height)
{
    glViewport( (width-GfViewWidth)/2, (height-GfViewHeight)/2, GfViewWidth,  GfViewHeight);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, 640.0, 0.0, 480.0, -1.0, 1.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    GfScrWidth = width;
    GfScrHeight = height;
    GfScrCenX = width / 2;
    GfScrCenY = height / 2;
}

void GfScrInit(int argc, char *argv[])
{
    int		Window;
    int		xw, yw;
    int		winX, winY;
    void	*handle;
    char	*fscr;
    int		fullscreen;
    static char	buf[256];
    int		i;
    
    
    handle = GfParmReadFile(GFSCR_CONF_FILE, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    xw = (int)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_X, (char*)NULL, 640);
    yw = (int)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_Y, (char*)NULL, 480);
    winX = (int)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_X, (char*)NULL, xw);
    winY = (int)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_Y, (char*)NULL, yw);
    GfViewWidth = xw;
    GfViewHeight = yw;
    GfScrCenX = xw / 2;
    GfScrCenY = yw / 2;
    
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    fscr = GfParmGetStr(handle, GFSCR_SECT_PROP, GFSCR_ATT_FSCR, GFSCR_VAL_NO);
    fullscreen = 0;
    if (strcmp(fscr, GFSCR_VAL_YES) == 0) {
	for (i = 160; i > 49; i--) {
	    sprintf(buf, "%dx%d:32@%d", winX, winY, i);
	    glutGameModeString(buf);
	    if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
		glutEnterGameMode();
		if (glutGameModeGet(GLUT_GAME_MODE_DISPLAY_CHANGED)) {
		    fullscreen = 1;
		    break;
		} else {
		    glutLeaveGameMode();
		}
	    }
	}
    }

    if (!fullscreen) {
	/* Give an initial size and position so user doesn't have to place window */
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(winX, winY);
	Window = glutCreateWindow(argv[0]);
	if (!Window) {
	    printf("Error, couldn't open window\n");
	    exit(1);
	}
    }

    if ((strcmp(fscr, GFSCR_VAL_YES) == 0) && (!fullscreen)) {
	/* glutFullScreen(); */
    }
    GfParmReleaseHandle(handle);

    glutReshapeFunc( Reshape );
}
/** Get the screen and viewport sizes.
    @ingroup	screen
    @param	scrw	address of screen with
    @param	scrh	address of screen height
    @param	vieww	address of viewport with
    @param	viewh	address of viewport height
    @return	none
 */
void GfScrGetSize(int *scrw, int *scrh, int *vieww, int *viewh)
{
    *scrw = GfScrWidth;
    *scrh = GfScrHeight;
    *vieww = GfViewWidth;
    *viewh = GfViewHeight;
}

void
GfScrReinit(void *dummy)
{
#ifdef WIN32
    if (execlp("wtorcs.exe", "torcs", (const char *)NULL)) {
#else
	if (execlp("./torcs", "torcs", (const char *)NULL)) {
#endif
	    perror("torcs");
	    exit(1);
#ifdef WIN32
	}
#else
    }
#endif    
}


static void
chgScreenType(void *p)
{
    void	*handle;
    int i = (int)p;
    
    handle = GfParmReadFile(GFSCR_CONF_FILE, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    switch(i){
    case 0:
	GfParmSetStr(handle, GFSCR_SECT_PROP, GFSCR_ATT_FSCR, "yes");
	break;
    case 1:
	GfParmSetStr(handle, GFSCR_SECT_PROP, GFSCR_ATT_FSCR, "no");
	break;
    }
    GfParmWriteFile(GFSCR_CONF_FILE, handle, "Screen", GFPARM_PARAMETER, "../dtd/params.dtd");
    GfParmReleaseHandle(handle);

    GfScrReinit();
}

static void
chgScreenSize(void *p)
{
    void	*handle;
    int i = (int)p;
    
    handle = GfParmReadFile(GFSCR_CONF_FILE, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    switch(i){
    case 0:
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_X, (char*)NULL, 320);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_Y, (char*)NULL, 200);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_X, (char*)NULL, 320);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_Y, (char*)NULL, 200);
	break;
    case 1:
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_X, (char*)NULL, 640);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_Y, (char*)NULL, 480);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_X, (char*)NULL, 640);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_Y, (char*)NULL, 480);
	break;
    case 2:
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_X, (char*)NULL, 800);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_Y, (char*)NULL, 600);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_X, (char*)NULL, 800);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_Y, (char*)NULL, 600);
	break;
    case 3:
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_X, (char*)NULL, 1024);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_Y, (char*)NULL, 768);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_X, (char*)NULL, 1024);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_Y, (char*)NULL, 768);
	break;
    case 4:
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_X, (char*)NULL, 1200);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_Y, (char*)NULL, 960);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_X, (char*)NULL, 1200);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_Y, (char*)NULL, 960);
	break;
    case 5:
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_X, (char*)NULL, 1280);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_Y, (char*)NULL, 1024);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_X, (char*)NULL, 1280);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_Y, (char*)NULL, 1024);
	break;
    case 6:
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_X, (char*)NULL, 1600);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_Y, (char*)NULL, 1200);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_X, (char*)NULL, 1600);
	GfParmSetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_Y, (char*)NULL, 1200);
	break;
    }
    GfParmWriteFile(GFSCR_CONF_FILE, handle, "Screen", GFPARM_PARAMETER, "../dtd/params.dtd");
    GfParmReleaseHandle(handle);

    GfScrReinit();
}


/** Create and activate the video options menu screen.
    @ingroup	screen
    @param	precMenu	previous menu to return to
*/
void *
GfScrMenuInit(void *precMenu)
{
    void	*menuHdle;
    void	*paramHdle;
    char	*fullscreen;
    

    menuHdle = GfuiMenuScreenCreate("Screen configuration");
    GfuiScreenAddBgImg(menuHdle, "data/img/splash-graphic.png");

    GfuiMenuButtonCreate(menuHdle, "320x200", "Relaunch TORCS in 320x200 mode", (void*)0, chgScreenSize);
    GfuiMenuButtonCreate(menuHdle, "640x480", "Relaunch TORCS in 640x480 mode", (void*)1, chgScreenSize);
    GfuiMenuButtonCreate(menuHdle, "800x600", "Relaunch TORCS in 800x600 mode", (void*)2, chgScreenSize);
    GfuiMenuButtonCreate(menuHdle, "1024x768", "Relaunch TORCS in 1024x768 mode", (void*)3, chgScreenSize);
    GfuiMenuButtonCreate(menuHdle, "1200x960", "Relaunch TORCS in 1200x960 mode", (void*)4, chgScreenSize);
    GfuiMenuButtonCreate(menuHdle, "1280x1024", "Relaunch TORCS in 1280x1024 mode", (void*)5, chgScreenSize);
    GfuiMenuButtonCreate(menuHdle, "1600x1200", "Relaunch TORCS in 1600x1200 mode", (void*)6, chgScreenSize);

    paramHdle = GfParmReadFile(GFSCR_CONF_FILE, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    fullscreen = GfParmGetStr(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_FSCR, GFSCR_VAL_NO);
    if (strcmp(fullscreen, GFSCR_VAL_NO) == 0) {
	GfuiMenuButtonCreate(menuHdle, "Full-screen mode", "Relaunch TORCS in full-screen mode", (void*)0, chgScreenType);
	GfuiEnable(menuHdle, GfuiMenuButtonCreate(menuHdle, "Window mode", "Relaunch TORCS in window mode",
						  (void*)1, chgScreenType),
		   GFUI_DISABLE);
    } else {
	GfuiEnable(menuHdle, GfuiMenuButtonCreate(menuHdle, "Full-screen mode", "Relaunch TORCS in full-screen mode",
						  (void*)0, chgScreenType),
		   GFUI_DISABLE);
	GfuiMenuButtonCreate(menuHdle, "Window mode", "Relaunch TORCS in window mode", (void*)1, chgScreenType);
    }
    GfParmReleaseHandle(paramHdle);
 
    GfuiMenuBackQuitButtonCreate(menuHdle, "Back", "", precMenu, GfuiScreenActivate);
 
    return menuHdle;
}

/** Convert a time in seconds (float) to an ascii string.
    @ingroup	screen
    @param	sec	Time to convert
    @param	sgn	Flag to indicate if the sign (+) is to be displayed for positive values of time.
    @return	Time string.
    @warning	The returned string has to be free by the caller.
 */
char * 
GfTime2Str(tdble sec, int sgn)
{
    char  buf[256];
    char* sign;

    if (sec < 0.0) {
	sec = -sec;
	sign = "-";
    } else {
	if (sgn) {
	    sign = "+";
	} else {
	    sign = "  ";
	}
    }
    int h = (int)(sec / 3600.0);
    sec -= 3600 * h;
    int m = (int)(sec / 60.0);
    sec -= 60 * m;
    int s = (int)(sec);
    sec -= s;
    int c = (int)floor((sec) * 100.0);
    if (h) {
	(void)sprintf(buf, "%s%2.2d:%2.2d:%2.2d:%2.2d", sign,h,m,s,c);
    } else if (m) {
	(void)sprintf(buf, "   %s%2.2d:%2.2d:%2.2d", sign,m,s,c);
    } else {
	(void)sprintf(buf, "      %s%2.2d:%2.2d", sign,s,c);
    }
    return strdup(buf);
}



