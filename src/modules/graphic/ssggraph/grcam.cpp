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
#include "grcam.h"
#include "grscene.h"
#include "grshadow.h"
#include "grskidmarks.h"
#include "grsmoke.h"
#include "grcar.h"
#include "grmain.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

int grScissorflag = 0;

float grviewRatio;

int		grCurCamHead = 0;			/* the current camera list */	
tGrCamHead	grCams[10];				/* from F1 to F12 */
cGrCamera	*grCurCam = (cGrCamera*)NULL;		/* the current camera */
cGrOrthoCamera	*grBoardCam = (cGrOrthoCamera*)NULL;	/* the board camera */

int scrx, scry, scrw, scrh;


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

void grSetZoom(void *vp) 
{
    grCurCam->setZoom((int)vp);
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

void cGrPerspCamera::setProjection(void)
{
    grContext.setFOV(grviewRatio * fovy, fovy);
    grContext.setNearFar(fnear, ffar);
}

void cGrPerspCamera::setModelView(void)
{
  sgMat4 mat;
  grMakeLookAtMat4(mat, eye, center, up);
  
  grContext.setCamera(mat);
}

void cGrPerspCamera::loadDefaults(char *attr)
{
    fovy = (float)GfParmGetNum(grHandle, GR_SCT_DISPMODE,
			       attr, (char*)NULL, fovydflt);
}

/* Give the height in pixels of 1 m high object on the screen at this point */
float cGrPerspCamera::getLODFactor(float x, float y, float z) {
    tdble	dx, dy, dz, dd;
    float	ang;
    int		scrh, dummy;

    dx = x - eye[0];
    dy = y - eye[1];
    dz = z - eye[2];

    dd = sqrt(dx*dx+dy*dy+dz*dz);

    ang = DEG2RAD(fovy);
    GfScrGetSize(&dummy, &scrh, &dummy, &dummy);
    
    return (float)scrh / dd / tan(ang);
}

void cGrPerspCamera::setZoom(int cmd)
{
    char	buf[256];

    switch(cmd) {
    case GR_ZOOM_IN:
	if (fovy > 2) {
	    fovy--;
	} else {
	    fovy /= 2.0;
	}
	if (fovy < fovymin) {
	    fovy = fovymin;
	}
	break;
	
    case GR_ZOOM_OUT:
	fovy++;
	if (fovy > fovymax) {
	    fovy = fovymax;
	}
	break;

    case GR_ZOOM_MAX:
	fovy = fovymax;
	break;

    case GR_ZOOM_MIN:
	fovy = fovymin;
	break;

    case GR_ZOOM_DFLT:
	fovy = fovydflt;
	break;

    sprintf(buf, "%s-%d-%d", GR_ATT_FOVY, grCurCamHead, getId());
    GfParmSetNum(grHandle, GR_SCT_DISPMODE, buf, (char*)NULL, (tdble)fovy);
    GfParmWriteFile("config/graph.xml", grHandle, "Graph",
		    GFPARM_PARAMETER, "../dtd/params.dtd");
    
    }
}

void cGrOrthoCamera::setProjection(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
}

void cGrOrthoCamera::setModelView(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void
grSelectCamera(void *vp)
{
    int		cam = (int)vp;
    char	buf[256];

    if (cam == grCurCamHead) {
	/* Same camera list, choose the next one */
	grCurCam = grCurCam->next();
	if (grCurCam == NULL) {
	    grCurCam = TAILQ_FIRST(&grCams[cam]);
	}
    } else {
	/* Change of camera list, take the first one */
	grCurCamHead = cam;
	grCurCam = TAILQ_FIRST(&grCams[cam]);
    }
    if (grCurCam == NULL) {
	/* back to default camera */
	grCurCamHead = 0;
	grCurCam = TAILQ_FIRST(&grCams[grCurCamHead]);
    }
    GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_CAM, (char*)NULL, (tdble)grCurCam->getId());
    GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_CAM_HEAD, (char*)NULL, (tdble)grCurCamHead);    
    
    sprintf(buf, "%s-%d-%d", GR_ATT_FOVY, grCurCamHead, grCurCam->getId());
    grCurCam->loadDefaults(buf);
    grDrawCurrent = grCurCam->getDrawCurrent();
    GfParmWriteFile("config/graph.xml", grHandle, "Graph", GFPARM_PARAMETER, "../dtd/params.dtd");
}

