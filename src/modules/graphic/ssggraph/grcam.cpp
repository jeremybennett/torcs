/***************************************************************************

    file                 : grcam.cpp
    created              : Mon Aug 21 20:55:32 CEST 2000
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <plib/ssg.h>

#include <robottools.h>
#include <graphic.h>
#include "grscene.h"
#include "grcam.h"
#include "grcar.h"
#include "grmain.h"

int grScissorflag = 0;

float grviewRatio;

tCameraHead grCams[10];  /*  */
tCamera *grCurCam   = (tCamera*)NULL;   /* the current camera */
int	grCurCamHead = 0;		/* the current camera list */	
tCamera *grBoardCam = (tCamera*)NULL;   /* the board camera */

int scrx, scry, scrw, scrh;
t3Dd	grCamPos;

static void grCarCam20(tCamera *cam, tCarElt*);
static void grCarCam21(tCamera *cam, tCarElt*);
static void grCarCam22(tCamera *cam, tCarElt*);
static void grCarCam30(tCamera *cam, tCarElt*);
static void grCarCam31(tCamera *cam, tCarElt*);
static void grCarCam40(tCamera *cam, tCarElt*);
static void grCarCam41(tCamera *cam, tCarElt*);
static void grCarCam42(tCamera *cam, tCarElt*);
static void grCarCam43(tCamera *cam, tCarElt*);
static void grCarCam50(tCamera *cam, tCarElt*);
static void grCarCam60(tCamera *cam, tCarElt*);
static void grCarCam80(tCamera *cam, tCarElt*);
static void grCarCamNoZoompersp(tCamera *cam, tCarElt *car);
static void grCarCamZoompersp(tCamera *cam, tCarElt *car);
static void grCarCam100(tCamera *cam, tCarElt *car);
static void grCarCam101(tCamera *cam, tCarElt *car);
static void grCarCam110(tCamera *cam, tCarElt *car, tSituation *s);

void grSetView(int x, int y, int w, int h)
{
    grviewRatio = (float)w / (float)h;
    glViewport(x, y, w, h);

    if (grScissorflag) {
	glScissor(x, y, w, h);
    }

    scrx = x;
    scry = y;
    scrw = w;
    scrh = h;
}

void grUpdateCamera(tCamera *cam, tCarElt *car, tSituation *s)
{
    switch (cam->projtype) {
    case CAM_FCTPERSPEC:
	cam->uproj.fpersp.fcam(cam, car);
	break;
    }

    switch (cam->camtype) {
    case CAM_FCT:
	cam->ucam.fcam.fcam(cam, car);
	break;
    case CAM_FCTS:
	cam->ucam.fcams.fcams(cam, car, s);
	break;
    }
    
}

static void
grMakeLookAtMat4 ( sgMat4 dst, const sgVec3 eye, const sgVec3 center, const sgVec3 up )
{
  // Caveats:
  // 1) In order to compute the line of sight, the eye point must not be equal
  //    to the center point.
  // 2) The up vector must not be parallel to the line of sight from the eye
  //    to the center point.

  /* Compute the direction vectors */
  sgVec3 x,y,z;

  /* Y vector = center - eye */
  sgSubVec3 ( y, center, eye ) ;

  /* Z vector = up */
  sgCopyVec3 ( z, up ) ;

  /* X vector = Y cross Z */
  sgVectorProductVec3 ( x, y, z ) ;

  /* Recompute Z = X cross Y */
  sgVectorProductVec3 ( z, x, y ) ;

  /* Normalize everything */
  sgNormaliseVec3 ( x ) ;
  sgNormaliseVec3 ( y ) ;
  sgNormaliseVec3 ( z ) ;

  /* Build the matrix */
#define M(row,col)  dst[row][col]
  M(0,0) = x[0];    M(0,1) = x[1];    M(0,2) = x[2];    M(0,3) = 0.0;
  M(1,0) = y[0];    M(1,1) = y[1];    M(1,2) = y[2];    M(1,3) = 0.0;
  M(2,0) = z[0];    M(2,1) = z[1];    M(2,2) = z[2];    M(2,3) = 0.0;
  M(3,0) = eye[0];  M(3,1) = eye[1];  M(3,2) = eye[2];  M(3,3) = 1.0;
#undef M
}

static void
grCameraLookAt ( const sgVec3 eye, const sgVec3 center, const sgVec3 up )
{
  sgMat4 mat;
  grMakeLookAtMat4(mat, eye, center, up);
  
  grContext.setCamera(mat);
}

void grSetCamera(tCamera *cam, tCarElt *car)
{
    switch (cam->projtype) {
    case CAM_FCTPERSPEC:
	grContext.setFOV(grviewRatio * cam->uproj.fpersp.cfovy, cam->uproj.fpersp.cfovy);
	grContext.setNearFar(cam->uproj.fpersp.cnear, cam->uproj.fpersp.cfar);
	break;
	
    case CAM_PERSPEC:
	grContext.setFOV(grviewRatio * cam->uproj.persp.fovy, cam->uproj.persp.fovy);
	grContext.setNearFar(cam->uproj.persp.fnear, cam->uproj.persp.ffar);
	break;

    case CAM_ORTHO:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(cam->uproj.ortho.left, cam->uproj.ortho.right, cam->uproj.ortho.bottom,
		   cam->uproj.ortho.top);
	break;
    }
    

    switch (cam->camtype) {
    case CAM_LOOKAT:
	grCameraLookAt(cam->ucam.lookat.eye, cam->ucam.lookat.center, cam->ucam.lookat.up);
	break;

    case CAM_FCT:
	grCameraLookAt(cam->ucam.fcam.eye, cam->ucam.fcam.center, cam->ucam.fcam.up);
	break;

    case CAM_FCTS:
	grCameraLookAt(cam->ucam.fcams.eye, cam->ucam.fcams.center, cam->ucam.fcams.up);
	break;

    default:
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	break;
    }
    
}

