/***************************************************************************

    file        : grscreen.cpp
    created     : Thu May 15 22:11:03 CEST 2003
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

#include <plib/ssg.h>

#include <tgfclient.h>
#include "grutil.h"
#include "grmain.h"
#include "grscene.h"
#include "grshadow.h"
#include "grskidmarks.h"
#include "grcar.h"
#include "grboard.h"


#include "grscreen.h"

static char buf[1024];
static char path[1024];
static char path2[1024];

cGrScreen::cGrScreen(int myid)
{
    id = myid;
    curCar = NULL;
    curCam = NULL;
    mirrorCam = NULL;
    dispCam = NULL;
    boardCam = NULL;
    bgCam = NULL;
    board = NULL;
    curCamHead = 0;
    drawCurrent = 0;
    active = 0;
    selectNextFlag = 0;
    selectPrevFlag = 0;
    memset(cams, 0, sizeof(cams));
    viewRatio = 1.33;
}

cGrScreen::~cGrScreen()
{
    int			i;
    class cGrCamera	*cam;

    for (i = 0; i < 10; i++) {
	while ((cam =  GF_TAILQ_FIRST(&cams[i])) != 0) {
	    cam->remove(&cams[i]);
	    delete cam;
	}
    }

    board->shutdown ();
    delete board;
}

int cGrScreen::isInScreen(int x, int y)
{
    if (!active) {
	return 0;
    }
    
    if ((x >= scrx) &&
	(y >= scry) &&
	(x < (scrx + scrw)) &&
	(y < (scry + scrh))) {
	return 1;
    }
    return 0;
}

void cGrScreen::setCurrentCar(tCarElt *newCurCar)
{
    curCar = newCurCar;
}

/* Set Screen size & position */
void cGrScreen::activate(int x, int y, int w, int h)
{
    viewRatio = (float)w / (float)h;

    if (viewRatio > 2.3) viewRatio = 2.3;
    
    scrx = x;
    scry = y;
    scrw = w;
    scrh = h;

    active = 1;
}

void cGrScreen::desactivate(void)
{
    active = 0;
}

/* Set camera zoom value */
void cGrScreen::setZoom(int zoom) 
{
    curCam->setZoom(zoom);
}

void cGrScreen::selectNextCar(void)
{
    selectNextFlag = 1;
}

void cGrScreen::selectPrevCar(void)
{
    selectPrevFlag = 1;
}

void cGrScreen::selectBoard(int brd)
{
    board->selectBoard(brd);
}

/* Select the camera by number */
void cGrScreen::selectCamera(int cam)
{
    if (cam == curCamHead) {
	/* Same camera list, choose the next one */
	curCam = curCam->next();
	if (curCam == (cGrPerspCamera*)GF_TAILQ_END(&cams[cam])) {
	    curCam = (cGrPerspCamera*)GF_TAILQ_FIRST(&cams[cam]);
	}
    } else {
	/* Change of camera list, take the first one */
	curCamHead = cam;
	curCam = (cGrPerspCamera*)GF_TAILQ_FIRST(&cams[cam]);
    }
    if (curCam == NULL) {
	/* back to default camera */
	curCamHead = 0;
	curCam = (cGrPerspCamera*)GF_TAILQ_FIRST(&cams[curCamHead]);
    }
    sprintf(path, "%s/%d", GR_SCT_DISPMODE, id);
    GfParmSetStr(grHandle, path, GR_ATT_CUR_DRV, curCar->_name);
    GfParmSetNum(grHandle, path, GR_ATT_CAM, (char*)NULL, (tdble)curCam->getId());
    GfParmSetNum(grHandle, path, GR_ATT_CAM_HEAD, (char*)NULL, (tdble)curCamHead);

    /* save also as user's preference if human */
    if (curCar->_driverType == RM_DRV_HUMAN) {
	sprintf(path2, "%s/%s", GR_SCT_DISPMODE, curCar->_name);
	GfParmSetNum(grHandle, path2, GR_ATT_CAM, (char*)NULL, (tdble)curCam->getId());
	GfParmSetNum(grHandle, path2, GR_ATT_CAM_HEAD, (char*)NULL, (tdble)curCamHead);
    }

    sprintf(buf, "%s-%d-%d", GR_ATT_FOVY, curCamHead, curCam->getId());
    curCam->loadDefaults(buf);
    drawCurrent = curCam->getDrawCurrent();
    GfParmWriteFile(NULL, grHandle, "Graph", GFPARM_PARAMETER, "../dtd/params.dtd");
}

