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
#include "gui.h"
#include "fg_gm.h"

static int GfScrWidth;
static int GfScrHeight;
static int GfViewWidth;
static int GfViewHeight;
static int GfScrCenX;
static int GfScrCenY;

void	*scrHandle = NULL;
static char buf[1024];

static int usedGM = 0;
#if !defined(FREEGLUT) && !defined(WIN32)
static int usedFG = 0;
#endif

static char	*Res[] = {"640x480", "800x600", "1024x768", "1200x960", "1280x1024", "1600x1200", "320x200"};
static char	*Mode[] = {"Full-screen mode", "Window mode"};
static char	*Depth[] = {"24", "32", "8", "16"};

static const int nbRes = sizeof(Res) / sizeof(Res[0]);
static const int nbMode = sizeof(Mode) / sizeof(Mode[0]);
static const int nbDepth = sizeof(Depth) / sizeof(Depth[0]);

static int	curRes = 0;
static int	curMode = 0;
static int	curDepth = 0;

static int	curMaxFreq = 160;
#if WIN32
static int	MaxFreqId;
#endif

static int	ResLabelId;
static int	DepthLabelId;
static int	ModeLabelId;

static void	*paramHdle;

static float LabelColor[] = {1.0, 0.0, 1.0, 1.0};


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
    int		maxfreq;
    int		i, depth;
    
    sprintf(buf, "%s%s", GetLocalDir(), GFSCR_CONF_FILE);
    handle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    xw = (int)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_X, (char*)NULL, 640);
    yw = (int)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_Y, (char*)NULL, 480);
    winX = (int)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_X, (char*)NULL, xw);
    winY = (int)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_Y, (char*)NULL, yw);
    depth = (int)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_BPP, (char*)NULL, 32);
    maxfreq = (int)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_MAXREFRESH, (char*)NULL, 160);
    GfViewWidth = xw;
    GfViewHeight = yw;
    GfScrCenX = xw / 2;
    GfScrCenY = yw / 2;

#if !defined(FREEGLUT) && !defined(WIN32)
    /* Resize the screen */
    fscr = GfParmGetStr(handle, GFSCR_SECT_PROP, GFSCR_ATT_FSCR, GFSCR_VAL_NO);
    if (strcmp(fscr, GFSCR_VAL_YES) == 0) {
	for (i = 160; i > 59; i--) {
	    sprintf(buf, "%dx%d:%d@%d", winX, winY, depth, i);
	    GfOut("Trying %s mode\n", buf);
	    fglutGameModeString(buf);
	    if (fglutEnterGameMode()) {
		GfOut("OK done for %s\n", buf);
		usedFG = 1;
		break;
	    }
	}
    }
    /* End of resize the screen */
#endif

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    fscr = GfParmGetStr(handle, GFSCR_SECT_PROP, GFSCR_ATT_FSCR, GFSCR_VAL_NO);
    fullscreen = 0;
    if (strcmp(fscr, GFSCR_VAL_YES) == 0) {
	for (i = maxfreq; i > 59; i--) {
	    sprintf(buf, "%dx%d:%d@%d", winX, winY, depth, i);
	    glutGameModeString(buf);
	    if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
		glutEnterGameMode();
		if (glutGameModeGet(GLUT_GAME_MODE_DISPLAY_CHANGED)) {
		    usedGM = 1;
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
	    GfScrShutdown();
	    exit(1);
	}
    }

    if ((strcmp(fscr, GFSCR_VAL_YES) == 0) && (!fullscreen)) {
	/* glutVideoResize(0, 0, winX, winY); */
	glutFullScreen();
    }

    GfParmReleaseHandle(handle);

    glutReshapeFunc( Reshape );
}

