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

#include <tgfclient.h>
#include <graphic.h>

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

/* splitted screen */
int winX[4];
int winY[4];
int winW;
int winH;
float winR;
int currCurrent[4] = {0};

int nbScreen = 1;


static char buf[1024];

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

static void
grAdaptScreenSize(void)
{
    switch (nbScreen) {
    case 0:
    case 1:
	winX[0] = grWinx;
	winY[0] = grWiny;
	winW = grWinw;
	winH = grWinh;
	winR = winW / winH;
	break;
    case 2:
	winX[0] = grWinx;
	winY[0] = grWiny + grWinh / 2;
	winW = grWinw;
	winH = grWinh / 2;

	winX[1] = grWinx;
	winY[1] = grWiny;
	winR = winW / winH;
	break;
    case 3:
	winX[0] = grWinx;
	winY[0] = grWiny + grWinh / 2;
	winW = grWinw / 2;
	winH = grWinh / 2;

	winX[1] = grWinx + grWinw / 2;
	winY[1] = grWiny + grWinh / 2;

	winX[2] = grWinx + grWinw / 4;
	winY[2] = grWiny;
	winR = winW / winH;
	break;
    case 4:
	winX[0] = grWinx;
	winY[0] = grWiny + grWinh / 2;
	winW = grWinw / 2;
	winH = grWinh / 2;

	winX[1] = grWinx + grWinw / 2;
	winY[1] = grWiny + grWinh / 2;

	winX[2] = grWinx;
	winY[2] = grWiny;

	winX[3] = grWinx + grWinw / 2;
	winY[3] = grWiny;
	winR = winW / winH;
	break;
    }
}

static void
grSplitScreen(void *vp)
{
    int p = (int)vp;

    switch (p) {
    case GR_SPLIT_ADD:
	nbScreen++;
	if (nbScreen > GR_NB_MAX_SCREEN) {
	    nbScreen = GR_NB_MAX_SCREEN;
	}
	break;
    case GR_SPLIT_REM:
	nbScreen--;
	if (nbScreen < 1) {
	    nbScreen = 1;
	}
	break;
    }
    grAdaptScreenSize();
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
    /* GfuiMouseSetPos(x + width / 2, y + height / 2); */

    grInitBoard();
    OldTime = GfTimeClock();
    nFrame = 0;
    Fps = 0;
    grWindowRatio = 0;

    sprintf(buf, "%s%s", GetLocalDir(), GR_PARAM_FILE);
    grHandle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    grLoadBoardParams();

    GfuiAddSKey(screen, GLUT_KEY_HOME, "Zoom Maximum",     (void*)GR_ZOOM_MAX,	grSetZoom, NULL);
    GfuiAddSKey(screen, GLUT_KEY_END,  "Zoom Minimum",     (void*)GR_ZOOM_MIN,	grSetZoom, NULL);
    GfuiAddKey(screen, '*',            "Zoom Default",     (void*)GR_ZOOM_DFLT,	grSetZoom, NULL);

    GfuiAddSKey(screen, GLUT_KEY_F2,   "Driver Views",      (void*)0, grSelectCamera, NULL);
    GfuiAddSKey(screen, GLUT_KEY_F3,   "Car Views",         (void*)1, grSelectCamera, NULL);
    GfuiAddSKey(screen, GLUT_KEY_F4,   "Side Car Views",    (void*)2, grSelectCamera, NULL);
    GfuiAddSKey(screen, GLUT_KEY_F5,   "Up Car View",       (void*)3, grSelectCamera, NULL);
    GfuiAddSKey(screen, GLUT_KEY_F6,   "Persp Car View",    (void*)4, grSelectCamera, NULL);
    GfuiAddSKey(screen, GLUT_KEY_F7,   "All Circuit Views", (void*)5, grSelectCamera, NULL);
    GfuiAddSKey(screen, GLUT_KEY_F8,   "Track View",        (void*)6, grSelectCamera, NULL);
    GfuiAddSKey(screen, GLUT_KEY_F9,   "Track View Zoomed", (void*)7, grSelectCamera, NULL);
    GfuiAddSKey(screen, GLUT_KEY_F10,  "Follow Car Zoomed", (void*)8, grSelectCamera, NULL);
    GfuiAddSKey(screen, GLUT_KEY_F11,  "TV Director View",  (void*)9, grSelectCamera, NULL);

    GfuiAddKey(screen, '5',            "FPS Counter",      (void*)3, grSelectBoard, NULL);
    GfuiAddKey(screen, '4',            "G/Cmd Graph",      (void*)4, grSelectBoard, NULL);
    GfuiAddKey(screen, '3',            "Leaders Board",    (void*)2, grSelectBoard, NULL);
    GfuiAddKey(screen, '2',            "Driver Counters",  (void*)1, grSelectBoard, NULL);
    GfuiAddKey(screen, '1',            "Driver Board",     (void*)0, grSelectBoard, NULL);
    GfuiAddKey(screen, '0',            "Arcade Board",     (void*)5, grSelectBoard, NULL);
    GfuiAddKey(screen, '>',            "Zoom In",          (void*)GR_ZOOM_IN,	grSetZoom, NULL);
    GfuiAddKey(screen, '<',            "Zoom Out",         (void*)GR_ZOOM_OUT,	grSetZoom, NULL);
    GfuiAddKey(screen, '[',            "Split Screen",     (void*)GR_SPLIT_ADD,	grSplitScreen, NULL);
    GfuiAddKey(screen, ']',            "UnSplit Screen",   (void*)GR_SPLIT_REM,	grSplitScreen, NULL);

    grAdaptScreenSize();

    grInitScene();

    return 0;
}