void
grSetZoom(void *vp)
{
    int		cmd = (int)vp;
    char	buf[256];
    
    switch(cmd) {
	/* zoom in */
    case 0:
	if ((grCurCam->projtype == CAM_PERSPEC) || (grCurCam->projtype == CAM_FCTPERSPEC)) {
	    if (grCurCam->uproj.persp.fovy > 2) {
		grCurCam->uproj.persp.fovy--;
	    } else {
		grCurCam->uproj.persp.fovy /= 2.0;
	    }
	    
	    if (grCurCam->uproj.persp.fovy < grCurCam->uproj.persp.fovymin) {
		grCurCam->uproj.persp.fovy = grCurCam->uproj.persp.fovymin;
	    }
	}
	break;
	
	/* zoom out */
    case 1:
	if ((grCurCam->projtype == CAM_PERSPEC) || (grCurCam->projtype == CAM_FCTPERSPEC)) {
	    grCurCam->uproj.persp.fovy++;
	    if (grCurCam->uproj.persp.fovy > grCurCam->uproj.persp.fovymax) {
		grCurCam->uproj.persp.fovy = grCurCam->uproj.persp.fovymax;
	    }
	}
	break;

	/* zoom max */
    case 2:
	if ((grCurCam->projtype == CAM_PERSPEC) || (grCurCam->projtype == CAM_FCTPERSPEC)) {
	    grCurCam->uproj.persp.fovy = grCurCam->uproj.persp.fovymax;
	}
	break;

	/* zoom min */
    case 3:
	if ((grCurCam->projtype == CAM_PERSPEC) || (grCurCam->projtype == CAM_FCTPERSPEC)) {
	    grCurCam->uproj.persp.fovy = grCurCam->uproj.persp.fovymin;
	}
	break;

	/* zoom default */
    case 4:
	if ((grCurCam->projtype == CAM_PERSPEC) || (grCurCam->projtype == CAM_FCTPERSPEC)) {
	    grCurCam->uproj.persp.fovy = grCurCam->uproj.persp.fovydflt;
	}
	break;
    }
    sprintf(buf, "%s-%d-%d", GR_ATT_FOVY, grCurCamHead, grCurCam->id);
    GfParmSetNum(grHandle, GR_SCT_DISPMODE, buf,
		 (char*)NULL, (tdble)grCurCam->uproj.persp.fovy);
    GfParmWriteFile("config/graph.xml", grHandle, "Graph", GFPARM_PARAMETER, "../dtd/params.dtd");
}

void
grSelectCamera(void *vp)
{
    int		cam = (int)vp;
    char	buf[256];

    if (cam == grCurCamHead) {
	/* Same camera list, choose the next one */
	grCurCam = (tCamera*)GfRlstGetNext(&(grCams[cam].cams), &(grCurCam->l));
	if (grCurCam == NULL) {
	    /* only one cam */
	    grCurCam = (tCamera*)GfRlstGetFirst(&(grCams[cam].cams));
	} else {
	    GfRlstSeekElt(&(grCams[cam].cams), &(grCurCam->l));
	}
    } else {
	/* Change of camera list, take the first one */
	grCurCamHead = cam;
	grCurCam = (tCamera*)GfRlstGetFirst(&(grCams[cam].cams));
    }
    if (grCurCam == NULL) {
	/* back to default camera */
	grCurCamHead = 0;
	grCurCam = (tCamera*)GfRlstGetFirst(&(grCams[grCurCamHead].cams));
    }
    GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_CAM, (char*)NULL, (tdble)grCurCam->id);
    GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_CAM_HEAD, (char*)NULL, (tdble)grCurCamHead);    
    
    sprintf(buf, "%s-%d-%d", GR_ATT_FOVY, grCurCamHead, grCurCam->id);
    grCurCam->uproj.persp.fovy = (float)GfParmGetNum(grHandle, GR_SCT_DISPMODE,
						       buf, (char*)NULL, grCurCam->uproj.persp.fovydflt);
    grDrawCurrent = grCurCam->drawCurrent;
    GfParmWriteFile("config/graph.xml", grHandle, "Graph", GFPARM_PARAMETER, "../dtd/params.dtd");
}

