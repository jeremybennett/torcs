/***************************************************************************

    file                 : grmain.cpp
    created              : Thu Aug 17 23:23:49 CEST 2000
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

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include <plib/ssg.h>

#include <tgf.h>
#include <graphic.h>
#include <racemantools.h>

#include "grmain.h"
#include "grshadow.h"
#include "grskidmarks.h"
#include "grsmoke.h"
#include "grcar.h"
#include "grcam.h"
#include "grscene.h"
#include "grsound.h"
#include "grboard.h"
#include "grutil.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

int grDebugFlag			= 1;
int grBoardFlag			= 1;
int grLeaderFlag		= 1;
int grLeaderNb			= 10;
int grCounterFlag		= 1;
int grGFlag			= 0;
int grDrawCurrent		= 0;

int maxTextureUnits = 0;
static double	OldTime;
static int	nFrame;
static float	Fps;
double		grCurTime;
double		grDeltaTime;
int		segIndice	= 0;

tdble grMaxDammage = 10000.0;
static int grWindowRatio = 0;
int grNbCars = 0;

void *grHandle = NULL;
void *grTrackHandle = NULL;

int grWinx, grWiny, grWinw, grWinh;

tgrCarInfo	*grCarInfo;
ssgContext	grContext;



#ifdef WIN32
#include "win32_glext.h"
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = NULL;
PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB =NULL;
PFNGLACTIVETEXTUREARBPROC   glActiveTextureARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB = NULL;

// InStr
// desc: returns true if searchStr is in str, which is a list of
//       strings separated by spaces
bool InStr(char *searchStr, char *str)
{
	char *extension;			// start of an extension in the list
	char *endOfStr;				// pointer to last string element
	int idx = 0;

	endOfStr = str + strlen(str);	// find the last character in str

	// loop while we haven't reached the end of the string
	while (str < endOfStr)
	{
		// find where a space is located
		idx = strcspn(str, " ");

		// we found searchStr
		if ( (strlen(searchStr) == idx) && (strncmp(searchStr, str, idx) == 0))
		{
			return true;
		}

		// we didn't find searchStr, move pointer to the next string to search
		str += (idx + 1);
	}

	return false;
}
#endif

// InitMultiTex
// desc: sets up OpenGL for multitexturing support
bool InitMultiTex(void)
{
	char *extensionStr;			// list of available extensions
		
	extensionStr = (char*)glGetString(GL_EXTENSIONS);

	if (extensionStr == NULL)
		return false;

	/* printf("glextensionstr: %s\n", extensionStr); */

	if (strstr(extensionStr, "GL_ARB_multitexture"))
	{
		// retrieve the maximum number of texture units allowed
		glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &maxTextureUnits);
		/* printf("\nfound number of texture units : %d\n", maxTextureUnits); */
#ifdef WIN32
		// retrieve addresses of multitexturing functions
		glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) wglGetProcAddress("glMultiTexCoord2fARB");
		glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC) wglGetProcAddress("glActiveTextureARB");
		glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTextureARB");
		glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC) wglGetProcAddress("glMultiTexCoord2fvARB");
#endif
		return true;
	}
	else
		return false;
}