int
refresh(tSituation *s)
{
    int			i, j, player;
    ssgLight *          light;
    sgVec4		fogColor;

    START_PROFILE("refresh");
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

    START_PROFILE("grRefreshSound*");
    grRefreshSound(s);
    STOP_PROFILE("grRefreshSound*");

    START_PROFILE("grDrawBackground/glClear");
    glDepthFunc(GL_LEQUAL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    STOP_PROFILE("grDrawBackground/glClear");


    if (nbScreen < 2) {
	if (grCurCam->getDrawBackground()) {
	    glDisable(GL_LIGHTING);    
	    grDrawBackground(grCurCam);
	    glEnable(GL_DEPTH_TEST);
	    glClear(GL_DEPTH_BUFFER_BIT);
	} else {
	    glEnable(GL_DEPTH_TEST);
	}

	grSetView(scrx, scry, scrw, scrh);

	glDisable(GL_COLOR_MATERIAL);

	START_PROFILE("grCurCam->update*");
	grCurCam->update(s->cars[s->current], s);
	STOP_PROFILE("grCurCam->update*");

	START_PROFILE("grCurCam->action*");
	grCurCam->action();
	STOP_PROFILE("grCurCam->action*");

	START_PROFILE("grDrawCar*");
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

	for (i = 0; i < s->_ncars; i++) {
	    grDrawCar(s->cars[i], s->cars[s->current], grCurCam->getDrawCurrent(), s->currentTime);
	} 
	/* segIndice = (s->cars[s->current])->_trkPos.seg->id; */
	grUpdateSmoke(s->currentTime);
	STOP_PROFILE("grDrawCar*");

	START_PROFILE("grDrawScene*");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	grDrawScene();
	STOP_PROFILE("grDrawScene*");

	START_PROFILE("grBoardCam*");
	glViewport(grWinx, grWiny, grWinw, grWinh);
	grBoardCam->action();
	STOP_PROFILE("grBoardCam*");

	START_PROFILE("grDisp**");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);    
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);

	TRACE_GL("refresh: glDisable(GL_DEPTH_TEST)");
	grRefreshBoard(s, Fps, 0, s->current);
	TRACE_GL("refresh: display boards");
	STOP_PROFILE("grDisp**");
    } else {
	for (player = 0; player < nbScreen; player++) {
	    grviewRatio = winR;
	    glViewport(winX[player], winY[player], winW, winH);

	    if (s->cars[currCurrent[player]]->_startRank != player) {
		for (j = 0; j < s->_ncars; j++) {
		    if (s->cars[j]->_startRank == player) {
			currCurrent[player] = j;
			break;
		    }
		}
	    }
	    
	    glDisable(GL_COLOR_MATERIAL);

	    START_PROFILE("grCurCam->update*");
	    grCurCam->update(s->cars[currCurrent[player]], s);
	    STOP_PROFILE("grCurCam->update*");

	    if (grCurCam->getDrawBackground()) {
		glDisable(GL_LIGHTING);    
		grDrawBackground(grCurCam);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
	    } else {
		glEnable(GL_DEPTH_TEST);
	    }

	    START_PROFILE("grCurCam->action*");
	    grCurCam->action();
	    STOP_PROFILE("grCurCam->action*");

	    START_PROFILE("grDrawCar*");
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

	    for (i = 0; i < s->_ncars; i++) {
		grDrawCar(s->cars[i], s->cars[currCurrent[player]], grCurCam->getDrawCurrent(), s->currentTime);
	    } 
	    STOP_PROFILE("grDrawCar*");
	
	    /* segIndice = (s->cars[currCurrent[player]])->_trkPos.seg->id; */
	    if (player == 0) {
		grUpdateSmoke(s->currentTime);
	    }

	    START_PROFILE("grDrawScene*");
	    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	    grDrawScene();
	    STOP_PROFILE("grDrawScene*");

	    START_PROFILE("grBoardCam*");
	    //glViewport(grWinx, grWiny, grWinw, grWinh);
	    grBoardCam->action();
	    STOP_PROFILE("grBoardCam*");

	    START_PROFILE("grDisp**");
	    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	    glDisable(GL_CULL_FACE);
	    glDisable(GL_DEPTH_TEST);
	    glDisable(GL_LIGHTING);    
	    glDisable(GL_COLOR_MATERIAL);
	    glDisable(GL_ALPHA_TEST);
	    glDisable(GL_TEXTURE_2D);

	    TRACE_GL("refresh: glDisable(GL_DEPTH_TEST)");
	    grRefreshBoard(s, Fps, 1, currCurrent[player]);
	    TRACE_GL("refresh: display boards");
	    STOP_PROFILE("grDisp**");
	}
    }

    STOP_PROFILE("refresh");
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
    int		camNum;
    cGrCamera	*cam;

    TRACE_GL("initCars: start");

    sprintf(buf, "%s%s", GetLocalDir(), GR_PARAM_FILE);
    grHandle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    grInitCommonState();

    grMaxDammage = (tdble)s->_maxDammage;
    grNbCars = s->_ncars;
    grInitCams();
    grCurCamHead = (int)GfParmGetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_CAM_HEAD,
				     (char*)NULL, 9);
    cam = GF_TAILQ_FIRST(&grCams[grCurCamHead]);
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
	grCurCam = GF_TAILQ_FIRST(&grCams[grCurCamHead]);
	GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_CAM, (char*)NULL, (tdble)grCurCam->getId());
	GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_CAM_HEAD, (char*)NULL, (tdble)grCurCamHead);    
    }
    sprintf(buf, "%s-%d-%d", GR_ATT_FOVY, grCurCamHead, grCurCam->getId());
    grCurCam->loadDefaults(buf);
    grDrawCurrent = grCurCam->getDrawCurrent();

    grCustomizePits();

    grCarInfo = (tgrCarInfo*)calloc(s->_ncars, sizeof(tgrCarInfo));

    for (i = 0; i < s->_ncars; i++) {
	elt = s->cars[i];
	/* Shadow init (Should be done before the cars for display order) */
	grInitShadow(elt);
	/* Skidmarks init */
	grInitSkidmarks(elt);
    }
    
    nbScreen = 0;
    
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
	if (elt->_driverType == RM_DRV_HUMAN) {
	    nbScreen++;
	}
    }
    if (nbScreen > 4) {
	nbScreen = 4;
    }
    TRACE_GL("initCars: end");

    grInitSmoke(s->_ncars);


    //int nb = grPruneTree(TheScene, true);
    //GfOut("PRUNE SSG TREE: removed %d empty branches\n", nb);

    return 0;
    
}

void
shutdownCars(void)
{
    /* int i; */

    GfOut("-- shutdownCars\n");

    if (grNbCars) {
	grShutdownSkidmarks();
	grShutdownSmoke();
	/* Delete ssg objects */
	CarsAnchor->removeAllKids();
	ShadowAnchor->removeAllKids();
	/* for (i = 0; i < grNbCars; i++) { */
	/*     CarsAnchor->removeKid(grCarInfo[i].carTransform); */
	/*     ShadowAnchor->removeKid(grCarInfo[i].shadowAnchor); */
	/* } */
	PitsAnchor->removeAllKids();
	/* if (grTrack->pits.type == TR_PIT_ON_TRACK_SIDE) PitsAnchor->removeKid(ThePits); */
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
    grShutdownState();
}

