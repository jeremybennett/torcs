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

#include <tgfclient.h>
#include "gui.h"
#include "fg_gm.h"

static int GfScrWidth;
static int GfScrHeight;
static int GfViewWidth;
static int GfViewHeight;
static int GfScrCenX;
static int GfScrCenY;

static void	*scrHandle = NULL;
static char 	buf[1024];

static int usedGM = 0;
#if !defined(FREEGLUT) && !defined(WIN32)
static int usedFG = 0;
#endif

static char	*Res[] = {"640x480", "800x600", "1024x768", "1152x864", "1200x960", "1280x1024", "1600x1200", "320x200"};
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

    glutInit(&argc, argv);

	// Try to get "best" videomode, z-buffer >= 24bit, visual with alpha channel,
	// antialiasing support.

	int visualDepthBits = 24;
	bool visualSupportsMultisample = true;
	bool visualSupportsAlpha = true;

	glutInitDisplayString("rgba double depth>=24 samples alpha");

	if (!glutGet(GLUT_DISPLAY_MODE_POSSIBLE)) {
		// Failed, try without antialiasing support.
		visualDepthBits = 24;
		visualSupportsMultisample = false;
		visualSupportsAlpha = true;
		glutInitDisplayString("rgba double depth>=24 alpha");
	}

	if (!glutGet(GLUT_DISPLAY_MODE_POSSIBLE)) {
		// Failed, try without alpha channel.
		visualDepthBits = 24;
		visualSupportsMultisample = true;
		visualSupportsAlpha = false;
		glutInitDisplayString("rgb double depth>=24 samples");
	}

	if (!glutGet(GLUT_DISPLAY_MODE_POSSIBLE)) {
		// Failed, try without antialiasing and alpha support.
		visualDepthBits = 24;
		visualSupportsMultisample = false;
		visualSupportsAlpha = false;
		glutInitDisplayString("rgb double depth>=24");
	}

	if (!glutGet(GLUT_DISPLAY_MODE_POSSIBLE)) {
		// Failed, try without 24 bit z-Buffer and without antialiasing.
		visualDepthBits = 16;
		visualSupportsMultisample = false;
		visualSupportsAlpha = true;
		glutInitDisplayString("rgba double depth>=16 alpha");
	}

	if (!glutGet(GLUT_DISPLAY_MODE_POSSIBLE)) {
		// Failed, try without 24 bit z-Buffer, without antialiasing and without alpha.
		visualDepthBits = 16;
		visualSupportsMultisample = false;
		visualSupportsAlpha = false;
		glutInitDisplayString("rgb double depth>=16");
	}

	printf("Visual Properties Report\n");
	printf("------------------------\n");

	if (!glutGet(GLUT_DISPLAY_MODE_POSSIBLE)) {
		// All failed.
		printf("The minimum display requirements are not fulfilled.\n");
		printf("We need a double buffered RGBA visual with a 16 bit depth buffer at least.\n");
	} else {
		// We have got a mode, report the properties.
		printf("z-buffer depth: %d\n", visualDepthBits);
		printf("alpha channel : %s\n", visualSupportsAlpha ? "enabled" : "disabled");
		printf("antialiasing  : %s\n", visualSupportsMultisample ? "enabled" : "disabled");
		if (visualDepthBits < 24) {
			// Show a hint if the z-buffer depth is not optimal.
			printf("The z-buffer resolution is below 24 bit, you will experience rendering\n");
			printf("artefacts. Try to improve the setup of your graphics board or look\n");
			printf("for an alternate driver.\n");
		}
	}

    fscr = GfParmGetStr(handle, GFSCR_SECT_PROP, GFSCR_ATT_FSCR, GFSCR_VAL_NO);
    fullscreen = 0;
    if (strcmp(fscr, GFSCR_VAL_YES) == 0) {
#if !defined(FREEGLUT) && !defined(WIN32)
    /* Resize the screen */
	GfOut ("Freeglut not detected...\n");
	for (i = maxfreq; i > 59; i--) {
	    sprintf(buf, "%dx%d:%d@%d", winX, winY, depth, i);
	    GfOut("Trying %s mode\n", buf);
	    fglutGameModeString(buf);
	    if (fglutEnterGameMode()) {
		GfOut("OK done for %s\n", buf);
		usedFG = 1;
		break;
	    }
	}
#endif
	for (i = maxfreq; i > 59; i--) {
	    sprintf(buf, "%dx%d:%d@%d", winX, winY, depth, i);
	    glutGameModeString(buf);
	    GfOut("2 - Trying %s mode\n", buf);
	    if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
		GfOut("2- %s mode Possible\n", buf);
		glutEnterGameMode();
		if (glutGameModeGet(GLUT_GAME_MODE_DISPLAY_CHANGED)) {
		    GfOut("Use GameMode %s\n", buf);
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
    GfParmWriteFile(NULL, paramHdle, "Screen");
}


void
GfScrReinit(void * /* dummy */)
{
    int retcode = 0;
#ifndef WIN32
    char	cmd[1024];
    char	*arg[8];
    int		curArg;
#endif

    saveParams();

#ifdef WIN32
    retcode = execlp("wtorcs.exe", "torcs", (const char *)NULL);
#else
    GfScrShutdown();

    sprintf (cmd, "%storcs-bin", GetLibDir ());
    memset (arg, 0, sizeof (arg));
    curArg = 0;
    if (GfuiMouseHW) {
	arg[curArg++] = "-m";
    }
    
    if (strlen(GetLocalDir ())) {
	arg[curArg++] = "-l";
	arg[curArg++] = GetLocalDir ();
    }

    if (strlen(GetLibDir ())) {
	arg[curArg++] = "-L";
	arg[curArg++] = GetLibDir ();
    }

    if (strlen(GetDataDir ())) {
	arg[curArg++] = "-D";
	arg[curArg++] = GetDataDir ();
    }

    switch (curArg) {
    case 0:
	retcode = execlp (cmd, cmd, (const char *)NULL);
	break;
    case 1:
	retcode = execlp (cmd, cmd, arg[0], (const char *)NULL);
	break;
    case 2:
	retcode = execlp (cmd, cmd, arg[0], arg[1], (const char *)NULL);
	break;
    case 3:
	retcode = execlp (cmd, cmd, arg[0], arg[1], arg[2], (const char *)NULL);
	break;
    case 4:
	retcode = execlp (cmd, cmd, arg[0], arg[1], arg[2], arg[3], (const char *)NULL);
	break;
    case 5:
	retcode = execlp (cmd, cmd, arg[0], arg[1], arg[2], arg[3], arg[4], (const char *)NULL);
	break;
    case 6:
	retcode = execlp (cmd, cmd, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], (const char *)NULL);
	break;
    case 7:
	retcode = execlp (cmd, cmd, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], (const char *)NULL);
	break;
    case 8:
	retcode = execlp (cmd, cmd, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], (const char *)NULL);
	break;
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
    long delta = (long)vdelta;

    curRes += (int)delta;
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
    long delta = (long)vdelta;

    curDepth += (int)delta;
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
    long delta = (long)vdelta;

    curMode += (int)delta;
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
ChangeMaxFreq(void * /* dummy */)
{
    char	*val;
    
    val = GfuiEditboxGetString(scrHandle, MaxFreqId);
    curMaxFreq = (int)strtol(val, (char **)NULL, 0);
    sprintf(buf, "%d", curMaxFreq);
    GfuiEditboxSetString(scrHandle, MaxFreqId, buf);
}
#endif

static void
onActivate(void * /* dummy */)
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
    GfuiAddSKey(scrHandle, GLUT_KEY_LEFT, "Previous Resolution", (void*)-1, ResPrevNext, NULL);

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
    GfuiAddSKey(scrHandle, GLUT_KEY_RIGHT, "Next Resolution", (void*)1, ResPrevNext, NULL);

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
    GfuiAddKey(scrHandle, 'f', "Display Mode", (void*)1, ModePrevNext, NULL);

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



int GfuiGlutExtensionSupported(char *str)
{
    return glutExtensionSupported(str);
}