void
grInitCams(void)
{
    int		c;
    int		id;
    tCamera	*curCam;

#define FAR_GEN 1500.0

    /* Board camera ortho */
    if (grBoardCam == NULL) {
	grBoardCam = (tCamera*)malloc(sizeof(tCamera));
	memset(grBoardCam, 0, sizeof(tCamera));
	grBoardCam->projtype = CAM_ORTHO;
	grBoardCam->uproj.ortho.left = scrx;
	grBoardCam->uproj.ortho.right = scrx + scrw;
	grBoardCam->uproj.ortho.bottom = scry;
	grBoardCam->uproj.ortho.top = scry + scrh;
	grBoardCam->camtype = CAM_INIT;
    }

    /* Scene Cameras */
    memset(grCams, 0, sizeof(grCams));
    
    c = 0;
    
    /* F2 */
    GfRlstInit(&(grCams[c].cams));
    id = 0;

    /* cam F2 = behind near */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 40.0;
    curCam->uproj.persp.fnear = 1.0;
    curCam->uproj.persp.ffar  = FAR_GEN;
    curCam->uproj.persp.fovymin = 5.0;
    curCam->uproj.persp.fovymax = 95.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam20;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;
    
    /* cam F2 = behind far */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 40.0;
    curCam->uproj.persp.fnear = 1.0;
    curCam->uproj.persp.ffar  = FAR_GEN;
    curCam->uproj.persp.fovymin = 5.0;
    curCam->uproj.persp.fovymax = 95.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam21;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;

    /* cam F2 = car inside with car (bonnet view) */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 67.5;
    curCam->uproj.persp.fnear = 0.3;
    curCam->uproj.persp.ffar  = FAR_GEN;
    curCam->uproj.persp.fovymin = 50.0;
    curCam->uproj.persp.fovymax = 95.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam22;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;

    /* cam F2 = car inside car (no car - road view) */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 67.5;
    curCam->uproj.persp.fnear = 1.0;
    curCam->uproj.persp.ffar  = FAR_GEN;
    curCam->uproj.persp.fovymin = 5.0;
    curCam->uproj.persp.fovymax = 95.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam22;
    curCam->drawCurrent = 0;
    curCam->drawBackground = 1;

    /* F3 */
    c++;
    GfRlstInit(&(grCams[c].cams));
    id = 0;

    /* cam F3 = car behind*/
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 40.0;
    curCam->uproj.persp.fnear = 1.0;
    curCam->uproj.persp.ffar  = FAR_GEN;
    curCam->uproj.persp.fovymin = 5.0;
    curCam->uproj.persp.fovymax = 95.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam30;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;

    /* cam F3 = car reverse*/
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 30.0;
    curCam->uproj.persp.fnear = 1.0;
    curCam->uproj.persp.ffar  = FAR_GEN;
    curCam->uproj.persp.fovymin = 5.0;
    curCam->uproj.persp.fovymax = 95.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam31;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;


    /* F4 */
    c++;
    GfRlstInit(&(grCams[c].cams));
    id = 0;

    /* cam F4 = car side */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 30.0;
    curCam->uproj.persp.fnear = 1.0;
    curCam->uproj.persp.ffar  = MAX(grWrldMaxSize * 2, 1000);
    curCam->uproj.persp.fovymin = 5.0;
    curCam->uproj.persp.fovymax = 50.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam40;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;

    /* cam F4 = car side */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 30.0;
    curCam->uproj.persp.fnear = 1.0;
    curCam->uproj.persp.ffar  = MAX(grWrldMaxSize * 2, 1000);
    curCam->uproj.persp.fovymin = 5.0;
    curCam->uproj.persp.fovymax = 50.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam41;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;

    /* cam F4 = car side */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 30.0;
    curCam->uproj.persp.fnear = 1.0;
    curCam->uproj.persp.ffar  = MAX(grWrldMaxSize * 2, 1000);
    curCam->uproj.persp.fovymin = 5.0;
    curCam->uproj.persp.fovymax = 50.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam42;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;

    /* cam F4 = car side */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 30.0;
    curCam->uproj.persp.fnear = 1.0;
    curCam->uproj.persp.ffar  = MAX(grWrldMaxSize * 2, 1000);
    curCam->uproj.persp.fovymin = 5.0;
    curCam->uproj.persp.fovymax = 50.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam43;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;


    /* F5 */
    c++;
    GfRlstInit(&(grCams[c].cams));
    id = 0;

    /* cam F5 = car up */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 10.0;
    curCam->uproj.persp.fnear = 200.0;
    curCam->uproj.persp.ffar  = grWrldMaxSize * 2;
    curCam->uproj.persp.fovymin = 2.0;
    curCam->uproj.persp.fovymax = 90.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam50;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 0;


    /* F6 */
    c++;
    GfRlstInit(&(grCams[c].cams));
    id = 0;

    /* cam F6 = car from circuit centre */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_FCTPERSPEC;
    curCam->uproj.fpersp.fcam = grCarCamZoompersp;
    curCam->uproj.persp.fovy = 21.0;
    curCam->uproj.persp.fnear = 100.0;
    curCam->uproj.persp.ffar  = FAR_GEN;
    curCam->uproj.persp.fovymin = 2.0;
    curCam->uproj.persp.fovymax = 60.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam60;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;


    /* F7 */
    c++;
    GfRlstInit(&(grCams[c].cams));
    id = 0;

    /* cam F7 = panoramic */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 74.0;
    curCam->uproj.persp.fnear = 10.0;
    curCam->uproj.persp.ffar  = grWrldMaxSize;
    curCam->uproj.persp.fovymin = 1.0;
    curCam->uproj.persp.fovymax = 110.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_LOOKAT;
    curCam->ucam.lookat.eye[0] = grWrldX/2;
    curCam->ucam.lookat.eye[1] = grWrldY/2;
    curCam->ucam.lookat.eye[2] = MAX(grWrldX/2, grWrldY*4/3/2) + grWrldZ;
    curCam->ucam.lookat.center[0] = grWrldX/2;
    curCam->ucam.lookat.center[1] = grWrldY/2;
    curCam->ucam.lookat.center[2] = 0;
    curCam->ucam.lookat.up[0] = 0;
    curCam->ucam.lookat.up[1] = 1;
    curCam->ucam.lookat.up[2] = 0;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 0;

    /* cam F7 = panoramic */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 74.0;
    curCam->uproj.persp.fnear = 10.0;
    curCam->uproj.persp.ffar  = 2 * grWrldMaxSize;
    curCam->uproj.persp.fovymin = 1.0;
    curCam->uproj.persp.fovymax = 110.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_LOOKAT;
    curCam->ucam.lookat.eye[0] = -grWrldX/2;
    curCam->ucam.lookat.eye[1] = -grWrldY/2;
    curCam->ucam.lookat.eye[2] = 0.25 * sqrt(grWrldX*grWrldX+grWrldY*grWrldY);
    curCam->ucam.lookat.center[0] = grWrldX/2;
    curCam->ucam.lookat.center[1] = grWrldY/2;
    curCam->ucam.lookat.center[2] = 0;
    curCam->ucam.lookat.up[0] = 0;
    curCam->ucam.lookat.up[1] = 0;
    curCam->ucam.lookat.up[2] = 1;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;

    /* cam F7 = panoramic */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_PERSPEC;
    curCam->uproj.persp.fovy = 74.0;
    curCam->uproj.persp.fnear = 10.0;
    curCam->uproj.persp.ffar  = 2 * grWrldMaxSize;
    curCam->uproj.persp.fovymin = 1.0;
    curCam->uproj.persp.fovymax = 110.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_LOOKAT;
    curCam->ucam.lookat.eye[0] = -grWrldX/2;
    curCam->ucam.lookat.eye[1] = grWrldY + grWrldY/2;
    curCam->ucam.lookat.eye[2] = 0.25 * sqrt(grWrldX*grWrldX+grWrldY*grWrldY);
    curCam->ucam.lookat.center[0] = grWrldX/2;
    curCam->ucam.lookat.center[1] = grWrldY/2;
    curCam->ucam.lookat.center[2] = 0;
    curCam->ucam.lookat.up[0] = 0;
    curCam->ucam.lookat.up[1] = 0;
    curCam->ucam.lookat.up[2] = 1;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;

    /* F8 */
    c++;
    GfRlstInit(&(grCams[c].cams));
    id = 0;

    /* cam F8 = road cam  */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_FCTPERSPEC;
    curCam->uproj.fpersp.fcam = grCarCamNoZoompersp;
    curCam->uproj.persp.fovy = 10.0;
    curCam->uproj.persp.fnear = 300.0;
    curCam->uproj.persp.ffar  = FAR_GEN;
    curCam->uproj.persp.fovymin = 1.0;
    curCam->uproj.persp.fovymax = 20.0;
    curCam->uproj.persp.fovydflt = curCam->uproj.persp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam80;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;


    /* F9 */
    c++;
    GfRlstInit(&(grCams[c].cams));
    id = 0;

    /* cam F9 = road cam zoomed */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_FCTPERSPEC;
    curCam->uproj.fpersp.fcam = grCarCamZoompersp;
    curCam->uproj.fpersp.fovy = 5.0;
    curCam->uproj.fpersp.fnear = 300.0;
    curCam->uproj.fpersp.ffar  = FAR_GEN;
    curCam->uproj.fpersp.fovymin = 1.0;
    curCam->uproj.fpersp.fovymax = 90.0;
    curCam->uproj.fpersp.fovydflt = 17.0;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam80;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;


    /* F10 */
    c++;
    GfRlstInit(&(grCams[c].cams));
    id = 0;

    /* cam F10 = follow car zoomed */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_FCTPERSPEC;
    curCam->uproj.fpersp.fcam = grCarCamZoompersp;
    curCam->uproj.fpersp.fovy = 22.0;
    curCam->uproj.fpersp.fnear = 50.0;
    curCam->uproj.fpersp.ffar  = FAR_GEN;
    curCam->uproj.fpersp.fovymin = 1.0;
    curCam->uproj.fpersp.fovymax = 90.0;
    curCam->uproj.fpersp.fovydflt = curCam->uproj.fpersp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam100;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;

    /* cam F10 = road cam zoomed */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_FCTPERSPEC;
    curCam->uproj.fpersp.fcam = grCarCamZoompersp;
    curCam->uproj.fpersp.fovy = 20.0;
    curCam->uproj.fpersp.fnear = 50.0;
    curCam->uproj.fpersp.ffar  = FAR_GEN;
    curCam->uproj.fpersp.fovymin = 1.0;
    curCam->uproj.fpersp.fovymax = 90.0;
    curCam->uproj.fpersp.fovydflt = curCam->uproj.fpersp.fovy;
    curCam->camtype = CAM_FCT;
    curCam->ucam.fcam.fcam = grCarCam101;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;


    /* F11 */
    c++;
    GfRlstInit(&(grCams[c].cams));
    id = 0;

    /* cam F11 = Realizator view */
    curCam = (tCamera*)malloc(sizeof(tCamera));
    memset(curCam, 0, sizeof(tCamera));
    curCam->id = id++;
    GfRlstAddLast(&(grCams[c].cams), &(curCam->l));
    curCam->projtype = CAM_FCTPERSPEC;
    curCam->uproj.fpersp.fcam = grCarCamZoompersp;
    curCam->uproj.fpersp.fovy = 5.0;
    curCam->uproj.fpersp.fnear = 300.0;
    curCam->uproj.fpersp.ffar  = FAR_GEN;
    curCam->uproj.fpersp.fovymin = 1.0;
    curCam->uproj.fpersp.fovymax = 90.0;
    curCam->uproj.fpersp.fovydflt = 17.0;
    curCam->camtype = CAM_FCTS;
    curCam->ucam.fcams.fcams = grCarCam110;
    curCam->drawCurrent = 1;
    curCam->drawBackground = 1;
    
}