class cGrCarCamInside : public cGrPerspCamera
{
 public:
    cGrCarCamInside(int id, int drawCurr, int drawBG,
		    float myfovy, float myfovymin, float myfovymax,
		    float myfnear, float myffar = 1500.0)
	: cGrPerspCamera(id, drawCurr, drawBG,
			 myfovy, myfovymin, myfovymax,
			 myfnear, myffar) {
	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }

    void update(tCarElt *car, tSituation *s) {
	tdble A1 = car->_yaw;
	tdble CosA1 = cos(A1);
	tdble SinA1 = sin(A1);
	//tdble A2 = MIN(car->ctrl->steer * 1.5, 0.5) + car->_yaw;
	//tdble CosA2 = cos(A2);
	//tdble SinA2 = sin(A2);
	tdble CosA2 = CosA1;
	tdble SinA2 = SinA1;
	tdble x = car->_pos_X + 30.0 * CosA2;
	tdble y = car->_pos_Y + 30.0 * SinA2;

	tdble X = car->_pos_X + CosA1 * car->_drvPos_x - SinA1 * car->_drvPos_y;
	tdble Y = car->_pos_Y + SinA1 * car->_drvPos_x + CosA1 * car->_drvPos_y;
	tdble Z = car->_pos_Z + car->_drvPos_z;
	eye[0] = X;
	eye[1] = Y;
	eye[2] = Z;
	center[0] = x;
	center[1] = y;
	center[2] = RtTrackHeightG(car->_trkPos.seg, x, y) + 1.5;
    }
};

class cGrCarCamInsideFixedCar : public cGrPerspCamera
{
 public:
    cGrCarCamInsideFixedCar(int id, int drawCurr, int drawBG,
			    float myfovy, float myfovymin, float myfovymax,
			    float myfnear, float myffar = 1500.0)
	: cGrPerspCamera(id, drawCurr, drawBG,
			 myfovy, myfovymin, myfovymax,
			 myfnear, myffar) {
    }

    void update(tCarElt *car, tSituation *s) {
	tdble A1 = car->_yaw;
	tdble CosA1 = cos(A1);
	tdble SinA1 = sin(A1);
	//tdble A2 = MIN(car->ctrl->steer * 1.5, 0.5) + car->_yaw;
	//tdble CosA2 = cos(A2);
	//tdble SinA2 = sin(A2);
	tdble CosA2 = CosA1;
	tdble SinA2 = SinA1;
	tdble x = car->_pos_X + 30.0 * CosA2;
	tdble y = car->_pos_Y + 30.0 * SinA2;

	tdble X = car->_pos_X + CosA1 * car->_drvPos_x - SinA1 * car->_drvPos_y;
	tdble Y = car->_pos_Y + SinA1 * car->_drvPos_x + CosA1 * car->_drvPos_y;
	tdble Z = car->_pos_Z + car->_drvPos_z;
	eye[0] = X;
	eye[1] = Y;
	eye[2] = Z;
	center[0] = x;
	center[1] = y;
	center[2] = RtTrackHeightG(car->_trkPos.seg, x, y) + 1.5;
	up[0] = car->_posMat[2][0];
	up[1] = car->_posMat[2][1];
	up[2] = car->_posMat[2][2];
    }
};


class cGrCarCamBehind : public cGrPerspCamera
{
    tdble PreA;

 protected:
    float dist;
    
 public:
    cGrCarCamBehind(int id, int drawCurr, int drawBG,
		    float fovy, float fovymin, float fovymax,
		    float mydist, float fnear, float ffar = 1500.0)
	: cGrPerspCamera(id, drawCurr, drawBG, fovy, fovymin,
			 fovymax, fnear, ffar) {
	dist = mydist;
	PreA = 0.0;
	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }
    
    void update(tCarElt *car, tSituation *s) {
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
	x = car->_pos_X - dist * CosA;
	y = car->_pos_Y - dist * SinA;
    
	eye[0] = x;
	eye[1] = y;
	eye[2] = RtTrackHeightG(car->_trkPos.seg, x, y) + 2.0;
	center[0] = car->_pos_X;
	center[1] = car->_pos_Y;
	center[2] = car->_pos_Z;
    }
};