int
initView(int x, int y, int width, int height, int flag, void *screen)
{
    if (maxTextureUnits==0)
      {
	InitMultiTex();    
      }
    switch (flag) {
    case GR_VIEW_STD:
	grScissorflag = 0;
	break;
    case GR_VIEW_PART:
	grScissorflag = 1;
	break;
    }
    grWinx = x;
    grWiny = y;
    grWinw = width;
    grWinh = height;
    grSetView(x, y, width, height);
    grInitBoard();
    OldTime = GfTimeClock();
    nFrame = 0;
    Fps = 0;
    grWindowRatio = 0;

    grHandle = GfParmReadFile(GR_PARAM_FILE, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    grDebugFlag = (int)GfParmGetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_DEBUG,
				    (char*)NULL, grDebugFlag);
    grBoardFlag = (int)GfParmGetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_BOARD,
				    (char*)NULL, grBoardFlag);
    grLeaderFlag = (int)GfParmGetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_LEADER,
				     (char*)NULL, grLeaderFlag);
    grLeaderNb = (int)GfParmGetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_NBLEADER,
				   (char*)NULL, grLeaderNb);
    grCounterFlag = (int)GfParmGetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_COUNTER,
				      (char*)NULL, grCounterFlag);
    grGFlag = (int)GfParmGetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_GGRAPH,
				(char*)NULL, grGFlag);

    GfuiAddSKey(screen, GLUT_KEY_UP,   "Zoom In",          (void*)GR_ZOOM_IN,	grSetZoom);
    GfuiAddSKey(screen, GLUT_KEY_DOWN, "Zoom Out",         (void*)GR_ZOOM_OUT,	grSetZoom);
    GfuiAddSKey(screen, GLUT_KEY_HOME, "Zoom Maximum",     (void*)GR_ZOOM_MAX,	grSetZoom);
    GfuiAddSKey(screen, GLUT_KEY_END,  "Zoom Minimum",     (void*)GR_ZOOM_MIN,	grSetZoom);
    GfuiAddKey(screen, '*',            "Zoom Default",     (void*)GR_ZOOM_DFLT,	grSetZoom);

    GfuiAddSKey(screen, GLUT_KEY_F2,   "Driver Views",      (void*)0, grSelectCamera);
    GfuiAddSKey(screen, GLUT_KEY_F3,   "Car Views",         (void*)1, grSelectCamera);
    GfuiAddSKey(screen, GLUT_KEY_F4,   "Side Car Views",    (void*)2, grSelectCamera);
    GfuiAddSKey(screen, GLUT_KEY_F5,   "Up Car View",       (void*)3, grSelectCamera);
    GfuiAddSKey(screen, GLUT_KEY_F6,   "Persp Car View",    (void*)4, grSelectCamera);
    GfuiAddSKey(screen, GLUT_KEY_F7,   "All Circuit Views", (void*)5, grSelectCamera);
    GfuiAddSKey(screen, GLUT_KEY_F8,   "Track View",        (void*)6, grSelectCamera);
    GfuiAddSKey(screen, GLUT_KEY_F9,   "Track View Zoomed", (void*)7, grSelectCamera);
    GfuiAddSKey(screen, GLUT_KEY_F10,  "Follow Car Zoomed", (void*)8, grSelectCamera);
    GfuiAddSKey(screen, GLUT_KEY_F11,  "TV Director View",  (void*)9, grSelectCamera);

    GfuiAddKey(screen, 'b',            "Driver Board",     (void*)0, grSelectBoard);
    GfuiAddKey(screen, 'c',            "Driver Counters",  (void*)1, grSelectBoard);
    GfuiAddKey(screen, 'l',            "Leaders Board",    (void*)2, grSelectBoard);
    GfuiAddKey(screen, 'f',            "FPS Counter",      (void*)3, grSelectBoard);
    GfuiAddKey(screen, 'g',            "Debug Info",       (void*)4, grSelectBoard);

    grInitScene();

    return 0;
}


int
refresh(tSituation *s)
{
    int			i;
    ssgLight *          light;

    light=ssgGetLight(0);

    nFrame++;
    grCurTime = GfTimeClock();
    grDeltaTime = grCurTime - OldTime;
    if ((grCurTime - OldTime) > 1.0) {
	/* The Frames Per Second (FPS) display is refresh every second */
	Fps = (tdble)nFrame / (grCurTime - OldTime);
	nFrame = 0;
	OldTime = grCurTime;
    }

    TRACE_GL("refresh: start");

    grRefreshSound(s);

    grSetView(scrx, scry, scrw, scrh);

    glDisable(GL_COLOR_MATERIAL);

    grCurCam->update(s->cars[s->current], s);
    glDepthFunc(GL_LEQUAL);
    if (grCurCam->getDrawBackground()) {
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	grDrawBackground(grCurCam);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
    } else {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    grCurCam->action();

    sgVec4 fogColor;
    light->getColour(GL_AMBIENT, fogColor);
    sgScaleVec4(fogColor, 0.8);
    fogColor[3] = 0.5;
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.05);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, ((cGrPerspCamera*)grCurCam)->getFogStart());
    glFogf(GL_FOG_END, ((cGrPerspCamera*)grCurCam)->getFogEnd());
    glEnable(GL_FOG);

    glEnable(GL_LIGHTING);
    for (i = 0; i < s->_ncars; i++) {
      grDrawCar(s->cars[i], s->cars[s->current], grCurCam->getDrawCurrent(), s->currentTime);
    } 
    segIndice = (s->cars[s->current])->_trkPos.seg->id;
    grUpdateSmoke(s->currentTime);

    /*glEnable(GL_DEPTH_TEST);*/
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    grDrawScene();

    glViewport(grWinx, grWiny, grWinw, grWinh);
    grBoardCam->action();

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);    
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);

    TRACE_GL("refresh: glDisable(GL_DEPTH_TEST)");
    if (grDebugFlag)   grDispDebug(Fps, s->cars[s->current], s);
    if (grGFlag)       grDispGGraph(s->cars[s->current]);
    if (grBoardFlag)   grDispCarBoard(s->cars[s->current], s);
    if (grLeaderFlag)  grDispLeaderBoard(s->cars[s->current], s);
    if (grCounterFlag) grDispCounterBoard2(s->cars[s->current]);
    TRACE_GL("refresh: display boards");

    glEnable(GL_LIGHTING);

    return 0;
}