const tdble dist = 30.0;

static void
grCarCam20(tCamera *cam, tCarElt *car)
{
    static tdble PreA = 0.0;
    tdble A;
    tdble CosA;
    tdble SinA;
    tdble x;
    tdble y;

    A = car->_yaw;
    if (fabs(PreA - A) > fabs(PreA - A + 2*PI)) {
	PreA += 2*PI;
    } else if (fabs(PreA - A) > fabs(PreA - A - 2*PI)) {
	PreA -= 2*PI;
    }
    RELAXATION(A, PreA, 10.0);
    CosA = cos(A);
    SinA = sin(A);
    x = car->_pos_X - 10.0 * CosA;
    y = car->_pos_Y - 10.0 * SinA;

    grCamPos.x = x;
    grCamPos.y = y;
    grCamPos.z = RtTrackHeightG(car->_trkPos.seg, x, y) + 2.0;
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}

static void
grCarCam21(tCamera *cam, tCarElt *car)
{
    static tdble PreA = 0.0;
    tdble A;
    tdble CosA;
    tdble SinA;
    tdble x;
    tdble y;

    A = RtTrackSideTgAngleL(&(car->_trkPos));
    if (fabs(PreA - A) > fabs(PreA - A + 2*PI)) {
	PreA += 2*PI;
    } else if (fabs(PreA - A) > fabs(PreA - A - 2*PI)) {
	PreA -= 2*PI;
    }
    RELAXATION(A, PreA, 10.0);
    CosA = cos(A);
    SinA = sin(A);
    x = car->_pos_X - 20.0 * CosA;
    y = car->_pos_Y - 20.0 * SinA;

    grCamPos.x = x;
    grCamPos.y = y;
    grCamPos.z = RtTrackHeightG(car->_trkPos.seg, x, y) + 3.0;
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}