void cGrScreen::camDraw(tSituation *s)
{
    int		i;

    glDisable(GL_COLOR_MATERIAL);

    START_PROFILE("dispCam->update*");
    dispCam->update(curCar, s);
    STOP_PROFILE("dispCam->update*");

    if (dispCam->getDrawBackground()) {
	glDisable(GL_LIGHTING);    
	grDrawBackground(dispCam, bgCam);
	glClear(GL_DEPTH_BUFFER_BIT);
    }
    glEnable(GL_DEPTH_TEST);

    START_PROFILE("dispCam->action*");
    dispCam->action();
    STOP_PROFILE("dispCam->action*");

    START_PROFILE("grDrawCar*");
    glFogf(GL_FOG_START, dispCam->getFogStart());
    glFogf(GL_FOG_END, dispCam->getFogEnd());
    glEnable(GL_FOG);

    for (i = 0; i < s->_ncars; i++) {
	/* FIXME: sort the cars by distance for transparent windows */
	grDrawCar(s->cars[i], curCar, dispCam->getDrawCurrent(), s->currentTime, dispCam);
    } 
    STOP_PROFILE("grDrawCar*");
	
    START_PROFILE("grDrawScene*");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    grDrawScene();
    STOP_PROFILE("grDrawScene*");
}


/* Update screen display */
void cGrScreen::update(tSituation *s, float Fps)
{
    int		i;
    ssgLight	*light;

    if (!active) {
	return;
    }

    if (selectNextFlag) {
	for (i = 0; i < (s->_ncars - 1); i++) {
	    if (curCar == s->cars[i]) {
		curCar = s->cars[i + 1];
		curCar->priv.collision = 0;
		break;
	    }
	}
	sprintf(path, "%s/%d", GR_SCT_DISPMODE, id);
	GfParmSetStr(grHandle, path, GR_ATT_CUR_DRV, curCar->_name);
	GfParmWriteFile(NULL, grHandle, "Graph", GFPARM_PARAMETER, "../dtd/params.dtd");
	selectNextFlag = 0;
    }
    if (selectPrevFlag) {
	for (i = 1; i < s->_ncars; i++) {
	    if (curCar == s->cars[i]) {
		curCar = s->cars[i - 1];
		curCar->priv.collision = 0;
		break;
	    }
	}
	sprintf(path, "%s/%d", GR_SCT_DISPMODE, id);
	GfParmSetStr(grHandle, path, GR_ATT_CUR_DRV, curCar->_name);
	GfParmWriteFile(NULL, grHandle, "Graph", GFPARM_PARAMETER, "../dtd/params.dtd");
	selectPrevFlag = 0;
    }


    light = ssgGetLight (0);

    glViewport(scrx, scry, scrw, scrh);

    dispCam = curCam;
    camDraw(s);

#if MIRROR
    if (curCam->isMirrorAllowed()) {
	glViewport(scrx + scrw / 4, scry +  5 * scrh / 6 - scrh / 10, scrw / 2, scrh / 6);
	dispCam = mirrorCam;
	glClear(GL_DEPTH_BUFFER_BIT);
	camDraw(s);
	glViewport(scrx, scry, scrw, scrh);
    }
#endif

    START_PROFILE("boardCam*");
    boardCam->action();
    STOP_PROFILE("boardCam*");

    START_PROFILE("grDisp**");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);    
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_FOG);

    TRACE_GL("cGrScreen::update glDisable(GL_DEPTH_TEST)");
    board->refreshBoard(s, Fps, 0, curCar);
    TRACE_GL("cGrScreen::update display boards");

    STOP_PROFILE("grDisp**");
}