class cGrCarCamBehind2 : public cGrPerspCamera
{
    tdble PreA;

 protected:
    float dist;
    
 public:
    cGrCarCamBehind2(int id, int drawCurr, int drawBG,
		    float fovy, float fovymin, float fovymax,
		    float mydist, float fnear, float ffar = 1500.0)
	: cGrPerspCamera(id, drawCurr, drawBG, fovy, fovymin,
			 fovymax, fnear, ffar) {
	dist = mydist;
	PreA = 0.0;
	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }
    
    void update(tCarElt *car, tSituation *s) {
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
    
	eye[0] = x;
	eye[1] = y;
	eye[2] = RtTrackHeightG(car->_trkPos.seg, x, y) + 5.0;
	center[0] = car->_pos_X;
	center[1] = car->_pos_Y;
	center[2] = car->_pos_Z;
    }
};


class cGrCarCamFront : public cGrPerspCamera
{
protected:
    float dist;
    
 public:
    cGrCarCamFront(int id, int drawCurr, int drawBG,
		   float fovy, float fovymin, float fovymax,
		   float mydist, float fnear, float ffar = 1500.0)
	: cGrPerspCamera(id, drawCurr, drawBG, fovy, fovymin,
			 fovymax, fnear, ffar) {
	dist = mydist;
	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }
    
    void update(tCarElt *car, tSituation *s) {
	tdble CosA = cos(car->_yaw);
	tdble SinA = sin(car->_yaw);
	tdble x = car->_pos_X + dist * CosA;
	tdble y = car->_pos_Y + dist * SinA;

	eye[0] = x;
	eye[1] = y;
	eye[2] = RtTrackHeightG(car->_trkPos.seg, x, y) + 0.5;
	center[0] = car->_pos_X;
	center[1] = car->_pos_Y;
	center[2] = car->_pos_Z;
    }
};


class cGrCarCamSide : public cGrPerspCamera
{
protected:
    float distx;
    float disty;
    float distz;
    
 public:
    cGrCarCamSide(int id, int drawCurr, int drawBG,
		  float fovy, float fovymin, float fovymax,
		  float mydistx, float mydisty, float mydistz,
		  float fnear, float ffar = 1500.0)
	: cGrPerspCamera(id, drawCurr, drawBG, fovy, fovymin,
			 fovymax, fnear, ffar) {
	distx = mydistx;
	disty = mydisty;
	distz = mydistz;

	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }
    
    void update(tCarElt *car, tSituation *s) {
	tdble x = car->_pos_X + distx;
	tdble y = car->_pos_Y + disty;
	tdble z = car->_pos_Z + distz;
    
	eye[0] = x;
	eye[1] = y;
	eye[2] = z;
	center[0] = car->_pos_X;
	center[1] = car->_pos_Y;
	center[2] = car->_pos_Z;
    }
};

class cGrCarCamUp : public cGrPerspCamera
{
protected:
    float distz;
    
 public:
    cGrCarCamUp(int id, int drawCurr, int drawBG,
		float fovy, float fovymin, float fovymax,
		float mydistz, int axis,
		float fnear, float ffar = 1500.0)
	: cGrPerspCamera(id, drawCurr, drawBG, fovy, fovymin,
			 fovymax, fnear, ffar) {
	distz = mydistz;
	up[2] = 0;
	switch (axis) {
	case 0:
	    up[0] = 0;
	    up[1] = 1;
	    break;
	case 1:
	    up[0] = 0;
	    up[1] = -1;
	    break;
	case 2:
	    up[0] = 1;
	    up[1] = 0;
	    break;
	case 3:
	    up[0] = -1;
	    up[1] = 0;
	    break;
	default:
	    up[0] = 0;
	    up[1] = 1;
	    break;
	}
    }
    
    void update(tCarElt *car, tSituation *s) {
	tdble x = car->_pos_X;
	tdble y = car->_pos_Y;
	tdble z = car->_pos_Z + distz;
    
	eye[0] = x;
	eye[1] = y;
	eye[2] = z;
	center[0] = x;
	center[1] = y;
	center[2] = car->_pos_Z;
    }
};

class cGrCarCamCenter : public cGrPerspCamera
{
protected:
    float distz;
    float locfar;
    float locfovy;
    