static void
grCarCam22(tCamera *cam, tCarElt *car)
{
    tdble A1 = car->_yaw;
    tdble CosA1 = cos(A1);
    tdble SinA1 = sin(A1);
    //tdble A2 = MIN(car->ctrl->steer * 1.5, 0.5) + car->_yaw;
    tdble A2 = car->_yaw;
    tdble CosA2 = cos(A2);
    tdble SinA2 = sin(A2);
    tdble x = car->_pos_X + dist * CosA2;
    tdble y = car->_pos_Y + dist * SinA2;

    grCamPos.x = car->_pos_X + CosA1 * car->_drvPos_x - SinA1 * car->_drvPos_y;
    grCamPos.y = car->_pos_Y + SinA1 * car->_drvPos_x + CosA1 * car->_drvPos_y;
    grCamPos.z = car->_pos_Z + car->_drvPos_z;
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = x;
    cam->ucam.fcam.center[1] = y;
    cam->ucam.fcam.center[2] = RtTrackHeightG(car->_trkPos.seg, x, y) + 1.5;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}

static void
grCarCam30(tCamera *cam, tCarElt *car)
{
    static tdble PreA = 0.0;
    tdble A;
    tdble CosA;
    tdble SinA;
    tdble x;
    tdble y;

    A = RtTrackSideTgAngleL(&(car->_trkPos));
    if (fabs(PreA - A) > fabs(PreA - A + 2*PI)) {
	PreA += 2*PI;
    } else if (fabs(PreA - A) > fabs(PreA - A - 2*PI)) {
	PreA -= 2*PI;
    }
    RELAXATION(A, PreA, 5.0);
    CosA = cos(A);
    SinA = sin(A);
    x = car->_pos_X - dist * CosA;
    y = car->_pos_Y - dist * SinA;

    grCamPos.x = x;
    grCamPos.y = y;
    grCamPos.z = RtTrackHeightG(car->_trkPos.seg, x, y) + 5.0;
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}



static void
grCarCam31(tCamera *cam, tCarElt *car)
{
    tdble CosA = cos(car->_yaw);
    tdble SinA = sin(car->_yaw);
    tdble x = car->_pos_X + dist * CosA;
    tdble y = car->_pos_Y + dist * SinA;
    
    grCamPos.x = x;
    grCamPos.y = y;
    grCamPos.z = RtTrackHeightG(car->_trkPos.seg, x, y) + 0.5;
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}