int
initCars(tSituation *s)
{
    char	idx[16];
    int		index;
    int		i;
    tCarElt 	*elt;
    void	*hdle;
    char	buf[256];
    int		camNum;
    cGrCamera	*cam;

    TRACE_GL("initCars: start");

    grHandle = GfParmReadFile(GR_PARAM_FILE, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    grMaxDammage = (tdble)s->_maxDammage;
    grNbCars = s->_ncars;
    grInitCams();
    grCurCamHead = (int)GfParmGetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_CAM_HEAD,
				     (char*)NULL, 9);
    cam = TAILQ_FIRST(&grCams[grCurCamHead]);
    grCurCam = NULL;
    camNum = (int)GfParmGetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_CAM,
			       (char*)NULL, 0);
    while (cam) {
	if (cam->getId() == camNum) {
	    grCurCam = cam;
	    break;
	}
	cam = cam->next();
    }
    if (grCurCam == NULL) {
	/* back to default camera */
	grCurCamHead = 0;
	grCurCam = TAILQ_FIRST(&grCams[grCurCamHead]);
	GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_CAM, (char*)NULL, (tdble)grCurCam->getId());
	GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_CAM_HEAD, (char*)NULL, (tdble)grCurCamHead);    
    }
    sprintf(buf, "%s-%d-%d", GR_ATT_FOVY, grCurCamHead, grCurCam->getId());
    grCurCam->loadDefaults(buf);
    grDrawCurrent = grCurCam->getDrawCurrent();

    grCarInfo = (tgrCarInfo*)calloc(s->_ncars, sizeof(tgrCarInfo));

    for (i = 0; i < s->_ncars; i++) {
	elt = s->cars[i];
	/* Shadow init (Should be done before the cars for display order) */
	grInitShadow(elt);
	/* Skidmarks init */
	grInitSkidmarks(elt);
    }
    
    for (i = 0; i < s->_ncars; i++) {
	elt = s->cars[i];
	index = elt->index;
	hdle = elt->_paramsHandle;
	sprintf(idx, "Robots/index/%d", elt->_driverIndex);
	grCarInfo[index].iconColor[0] = GfParmGetNum(hdle, idx, "red",   (char*)NULL, 0);
	grCarInfo[index].iconColor[1] = GfParmGetNum(hdle, idx, "green", (char*)NULL, 0);
	grCarInfo[index].iconColor[2] = GfParmGetNum(hdle, idx, "blue",  (char*)NULL, 0);
	grCarInfo[index].iconColor[3] = 1.0;
	grInitCar(elt);
    }
    TRACE_GL("initCars: end");

    grInitSmoke(s->_ncars);

    grCustomizePits();

    int nb = grPruneTree(TheScene, true);
    GfOut("PRUNE SSG TREE: removed %d empty branches\n", nb);

    return 0;
    
}

void
shutdownCars(void)
{
    int i;
    
    if (grNbCars) {
	grShutdownSkidmarks();
	grShutdownSmoke();
	/* Delete ssg objects */
	for (i = 0; i < grNbCars; i++) {
	    TheScene->removeKid(grCarInfo[i].carTransform);
	    TheScene->removeKid(grCarInfo[i].shadowAnchor);
	}
	if (grTrack->pits.type == TR_PIT_ON_TRACK_SIDE) TheScene->removeKid(ThePits);
	ThePits = 0;
	free(grCarInfo);
    }
    GfParmReleaseHandle(grHandle);
}

int
initTrack(tTrack *track)
{
    static int firstTime = 1; /* for persistent implementations ??? */
    
    if (firstTime) {
	ssgInit();
	firstTime = 0;
    }

    grContext.makeCurrent();
    grTrackHandle = GfParmReadFile(track->filename, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    grLoadScene(track);
    grInitSound();
    return 0;
}


void
shutdownTrack(void)
{
    grShutdownScene();
    grShutdownBoard();
    grShutdownSound();
}