 public:
    cGrCarCamCenter(int id, int drawCurr, int drawBG,
		    float fovy, float fovymin, float fovymax,
		    float mydistz,
		    float fnear, float ffar = 1500.0)
	: cGrPerspCamera(id, drawCurr, drawBG, fovy, fovymin,
			 fovymax, fnear, ffar) {
	distz = mydistz;
	locfar = ffar;
	locfovy = fovy;

	eye[0] = grWrldX * 0.5;
	eye[1] = grWrldY * 0.6;
	eye[2] = distz;

	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }

    void setZoom(int cmd) {
	fovy = locfovy;
	cGrPerspCamera::setZoom(cmd);
	locfovy = fovy;
    }
    
    void update(tCarElt *car, tSituation *s) {
	tdble	dx, dy, dz, dd;
	
	center[0] = car->_pos_X;
	center[1] = car->_pos_Y;
	center[2] = car->_pos_Z;

	dx = center[0] - eye[0];
	dy = center[1] - eye[1];
	dz = center[2] - eye[2];
    
	dd = sqrt(dx*dx+dy*dy+dz*dz);
    
	fnear = dz - 5;
	if (fnear < 1) {
	    fnear = 1;
	}
	ffar  = dd + locfar;

	fovy = RAD2DEG(atan2(locfovy, dd));
    }
};

class cGrCarCamLookAt : public cGrPerspCamera
{
 protected:
    
 public:
    cGrCarCamLookAt(int id, int drawCurr, int drawBG,
		    float fovy, float fovymin, float fovymax,
		    int axis,
		    float eyex, float eyey, float eyez,
		    float centerx, float centery, float centerz,
		    float fnear, float ffar = 1500.0)
	: cGrPerspCamera(id, drawCurr, drawBG, fovy, fovymin,
			 fovymax, fnear, ffar) {

	eye[0] = eyex;
	eye[1] = eyey;
	eye[2] = eyez;

	center[0] = centerx;
	center[1] = centery;
	center[2] = centerz;
	
	switch (axis) {
	case 0:
	    up[0] = 0;
	    up[1] = 1;
	    up[2] = 0;
	    break;
	case 1:
	    up[0] = 0;
	    up[1] = -1;
	    up[2] = 0;
	    break;
	case 2:
	    up[0] = 1;
	    up[1] = 0;
	    up[2] = 0;
	    break;
	case 3:
	    up[0] = -1;
	    up[1] = 0;
	    up[2] = 0;
	    break;
	case 4:
	    up[0] = 0;
	    up[1] = 0;
	    up[2] = 1;
	    break;
	case 5:
	    up[0] = 0;
	    up[1] = 0;
	    up[2] = -1;
	    break;
	default:
	    up[0] = 0;
	    up[1] = 0;
	    up[2] = 1;
	    break;
	}
    }
    
    void update(tCarElt *car, tSituation *s) {
    }
};


class cGrCarCamRoadNoZoom : public cGrPerspCamera
{
 protected:
    
 public:
    cGrCarCamRoadNoZoom(int id, int drawCurr, int drawBG,
			float fovy, float fovymin, float fovymax,
			float fnear, float ffar = 1500.0)
	: cGrPerspCamera(id, drawCurr, drawBG, fovy, fovymin,
			 fovymax, fnear, ffar) {
	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }
    
    void update(tCarElt *car, tSituation *s) {
	tRoadCam *curCam;

	curCam = car->_trkPos.seg->cam;
    
	if (curCam == NULL) {
	    eye[0] = grWrldX * 0.5;
	    eye[1] = grWrldY * 0.6;
	    eye[2] = 120;
	} else {
	    eye[0] = curCam->pos.x;
	    eye[1] = curCam->pos.y;
	    eye[2] = curCam->pos.z;
	}
	
	center[0] = car->_pos_X;
	center[1] = car->_pos_Y;
	center[2] = car->_pos_Z;
    }
};

class cGrCarCamRoadZoom : public cGrPerspCamera
{
 protected:
    float locfar;
    float locfovy;
    
 public:
    cGrCarCamRoadZoom(int id, int drawCurr, int drawBG,
		      float fovy, float fovymin, float fovymax,
		      float fnear, float ffar = 1500.0)
	: cGrPerspCamera(id, drawCurr, drawBG, fovy, fovymin,
			 fovymax, fnear, ffar) {
	locfar = ffar;
	locfovy = fovy;

	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }

    void setZoom(int cmd) {
	fovy = locfovy;
	cGrPerspCamera::setZoom(cmd);
	locfovy = fovy;
    }
    
    void update(tCarElt *car, tSituation *s) {
	tdble	dx, dy, dz, dd;
	tRoadCam *curCam;

	curCam = car->_trkPos.seg->cam;
    
	if (curCam == NULL) {
	    eye[0] = grWrldX * 0.5;
	    eye[1] = grWrldY * 0.6;
	    eye[2] = 120;

	} else {
	    eye[0] = curCam->pos.x;
	    eye[1] = curCam->pos.y;
	    eye[2] = curCam->pos.z;
	}
	
	center[0] = car->_pos_X;
	center[1] = car->_pos_Y;
	center[2] = car->_pos_Z;

	dx = center[0] - eye[0];
	dy = center[1] - eye[1];
	dz = center[2] - eye[2];
    
	dd = sqrt(dx*dx+dy*dy+dz*dz);

	fnear = dz - 5;
	if (fnear < 1) {
	    fnear = 1;
	}
	ffar  = dd + locfar;
	fovy = RAD2DEG(atan2(locfovy, dd));
    }
};

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

typedef struct 
{
    double	prio;
    int		viewable;
    int		event;
} tSchedView;

class cGrCarCamRoadZoomTVD : public cGrCarCamRoadZoom
{
    tSchedView *schedView;
    double camChangeInterval;
    double camEventInterval;
    double lastEventTime;
    double lastViewTime;
    tdble  proximityThld;