/** Shutdown the screen
    @ingroup	screen
    @return	none
*/
void GfScrShutdown(void)
{
    if (usedGM) {
	glutLeaveGameMode();
    }
#if !defined(FREEGLUT) && !defined(WIN32)
    if (usedFG) {
	fglutLeaveGameMode();
    }
#endif
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

static void
saveParams(void)
{
    int x, y, bpp;

    sscanf(Res[curRes], "%dx%d", &x, &y);
    sscanf(Depth[curDepth], "%d", &bpp);

    GfParmSetNum(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_X, (char*)NULL, x);
    GfParmSetNum(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_Y, (char*)NULL, y);
    GfParmSetNum(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_X, (char*)NULL, x);
    GfParmSetNum(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_WIN_Y, (char*)NULL, y);
    GfParmSetNum(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_BPP, (char*)NULL, bpp);
    GfParmSetNum(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_MAXREFRESH, (char*)NULL, curMaxFreq);

    if (curMode == 0) {
	GfParmSetStr(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_FSCR, "yes");
    } else {
	GfParmSetStr(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_FSCR, "no");
    }
    GfParmWriteFile(NULL, paramHdle, "Screen", GFPARM_PARAMETER, "../dtd/params.dtd");
}


void
GfScrReinit(void *dummy)
{
    int retcode;

    saveParams();

#ifdef WIN32
    retcode = execlp("wtorcs.exe", "torcs", (const char *)NULL);
#else
    GfScrShutdown();

    if (strlen(GetLocalDir()) == 0) {
	if (GfuiMouseHW) {
	    retcode = execlp("./torcs", "torcs", "-m", (const char *)NULL);
	} else {
	    retcode = execlp("./torcs", "torcs", (const char *)NULL);
	}
    } else {
	if (GfuiMouseHW) {
	    retcode = execlp("./torcs", buf, "-l", GetLocalDir(), "-m", (const char *)NULL);
	} else {
	    retcode = execlp("./torcs", buf, "-l", GetLocalDir(), (const char *)NULL);
	}
    }
#endif
    if (retcode) {
	perror("torcs");
	exit(1);
    }
}

static void
updateLabelText(void)
{
    GfuiLabelSetText (scrHandle, ResLabelId, Res[curRes]);
    GfuiLabelSetText (scrHandle, DepthLabelId, Depth[curDepth]);
    GfuiLabelSetText (scrHandle, ModeLabelId, Mode[curMode]);
#if WIN32
    sprintf(buf, "%d", curMaxFreq);
    GfuiEditboxSetString(scrHandle, MaxFreqId, buf);
#endif
}

static void
ResPrevNext(void *vdelta)
{
    int delta = (int)vdelta;

    curRes += delta;
    if (curRes < 0) {
	curRes = nbRes - 1;
    } else {
	if (curRes >= nbRes) {
	    curRes = 0;
	}
    }
    updateLabelText();
}

static void
DepthPrevNext(void *vdelta)
{
    int delta = (int)vdelta;

    curDepth += delta;
    if (curDepth < 0) {
	curDepth = nbDepth - 1;
    } else {
	if (curDepth >= nbDepth) {
	    curDepth = 0;
	}
    }
    updateLabelText();
}

static void
ModePrevNext(void *vdelta)
{
    int delta = (int)vdelta;

    curMode += delta;
    if (curMode < 0) {
	curMode = nbMode - 1;
    } else {
	if (curMode >= nbMode) {
	    curMode = 0;
	}
    }
    updateLabelText();
}

static void
initFromConf(void)
{
    int x, y, bpp;
    int i;

    x = (int)GfParmGetNum(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_X, NULL, 640);
    y = (int)GfParmGetNum(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_Y, NULL, 480);

    sprintf(buf, "%dx%d", x, y);
    for (i = 0; i < nbRes; i++) {
	if (!strcmp(buf, Res[i])) {
	    curRes = i;
	    break;
	}
    }

    if (!strcmp("yes", GfParmGetStr(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_FSCR, "yes"))) {
	curMode = 0;
    } else {
	curMode = 1;
    }

    bpp = (int)GfParmGetNum(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_BPP, NULL, 24);
    sprintf(buf, "%d", bpp);
    for (i = 0; i < nbDepth; i++) {
	if (!strcmp(buf, Depth[i])) {
	    curDepth = i;
	    break;
	}
    }

    curMaxFreq = (int)GfParmGetNum(paramHdle, GFSCR_SECT_PROP, GFSCR_ATT_MAXREFRESH, NULL, curMaxFreq);
}

#if WIN32
static void
ChangeMaxFreq(void *dummy)
{
    char	*val;
    
    val = GfuiEditboxGetString(scrHandle, MaxFreqId);
    curMaxFreq = (int)strtol(val, (char **)NULL, 0);
    sprintf(buf, "%d", curMaxFreq);
    GfuiEditboxSetString(scrHandle, MaxFreqId, buf);
}
#endif

static void
onActivate(void *dummy)
{
    initFromConf();
    updateLabelText();
}


/** Create and activate the video options menu screen.
    @ingroup	screen
    @param	precMenu	previous menu to return to
*/
void *
GfScrMenuInit(void *precMenu)
{
    int		y, x1, x2;
    
    sprintf(buf, "%s%s", GetLocalDir(), GFSCR_CONF_FILE);
    paramHdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    if (scrHandle) return scrHandle;

    scrHandle = GfuiScreenCreateEx((float*)NULL, NULL, onActivate, NULL, (tfuiCallback)NULL, 1);
    GfuiTitleCreate(scrHandle, "Screen configuration", 0);
    GfuiScreenAddBgImg(scrHandle, "data/img/splash-graphic.png");

    x1 = 200;
    x2 = 440;
    y = 400;
    GfuiLabelCreate(scrHandle,
		    "Screen Resolution",
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
		       (void*)-1, ResPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    ResLabelId = GfuiLabelCreate(scrHandle,
				 "",
				 GFUI_FONT_LARGE_C,
				 320, y, GFUI_ALIGN_HC_VB,
				 30);
    GfuiLabelSetColor(scrHandle, ResLabelId, LabelColor);

    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right-pushed.png",
		       x2, y, GFUI_ALIGN_HC_VB, 0,
		       (void*)1, ResPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    y -= 60;
    GfuiLabelCreate(scrHandle,
		    "Color Depth",
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
		       (void*)-1, DepthPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    DepthLabelId = GfuiLabelCreate(scrHandle,
				   "",
				   GFUI_FONT_LARGE_C,
				   320, y, GFUI_ALIGN_HC_VB,
				   30);
    GfuiLabelSetColor(scrHandle, DepthLabelId, LabelColor);

    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right-pushed.png",
		       x2, y, GFUI_ALIGN_HC_VB, 0,
		       (void*)1, DepthPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    y -= 60;
    GfuiLabelCreate(scrHandle,
		    "Display Mode",
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
		       (void*)-1, ModePrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    ModeLabelId = GfuiLabelCreate(scrHandle,
				  "",
				  GFUI_FONT_LARGE_C,
				  320, y, GFUI_ALIGN_HC_VB,
				  30);
    GfuiLabelSetColor(scrHandle, ModeLabelId, LabelColor);

    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right-pushed.png",
		       x2, y, GFUI_ALIGN_HC_VB, 0,
		       (void*)1, ModePrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

#if WIN32
    y -= 60;
    GfuiLabelCreate(scrHandle,
		    "Max Frequency",
		    GFUI_FONT_LARGE,
		    320, y, GFUI_ALIGN_HC_VB,
		    0);   
    y -= 30;
    MaxFreqId = GfuiEditboxCreate(scrHandle, "", GFUI_FONT_MEDIUM_C,
				   275, y, 0, 8, NULL, (tfuiCallback)NULL, ChangeMaxFreq);
#endif

    GfuiAddKey(scrHandle, 13, "Apply Mode", NULL, GfScrReinit, NULL);
    GfuiButtonCreate(scrHandle, "Apply", GFUI_FONT_LARGE, 210, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, GfScrReinit, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiAddKey(scrHandle, 27, "Cancel", precMenu, GfuiScreenActivate, NULL);
    GfuiButtonCreate(scrHandle, "Back", GFUI_FONT_LARGE, 430, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     precMenu, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
 
    return scrHandle;
}