static void
grCarCam40(tCamera *cam, tCarElt *car)
{
    grCamPos.x = car->_pos_X;
    grCamPos.y = car->_pos_Y-30;
    grCamPos.z = car->_pos_Z+5;
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}

static void
grCarCam41(tCamera *cam, tCarElt *car)
{
    grCamPos.x = car->_pos_X;
    grCamPos.y = car->_pos_Y+30;
    grCamPos.z = car->_pos_Z+5;
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}

static void
grCarCam42(tCamera *cam, tCarElt *car)
{
    grCamPos.x = car->_pos_X+30;
    grCamPos.y = car->_pos_Y;
    grCamPos.z = car->_pos_Z+5;
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}

static void
grCarCam43(tCamera *cam, tCarElt *car)
{
    grCamPos.x = car->_pos_X-30;
    grCamPos.y = car->_pos_Y;
    grCamPos.z = car->_pos_Z+5;
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}

static void
grCarCam50(tCamera *cam, tCarElt *car)
{
    static tdble precX = grWrldX*.5;
    static tdble precY = grWrldY*.6;
    static tdble precZ = 120;
 
#define    CAMSPD4 100.0

    grCamPos.x = car->_pos_X;
    RELAXATION(grCamPos.x, precX, CAMSPD4);
    grCamPos.y = car->_pos_Y;
    RELAXATION(grCamPos.y, precY, CAMSPD4);
    grCamPos.z = car->_pos_Z+300;
    RELAXATION(grCamPos.z, precZ, CAMSPD4);
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = grCamPos.x;
    cam->ucam.fcam.center[1] = grCamPos.y;
    cam->ucam.fcam.center[2] = grCamPos.z - 300;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 1;
    cam->ucam.fcam.up[2] = 0;
}

static void
grCarCam60(tCamera *cam, tCarElt *car)
{
    //gluLookAt(grWrldX*.5, -60, 120,
    grCamPos.x = grWrldX*.5;
    grCamPos.y = grWrldY*.6;
    grCamPos.z = 120;
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}


static void
grCarCam80(tCamera *cam, tCarElt *car)
{
    tRoadCam *curCam;

    curCam = car->_trkPos.seg->cam;
    
    if (curCam == NULL) {
	grCamPos.x = grWrldX*.5;
	grCamPos.y = grWrldY*.6;
	grCamPos.z = 120;
    
	cam->ucam.fcam.eye[0] = grCamPos.x;
	cam->ucam.fcam.eye[1] = grCamPos.y;
	cam->ucam.fcam.eye[2] = grCamPos.z;
	cam->ucam.fcam.center[0] = car->_pos_X;
	cam->ucam.fcam.center[1] = car->_pos_Y;
	cam->ucam.fcam.center[2] = car->_pos_Z;
	cam->ucam.fcam.up[0] = 0;
	cam->ucam.fcam.up[1] = 0;
	cam->ucam.fcam.up[2] = 1;
	return;
    }

    grCamPos.x = curCam->pos.x;
    grCamPos.y = curCam->pos.y;
    grCamPos.z = curCam->pos.z;
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}

static void
grCarCamNoZoompersp(tCamera *cam, tCarElt *car)
{
    tdble	dx, dy, dz, dd, fnear, ffar;

    dx = grCamPos.x - car->_pos_X;
    dy = grCamPos.y - car->_pos_Y;
    dz = grCamPos.z - car->_pos_Z;
    
    dd = sqrt(dx*dx+dy*dy+dz*dz);
    
    fnear = dz - 2;
    if (fnear < 1) {
	fnear = 1;
    }
    ffar  = dd + grCurCam->uproj.fpersp.ffar;

    grCurCam->uproj.fpersp.cfovy = grCurCam->uproj.fpersp.fovy;
    grCurCam->uproj.fpersp.cfar = ffar;
    grCurCam->uproj.fpersp.cnear = fnear;
}


static void
grCarCamZoompersp(tCamera *cam, tCarElt *car)
{
    tdble	dx, dy, dz, dd, fnear, ffar;

    dx = grCamPos.x - car->_pos_X;
    dy = grCamPos.y - car->_pos_Y;
    dz = grCamPos.z - car->_pos_Z;
    
    dd = sqrt(dx*dx+dy*dy+dz*dz);

    fnear = dz - 5;
    if (fnear < 1) {
	fnear = 1;
    }
    ffar  = dd + grCurCam->uproj.fpersp.ffar;

    grCurCam->uproj.fpersp.cfovy = RAD2DEG(atan2(grCurCam->uproj.fpersp.fovy, dd));
    grCurCam->uproj.fpersp.cfar = ffar;
    grCurCam->uproj.fpersp.cnear = fnear;
}