void cGrScreen::loadParams(tSituation *s)
{
    int			camNum;
    int			i;
    class cGrCamera	*cam;
    char		*carName;

    sprintf(path, "%s/%d", GR_SCT_DISPMODE, id);
    if (curCar) {
	sprintf(path2, "%s/%s", GR_SCT_DISPMODE, curCar->_name);
    }
    
    curCamHead = (int)GfParmGetNum(grHandle, path, GR_ATT_CAM_HEAD, NULL, 9);
    if (curCar) {
	curCamHead = (int)GfParmGetNum(grHandle, path2, GR_ATT_CAM_HEAD, NULL, (tdble)curCamHead);
    }

    cam = GF_TAILQ_FIRST(&cams[curCamHead]);
    curCam = NULL;
    camNum = (int)GfParmGetNum(grHandle, path, GR_ATT_CAM, NULL, 0);
    if (curCar) {
	camNum = (int)GfParmGetNum(grHandle, path2, GR_ATT_CAM, NULL, (tdble)camNum);
    }

    while (cam) {
	if (cam->getId() == camNum) {
	    curCam = (cGrPerspCamera*)cam;
	    break;
	}
	cam = cam->next();
    }
    if (curCam == NULL) {
	/* back to default camera */
	curCamHead = 0;
	curCam = (cGrPerspCamera*)GF_TAILQ_FIRST(&cams[curCamHead]);
	GfParmSetNum(grHandle, path, GR_ATT_CAM, NULL, (tdble)curCam->getId());
	GfParmSetNum(grHandle, path, GR_ATT_CAM_HEAD, NULL, (tdble)curCamHead);
    }

    if (!curCar) {
	carName = GfParmGetStr(grHandle, path, GR_ATT_CUR_DRV, "");
	for (i = 0; i < s->_ncars; i++) {
	    if (!strcmp(s->cars[i]->_name, carName)) {
		break;
	    }
	}
	if (i < s->_ncars) {
	    curCar = s->cars[i];
	} else {
	    curCar = s->cars[0];
	}
    }

    sprintf(buf, "%s-%d-%d", GR_ATT_FOVY, curCamHead, curCam->getId());
    curCam->loadDefaults(buf);
    drawCurrent = curCam->getDrawCurrent();
}


/* Create cameras */
void cGrScreen::initCams(tSituation *s)
{
    tdble		fovFactor;

    ssgGetLight(0)->getColour(GL_AMBIENT, fogColor);
    sgScaleVec4(fogColor, 0.8);
    fogColor[3] = 0.5;
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.05);
    glHint(GL_FOG_HINT, GL_DONT_CARE);

    fovFactor = GfParmGetNum(grHandle, GR_SCT_GRAPHIC, GR_ATT_FOVFACT, (char*)NULL, 1.0);
    fovFactor *= GfParmGetNum(grTrackHandle, TRK_SECT_GRAPH, TRK_ATT_FOVFACT, (char*)NULL, 1.0);

    if (boardCam == NULL) {
	boardCam = new cGrOrthoCamera(this,0, 800, 0, 600);
    }

    if (bgCam == NULL) {
	bgCam = new cGrBackgroundCam(this);
    }

    if (mirrorCam == NULL) {
	mirrorCam = new cGrCarCamMirror(this,
					-1,
					0,			/* drawCurr */
					1,			/* drawBG  */
					90.0,			/* fovy */
					0.0,			/* fovymin */
					360.0,			/* fovymax */
					0.3,			/* near */
					300.0 * fovFactor,	/* far */
					200.0 * fovFactor,	/* fog */
					300.0 * fovFactor	/* fog */
					);
    }
    
    /* Scene Cameras */
    memset(cams, 0, sizeof(cams));

    grCamCreateSceneCameraList(this, cams, fovFactor);

    loadParams(s);
}

void cGrScreen::initBoard(void)
{
    if (board == NULL) {
	board = new cGrBoard (id);
    }
    board->initBoard ();
    board->loadDefaults ();
}