 public:
    cGrCarCamRoadZoomTVD(int id, int drawCurr, int drawBG,
			 float fovy, float fovymin, float fovymax,
			 float fnear, float ffar = 1500.0)
	: cGrCarCamRoadZoom(id, drawCurr, drawBG, fovy, fovymin,
			    fovymax, fnear, ffar) {
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
    
    void update(tCarElt *car, tSituation *s) {
	int	i, j;
	int	curCar;
	double	curPrio;
	double	deltaEventTime = s->currentTime - lastEventTime;
	double	deltaViewTime = s->currentTime - lastViewTime;
	int	event = 0;
    
	/* Track events */
	if (deltaEventTime > camEventInterval) {

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
	}
	
	car = s->cars[s->current];

	cGrCarCamRoadZoom::update(car, s);
    }
};

void
grInitCams(void)
{
    int		id;
    int		c;
    cGrCamera	*curCam;

    if (grBoardCam == NULL) {
	grBoardCam = new cGrOrthoCamera(scrx, scrx + scrw, scry, scry + scrh);
    }
    
    /* Scene Cameras */
    memset(grCams, 0, sizeof(grCams));
    c = 0;

    /* F2 */
    TAILQ_INIT(&grCams[c]);
    id = 0;
    
    /* cam F2 = behind near */
    curCam = new cGrCarCamBehind(id,
				 1,	/* drawCurr */
				 1,	/* drawBG  */
				 40.0,	/* fovy */
				 5.0,	/* fovymin */
				 95.0,	/* fovymax */
				 10.0,	/* dist */
				 1.0	/* near */
				 );
    curCam->add(&grCams[c]);
    id++;
    
    /* cam F2 = behind far */
    curCam = new cGrCarCamBehind(id,
				 1,	/* drawCurr */
				 1,	/* drawBG  */
				 40.0,	/* fovy */
				 5.0,	/* fovymin */
				 95.0,	/* fovymax */
				 20.0,	/* dist */
				 1.0	/* near */
				 );
    curCam->add(&grCams[c]);
    id++;
    
    /* cam F2 = car inside with car (bonnet view) */
    curCam = new cGrCarCamInside(id,
				 1,	/* drawCurr */
				 1,	/* drawBG  */
				 67.5,	/* fovy */
				 50.0,	/* fovymin */
				 95.0,	/* fovymax */
				 0.3	/* near */
				 );
    curCam->add(&grCams[c]);
    id++;
    
    /* cam F2 = car inside with car (bonnet view) fixed to the car */
    curCam = new cGrCarCamInsideFixedCar(id,
					 1,	/* drawCurr */
					 1,	/* drawBG  */
					 67.5,	/* fovy */
					 50.0,	/* fovymin */
					 95.0,	/* fovymax */
					 0.3	/* near */
					 );
    curCam->add(&grCams[c]);
    id++;

    /* cam F2 = car inside car (no car - road view) */
    curCam = new cGrCarCamInside(id,
				 0,	/* drawCurr */
				 1,	/* drawBG  */
				 67.5,	/* fovy */
				 50.0,	/* fovymin */
				 95.0,	/* fovymax */
				 0.3	/* near */
				 );
    curCam->add(&grCams[c]);

    /* F3 */
    c++;
    TAILQ_INIT(&grCams[c]);
    id = 0;

    /* cam F3 = car behind*/
    curCam = new cGrCarCamBehind2(id,
				  1,	/* drawCurr */
				  1,	/* drawBG  */
				  40.0,	/* fovy */
				  5.0,	/* fovymin */
				  95.0,	/* fovymax */
				  30.0,	/* dist */
				  1.0	/* near */
				  );
    curCam->add(&grCams[c]);
    id++;

    /* cam F3 = car reverse*/
    curCam = new cGrCarCamFront(id,
				1,	/* drawCurr */
				1,	/* drawBG  */
				30.0,	/* fovy */
				5.0,	/* fovymin */
				95.0,	/* fovymax */
				20.0,	/* dist */
				1.0	/* near */
				);
    curCam->add(&grCams[c]);

    /* F4 */
    c++;
    TAILQ_INIT(&grCams[c]);
    id = 0;

    /* cam F4 = car side 1*/
    curCam = new cGrCarCamSide(id,
			       1,	/* drawCurr */
			       1,	/* drawBG  */
			       30.0,	/* fovy */
			       5.0,	/* fovymin */
			       60.0,	/* fovymax */
			       0.0,	/* distx */
			       -20.0,	/* disty */
			       3.0,	/* distz */
			       1.0	/* near */
			       );
    curCam->add(&grCams[c]);
    id++;

    /* cam F4 = car side 2*/
    curCam = new cGrCarCamSide(id,
			       1,	/* drawCurr */
			       1,	/* drawBG  */
			       30.0,	/* fovy */
			       5.0,	/* fovymin */
			       60.0,	/* fovymax */
			       0.0,	/* distx */
			       20.0,	/* disty */
			       3.0,	/* distz */
			       1.0	/* near */
			       );
    curCam->add(&grCams[c]);
    id++;

    /* cam F4 = car side 3*/
    curCam = new cGrCarCamSide(id,
			       1,	/* drawCurr */
			       1,	/* drawBG  */
			       30.0,	/* fovy */
			       5.0,	/* fovymin */
			       60.0,	/* fovymax */
			       -20.0,	/* distx */
			       0.0,	/* disty */
			       3.0,	/* distz */
			       1.0	/* near */
			       );
    curCam->add(&grCams[c]);
    id++;

    /* cam F4 = car side 4*/
    curCam = new cGrCarCamSide(id,
			       1,	/* drawCurr */
			       1,	/* drawBG  */
			       30.0,	/* fovy */
			       5.0,	/* fovymin */
			       60.0,	/* fovymax */
			       20.0,	/* distx */
			       0.0,	/* disty */
			       3.0,	/* distz */
			       1.0	/* near */
			       );
    curCam->add(&grCams[c]);
    id++;

    /* cam F4 = car side 5*/
    curCam = new cGrCarCamSide(id,
			       1,	/* drawCurr */
			       1,	/* drawBG  */
			       30.0,	/* fovy */
			       5.0,	/* fovymin */
			       60.0,	/* fovymax */
			       0.0,	/* distx */
			       -40.0,	/* disty */
			       6.0,	/* distz */
			       1.0	/* near */
			       );
    curCam->add(&grCams[c]);
    id++;

    /* cam F4 = car side 6*/
    curCam = new cGrCarCamSide(id,
			       1,	/* drawCurr */
			       1,	/* drawBG  */
			       30.0,	/* fovy */
			       5.0,	/* fovymin */
			       60.0,	/* fovymax */
			       0.0,	/* distx */
			       40.0,	/* disty */
			       6.0,	/* distz */
			       1.0	/* near */
			       );
    curCam->add(&grCams[c]);
    id++;

    /* cam F4 = car side 7*/
    curCam = new cGrCarCamSide(id,
			       1,	/* drawCurr */
			       1,	/* drawBG  */
			       30.0,	/* fovy */
			       5.0,	/* fovymin */
			       60.0,	/* fovymax */
			       -40.0,	/* distx */
			       0.0,	/* disty */
			       6.0,	/* distz */
			       1.0	/* near */
			       );
    curCam->add(&grCams[c]);
    id++;

    /* cam F4 = car side 8*/
    curCam = new cGrCarCamSide(id,
			       1,	/* drawCurr */
			       1,	/* drawBG  */
			       30.0,	/* fovy */
			       5.0,	/* fovymin */
			       60.0,	/* fovymax */
			       40.0,	/* distx */
			       0.0,	/* disty */
			       6.0,	/* distz */
			       1.0	/* near */
			       );
    curCam->add(&grCams[c]);

    /* F5 */
    c++;
    TAILQ_INIT(&grCams[c]);
    id = 0;

    /* cam F5 = car up 1*/
    curCam = new cGrCarCamUp(id,
			     1,	/* drawCurr */
			     1,	/* drawBG  */
			     30.0,	/* fovy */
			     1.0,	/* fovymin */
			     60.0,	/* fovymax */
			     300.0,	/* distz */
			     0,		/* axis */
			     200.0	/* near */
			     );
    curCam->add(&grCams[c]);
    id++;

    /* cam F5 = car up 2*/
    curCam = new cGrCarCamUp(id,
			     1,	/* drawCurr */
			     1,	/* drawBG  */
			     30.0,	/* fovy */
			     1.0,	/* fovymin */
			     60.0,	/* fovymax */
			     300.0,	/* distz */
			     1,		/* axis */
			     200.0	/* near */
			     );
    curCam->add(&grCams[c]);
    id++;

    /* cam F5 = car up 3*/
    curCam = new cGrCarCamUp(id,
			     1,	/* drawCurr */
			     1,	/* drawBG  */
			     30.0,	/* fovy */
			     1.0,	/* fovymin */
			     60.0,	/* fovymax */
			     300.0,	/* distz */
			     2,		/* axis */
			     200.0	/* near */
			     );
    curCam->add(&grCams[c]);
    id++;

    /* cam F5 = car up 4*/
    curCam = new cGrCarCamUp(id,
			     1,	/* drawCurr */
			     1,	/* drawBG  */
			     30.0,	/* fovy */
			     1.0,	/* fovymin */
			     60.0,	/* fovymax */
			     300.0,	/* distz */
			     3,		/* axis */
			     200.0	/* near */
			     );
    curCam->add(&grCams[c]);

    /* F6 */
    c++;
    TAILQ_INIT(&grCams[c]);
    id = 0;

    /* cam F6 = car from circuit centre */
    curCam = new cGrCarCamCenter(id,
				 1,	/* drawCurr */
				 1,	/* drawBG  */
				 21.0,	/* fovy */
				 2.0,	/* fovymin */
				 60.0,	/* fovymax */
				 120.0,	/* distz */
				 100.0	/* near */
				 );
    curCam->add(&grCams[c]);

    /* F7 */
    c++;
    TAILQ_INIT(&grCams[c]);
    id = 0;

    /* cam F7 = panoramic */
    curCam = new cGrCarCamLookAt(id,
				 1,		/* drawCurr */
				 0,		/* drawBG  */
				 74.0,		/* fovy */
				 1.0,		/* fovymin */
				 110.0,		/* fovymax */
				 0,		/* up axis */
				 grWrldX/2,	/* eyex */
				 grWrldY/2,	/* eyey */
				 MAX(grWrldX/2, grWrldY*4/3/2) + grWrldZ, /* eyez */
				 grWrldX/2,	/* centerx */
				 grWrldY/2,	/* centery */
				 0,		/* centerz */
				 10.0,		/* near */
				 grWrldMaxSize	/* far */
				 );
    curCam->add(&grCams[c]);
    id++;

    /* cam F7 = panoramic */
    curCam = new cGrCarCamLookAt(id,
				 1,		/* drawCurr */
				 0,		/* drawBG  */
				 74.0,		/* fovy */
				 1.0,		/* fovymin */
				 110.0,		/* fovymax */
				 4,		/* up axis */
				 -grWrldX/2,	/* eyex */
				 -grWrldY/2,	/* eyey */
				 0.25 * sqrt(grWrldX*grWrldX+grWrldY*grWrldY), /* eyez */
				 grWrldX/2,	/* centerx */
				 grWrldY/2,	/* centery */
				 0,		/* centerz */
				 10.0,		/* near */
				 2 * grWrldMaxSize	/* far */
				 );
    curCam->add(&grCams[c]);
    id++;

    /* cam F7 = panoramic */
    curCam = new cGrCarCamLookAt(id,
				 1,		/* drawCurr */
				 0,		/* drawBG  */
				 74.0,		/* fovy */
				 1.0,		/* fovymin */
				 110.0,		/* fovymax */
				 4,		/* up axis */
				 -grWrldX/2,	/* eyex */
				 grWrldY * 3/2,	/* eyey */
				 0.25 * sqrt(grWrldX*grWrldX+grWrldY*grWrldY), /* eyez */
				 grWrldX/2,	/* centerx */
				 grWrldY/2,	/* centery */
				 0,		/* centerz */
				 10.0,		/* near */
				 2 * grWrldMaxSize	/* far */
				 );
    curCam->add(&grCams[c]);
    id++;

    /* cam F7 = panoramic */
    curCam = new cGrCarCamLookAt(id,
				 1,		/* drawCurr */
				 0,		/* drawBG  */
				 74.0,		/* fovy */
				 1.0,		/* fovymin */
				 110.0,		/* fovymax */
				 4,		/* up axis */
				 grWrldX * 3/2,	/* eyex */
				 grWrldY * 3/2,	/* eyey */
				 0.25 * sqrt(grWrldX*grWrldX+grWrldY*grWrldY), /* eyez */
				 grWrldX/2,	/* centerx */
				 grWrldY/2,	/* centery */
				 0,		/* centerz */
				 10.0,		/* near */
				 2 * grWrldMaxSize	/* far */
				 );
    curCam->add(&grCams[c]);
    id++;

    /* cam F7 = panoramic */
    curCam = new cGrCarCamLookAt(id,
				 1,		/* drawCurr */
				 0,		/* drawBG  */
				 74.0,		/* fovy */
				 1.0,		/* fovymin */
				 110.0,		/* fovymax */
				 4,		/* up axis */
				 grWrldX * 3/2,	/* eyex */
				 -grWrldY/2,	/* eyey */
				 0.25 * sqrt(grWrldX*grWrldX+grWrldY*grWrldY), /* eyez */
				 grWrldX/2,	/* centerx */
				 grWrldY/2,	/* centery */
				 0,		/* centerz */
				 10.0,		/* near */
				 2 * grWrldMaxSize	/* far */
				 );
    curCam->add(&grCams[c]);
    id++;

    /* F8 */
    c++;
    TAILQ_INIT(&grCams[c]);
    id = 0;

    /* cam F8 = road cam fixed fov */

    curCam = new cGrCarCamRoadNoZoom(id,
				     1,		/* drawCurr */
				     1,		/* drawBG  */
				     30.0,	/* fovy */
				     5.0,	/* fovymin */
				     60.0,	/* fovymax */
				     1.0	/* near */
				     );
    curCam->add(&grCams[c]);

    /* F9 */
    c++;
    TAILQ_INIT(&grCams[c]);
    id = 0;

    /* cam F9 = road cam zoomed */
    curCam = new cGrCarCamRoadZoom(id,
				   1,		/* drawCurr */
				   1,		/* drawBG  */
				   17.0,	/* fovy */
				   1.0,		/* fovymin */
				   90.0,	/* fovymax */
				   1.0		/* near */
				   );
    curCam->add(&grCams[c]);

    /* F10 */
    c++;
    TAILQ_INIT(&grCams[c]);
    id = 0;

    /* F11 */
    c++;
    TAILQ_INIT(&grCams[c]);
    id = 0;
    curCam = new cGrCarCamRoadZoomTVD(id,
				      1,	/* drawCurr */
				      1,	/* drawBG  */
				      17.0,	/* fovy */
				      1.0,	/* fovymin */
				      90.0,	/* fovymax */
				      1.0	/* near */
				      );
    curCam->add(&grCams[c]);

}