static void
grCarCam100(tCamera *cam, tCarElt *car)
{
    tRoadCam	*curCam;
    tdble	dx, dy, dz, lg;
    tdble	x,y,z;
    static tdble preX = car->_pos_X;
    static tdble preY = car->_pos_Y;
    static tdble preZ = car->_pos_Z;
    static tdble precX = grWrldX*.5;
    static tdble precY = grWrldY*.6;
    static tdble precZ = 120;
    

    curCam = car->_trkPos.seg->cam;
    
    if (curCam == NULL) {
	grCamPos.x = grWrldX*.5;
	grCamPos.y = grWrldY*.6;
	grCamPos.z = 120;
    
	cam->ucam.fcam.eye[0] = grCamPos.x;
	cam->ucam.fcam.eye[1] = grCamPos.y;
	cam->ucam.fcam.eye[2] = grCamPos.z;
	cam->ucam.fcam.center[0] = car->_pos_X;
	cam->ucam.fcam.center[1] = car->_pos_Y;
	cam->ucam.fcam.center[2] = car->_pos_Z;
	cam->ucam.fcam.up[0] = 0;
	cam->ucam.fcam.up[1] = 0;
	cam->ucam.fcam.up[2] = 1;
	return;
    }

#define CARSPD	5.0
    x = car->_pos_X;
    RELAXATION(x, preX, CARSPD);
    y = car->_pos_Y;
    RELAXATION(y, preY, CARSPD);
    z = car->_pos_Z;
    RELAXATION(z, preZ, CARSPD);

    dx = x - curCam->pos.x;
    dy = y - curCam->pos.y;
    dz = z - curCam->pos.z;
    lg = sqrt(dx*dx+dy*dy+dz*dz) / grCurCam->uproj.fpersp.fovy;
    
#define CAMSPD	40.0
    
    grCamPos.x = car->_pos_X - dx / lg;
    RELAXATION(grCamPos.x, precX, CAMSPD);
    grCamPos.y = car->_pos_Y - dy / lg;
    RELAXATION(grCamPos.y, precY, CAMSPD);
    grCamPos.z = car->_pos_Z - dz / lg;
    RELAXATION(grCamPos.z, precZ, CAMSPD);


    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}

static void
grCarCam101(tCamera *cam, tCarElt *car)
{
    tRoadCam	*curCam;
    tdble	dx, dy, dz, lg;

    curCam = car->_trkPos.seg->cam;
    
    if (curCam == NULL) {
	grCamPos.x = grWrldX*.5;
	grCamPos.y = grWrldY*.6;
	grCamPos.z = 120;
    
	cam->ucam.fcam.eye[0] = grCamPos.x;
	cam->ucam.fcam.eye[1] = grCamPos.y;
	cam->ucam.fcam.eye[2] = grCamPos.z;
	cam->ucam.fcam.center[0] = car->_pos_X;
	cam->ucam.fcam.center[1] = car->_pos_Y;
	cam->ucam.fcam.center[2] = car->_pos_Z;
	cam->ucam.fcam.up[0] = 0;
	cam->ucam.fcam.up[1] = 0;
	cam->ucam.fcam.up[2] = 1;
	return;
    }

    dx = car->_pos_X - curCam->pos.x;
    dy = car->_pos_Y - curCam->pos.y;
    dz = car->_pos_Z - curCam->pos.z;
    lg = sqrt(dx*dx+dy*dy+dz*dz) / grCurCam->uproj.fpersp.fovy;
    

    
    grCamPos.x = car->_pos_X + dx / lg;
    grCamPos.y = car->_pos_Y + dy / lg;
    grCamPos.z = car->_pos_Z - dz / lg;
    
    cam->ucam.fcam.eye[0] = grCamPos.x;
    cam->ucam.fcam.eye[1] = grCamPos.y;
    cam->ucam.fcam.eye[2] = grCamPos.z;
    cam->ucam.fcam.center[0] = car->_pos_X;
    cam->ucam.fcam.center[1] = car->_pos_Y;
    cam->ucam.fcam.center[2] = car->_pos_Z;
    cam->ucam.fcam.up[0] = 0;
    cam->ucam.fcam.up[1] = 0;
    cam->ucam.fcam.up[2] = 1;
}


static tdble
GetDistToStart(tCarElt *car)
{
    tTrackSeg	*seg;
    tdble	lg;
    
    seg = car->_trkPos.seg;
    lg = seg->lgfromstart;
    
    switch (seg->type) {
    case TR_STR:
	lg += car->_trkPos.toStart;
	break;
    default:
	lg += car->_trkPos.toStart * seg->radius;
	break;
    }
    return lg;
}

/* TV Director View */
typedef struct 
{
    double	prio;
    int		viewable;
    int		event;
} tSchedView;

static tSchedView *schedView;
static double camChangeInterval;
static double camEventInterval;
static double lastEventTime;
static double lastViewTime;
static tdble  proximityThld;
void
grInitTVDirectorView(tSituation *s)
{
    schedView = (tSchedView *)calloc(grNbCars, sizeof(tSchedView));
    if (!schedView) {
	GfTrace("malloc error");
	exit (1);
    }
    
    lastEventTime = 0;
    lastViewTime = 0;

    camChangeInterval = GfParmGetNum(grHandle, GR_SCT_TVDIR, GR_ATT_CHGCAMINT, (char*)NULL, 10.0);
    camEventInterval  = GfParmGetNum(grHandle, GR_SCT_TVDIR, GR_ATT_EVTINT, (char*)NULL, 1.0);
    proximityThld     = GfParmGetNum(grHandle, GR_SCT_TVDIR, GR_ATT_PROXTHLD, (char*)NULL, 10.0);
}

static tCarElt *
grGetCurCar(tSituation *s)
{
    int		i, j;
    int		curCar;
    double	curPrio;
    tCarElt	*car = NULL;
    double	deltaEventTime = s->currentTime - lastEventTime;
    double	deltaViewTime = s->currentTime - lastViewTime;
    int		event = 0;
    
    /* Track events */
    if (deltaEventTime < camEventInterval) {
	return s->cars[s->current];
    }
    
    memset(schedView, 0, grNbCars * sizeof(tSchedView));
    
    for (i = 0; i < grNbCars; i++) {
	tdble dist, fs;

	car = s->cars[i];
	schedView[car->index].prio = grNbCars - i;
	fs = GetDistToStart(car);
	if (i == 0) {
	    if ((car->_state & RM_CAR_STATE_NO_SIMU) == 0) {
		schedView[car->index].viewable = 1;
		if ((fs > (grTrack->length - 100.0)) && (car->_remainingLaps == 0)) {
		    schedView[car->index].prio += 5 * grNbCars;
		    event = 1;
		}
	    }
	} else {
	    if ((fs > (grTrack->length - 100.0)) && (car->_remainingLaps == 0)) {
		schedView[car->index].prio += grNbCars;
		event = 1;
	    }
	}
	
	if ((car->_state & RM_CAR_STATE_NO_SIMU) == 0) {
	    dist = fabs(car->_trkPos.toMiddle) - grTrack->width / 2.0;
	    /* out of track */
	    if (dist > 0) {
		schedView[car->index].prio += grNbCars;
		schedView[car->index].viewable |= 8;
		if (car->ctrl->raceCmd & RM_CMD_PIT_ASKED) {
		    schedView[car->index].prio += grNbCars;
		    event = 1;
		}
	    }

	    for (j = i+1; j < grNbCars; j++) {
		tCarElt *car2 = s->cars[j];
		tdble fs2 = GetDistToStart(car2);
		tdble d = fabs(fs2 - fs);

		if ((car2->_state & RM_CAR_STATE_NO_SIMU) == 0) {
		    if (d < proximityThld) {
			d = proximityThld - d;
			schedView[car->index].prio  += d * grNbCars / proximityThld;
			schedView[car2->index].prio += d * (grNbCars - 1) / proximityThld;
			schedView[car->index].viewable  |= 2;
			schedView[car2->index].viewable |= 2;
			if (i == 0) {
			    event = 1;
			}
		    }
		}
	    }

	    if (car->priv->collision) {
		schedView[car->index].prio += grNbCars;
		schedView[car->index].viewable |= 4;
		event = 1;
	    }
	} else {
	    if (i == s->current) {
		event = 1;	/* update view */
	    }
	}
    }


    /* change current car */
    if ((event && (deltaEventTime > camEventInterval)) || (deltaViewTime > camChangeInterval)) {
	int	last_current = s->current;
	


	curCar = 0;
	curPrio = -1000000.0;
	for (i = 0; i < grNbCars; i++) {
	    
	    if ((schedView[i].prio > curPrio) && (schedView[i].viewable)) {
		curPrio = schedView[i].prio;
		curCar = i;
	    }
	}
	for (i = 0; i < grNbCars; i++) {
	    if (s->cars[i]->index == curCar) {
		s->current = i;
		break;
	    }
	}
	if (last_current != s->current) {
	    lastEventTime = s->currentTime;
	    lastViewTime = s->currentTime;

	    for (i = 0; i < grNbCars; i++) {
		s->cars[i]->priv->collision = 0;
	    }
	}
    }

    return s->cars[s->current];
}


static void
grCarCam110(tCamera *cam, tCarElt *car, tSituation *s)
{
    tRoadCam *curCam;

    car = grGetCurCar(s);
    
    curCam = car->_trkPos.seg->cam;
    
    if (curCam == NULL) {
	grCamPos.x = grWrldX*.5;
	grCamPos.y = grWrldY*.6;
	grCamPos.z = 120;
    
	cam->ucam.fcams.eye[0] = grCamPos.x;
	cam->ucam.fcams.eye[1] = grCamPos.y;
	cam->ucam.fcams.eye[2] = grCamPos.z;
	cam->ucam.fcams.center[0] = car->_pos_X;
	cam->ucam.fcams.center[1] = car->_pos_Y;
	cam->ucam.fcams.center[2] = car->_pos_Z;
	cam->ucam.fcams.up[0] = 0;
	cam->ucam.fcams.up[1] = 0;
	cam->ucam.fcams.up[2] = 1;
	return;
    }

    grCamPos.x = curCam->pos.x;
    grCamPos.y = curCam->pos.y;
    grCamPos.z = curCam->pos.z;
    
    cam->ucam.fcams.eye[0] = grCamPos.x;
    cam->ucam.fcams.eye[1] = grCamPos.y;
    cam->ucam.fcams.eye[2] = grCamPos.z;
    cam->ucam.fcams.center[0] = car->_pos_X;
    cam->ucam.fcams.center[1] = car->_pos_Y;
    cam->ucam.fcams.center[2] = car->_pos_Z;
    cam->ucam.fcams.up[0] = 0;
    cam->ucam.fcams.up[1] = 0;
    cam->ucam.fcams.up[2] = 1;
}
