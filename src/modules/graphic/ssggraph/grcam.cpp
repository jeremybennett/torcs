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
#include "grscreen.h"
#include "grscene.h"
#include "grshadow.h"
#include "grskidmarks.h"
#include "grsmoke.h"
#include "grcar.h"
#include "grmain.h"
#include <tgfclient.h>

static char path[1024];

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


cGrPerspCamera::cGrPerspCamera(class cGrScreen *myscreen, int id, int drawCurr, int drawBG, int mirrorAllowed,
			       float myfovy, float myfovymin, float myfovymax,
			       float myfnear, float myffar, float myfogstart, float myfogend)
    : cGrCamera(myscreen, id, drawCurr, drawBG, mirrorAllowed)
{
    fovy     = myfovy;
    fovymin  = myfovymin;
    fovymax  = myfovymax;
    fnear    = myfnear;
    ffar     = myffar;
    fovydflt = myfovy;
    fogstart = myfogstart;
    fogend   = myfogend;
    
}

void cGrPerspCamera::setProjection(void)
{
    grContext.setFOV(screen->getViewRatio() * fovy, fovy);
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
    sprintf(path, "%s/%d", GR_SCT_DISPMODE, screen->getId());
    fovy = (float)GfParmGetNum(grHandle, path,
			       attr, (char*)NULL, fovydflt);
    limitFov();
}


/* Give the height in pixels of 1 m high object on the screen at this point */
float cGrPerspCamera::getLODFactor(float x, float y, float z) {
    tdble	dx, dy, dz, dd;
    float	ang;
    int		scrh, dummy;
    float	res;

    dx = x - eye[0];
    dy = y - eye[1];
    dz = z - eye[2];

    dd = sqrt(dx*dx+dy*dy+dz*dz);

    ang = DEG2RAD(fovy / 2.0);
    GfScrGetSize(&dummy, &scrh, &dummy, &dummy);
    
    res = (float)scrh / 2.0 / dd / tan(ang);
    if (res < 0) {
	res = 0;
    }
    return res;
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
    }

    limitFov();

    sprintf(buf, "%s-%d-%d", GR_ATT_FOVY, screen->getCurCamHead(), getId());
    sprintf(path, "%s/%d", GR_SCT_DISPMODE, screen->getId());
    GfParmSetNum(grHandle, path, buf, (char*)NULL, (tdble)fovy);
    GfParmWriteFile(NULL, grHandle, "Graph");
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

void cGrBackgroundCam::update(cGrCamera *curCam)
{
    memcpy(&eye, curCam->getPosv(), sizeof(eye));
    memcpy(&center, curCam->getCenterv(), sizeof(center));
    sgSubVec3(center, center, eye);
    sgSetVec3(eye, 0, 0, 0);
    memcpy(&up, curCam->getUpv(), sizeof(up));
}



class cGrCarCamInside : public cGrPerspCamera
{
 public:
    cGrCarCamInside(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
		    float myfovy, float myfovymin, float myfovymax,
		    float myfnear, float myffar = 1500.0,
		    float myfogstart = 800.0, float myfogend = 1500.0)
	: cGrPerspCamera(myscreen, id, drawCurr, drawBG, 1,
			 myfovy, myfovymin, myfovymax,
			 myfnear, myffar, myfogstart, myfogend) {
	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }

    void limitFov(void) {
	if ((screen->getViewRatio() * fovy) > 90.0) {
	    fovy = 90.0 / screen->getViewRatio();
	}
    }

    void update(tCarElt *car, tSituation *s) {
	sgVec3 P, p;
	
	p[0] = car->_drvPos_x;
	p[1] = car->_drvPos_y;
	p[2] = car->_drvPos_z;
	sgXformPnt3(p, car->_posMat);
	
	eye[0] = p[0];
	eye[1] = p[1];
	eye[2] = p[2];

	P[0] = car->_drvPos_x + 30.0;
	P[1] = car->_drvPos_y;
	P[2] = car->_drvPos_z;
	sgXformPnt3(P, car->_posMat);

	center[0] = P[0];
	center[1] = P[1];
	center[2] = P[2];
    }
};


void cGrCarCamMirror::limitFov(void) {
    fovy = 90.0 / screen->getViewRatio();
}

void cGrCarCamMirror::update(tCarElt *car, tSituation *s)
{
    sgVec3 P, p;

    P[0] = car->_drvPos_x;
    P[1] = car->_drvPos_y;
    P[2] = car->_drvPos_z;
    sgXformPnt3(P, car->_posMat);
	
    eye[0] = P[0];
    eye[1] = P[1];
    eye[2] = P[2];
	
    p[0] = car->_drvPos_x - 30.0;
    p[1] = car->_drvPos_y;
    p[2] = car->_drvPos_z;
    sgXformPnt3(p, car->_posMat);

    center[0] = p[0];
    center[1] = p[1];
    center[2] = p[2];

    up[0] = car->_posMat[2][0];
    up[1] = car->_posMat[2][1];
    up[2] = car->_posMat[2][2];
}

class cGrCarCamInsideFixedCar : public cGrPerspCamera
{
 public:
    cGrCarCamInsideFixedCar(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
			    float myfovy, float myfovymin, float myfovymax,
			    float myfnear, float myffar = 1500.0,
			    float myfogstart = 1400.0, float myfogend = 1500.0)
	: cGrPerspCamera(myscreen, id, drawCurr, drawBG, 1,
			 myfovy, myfovymin, myfovymax,
			 myfnear, myffar, myfogstart, myfogend) {
    }

    void limitFov(void) {
	if ((screen->getViewRatio() * fovy) > 90.0) {
	    fovy = 90.0 / screen->getViewRatio();
	}
    }

    void update(tCarElt *car, tSituation *s) {
	sgVec3 P, p;
	
	p[0] = car->_drvPos_x;
	p[1] = car->_drvPos_y;
	p[2] = car->_drvPos_z;
	sgXformPnt3(p, car->_posMat);
	
	eye[0] = p[0];
	eye[1] = p[1];
	eye[2] = p[2];

	P[0] = car->_drvPos_x + 30.0;
	P[1] = car->_drvPos_y;
	P[2] = car->_drvPos_z;
	sgXformPnt3(P, car->_posMat);

	center[0] = P[0];
	center[1] = P[1];
	center[2] = P[2];

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
    cGrCarCamBehind(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
		    float fovy, float fovymin, float fovymax,
		    float mydist, float fnear, float ffar = 1500.0,
		    float myfogstart = 1400.0, float myfogend = 1500.0)
	: cGrPerspCamera(myscreen, id, drawCurr, drawBG, 0, fovy, fovymin,
			 fovymax, fnear, ffar, myfogstart, myfogend) {
	dist = mydist;
	PreA = 0.0;
	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }

    void limitFov(void) {
	if ((screen->getViewRatio() * fovy) > 90.0) {
	    fovy = 90.0 / screen->getViewRatio();
	}
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
    cGrCarCamBehind2(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
		    float fovy, float fovymin, float fovymax,
		    float mydist, float fnear, float ffar = 1500.0,
		    float myfogstart = 1400.0, float myfogend = 1500.0)
	: cGrPerspCamera(myscreen, id, drawCurr, drawBG, 0, fovy, fovymin,
			 fovymax, fnear, ffar, myfogstart, myfogend) {
	dist = mydist;
	PreA = 0.0;
	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }

    void limitFov(void) {
	if ((screen->getViewRatio() * fovy) > 90.0) {
	    fovy = 90.0 / screen->getViewRatio();
	}
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
    cGrCarCamFront(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
		   float fovy, float fovymin, float fovymax,
		   float mydist, float fnear, float ffar = 1500.0,
		   float myfogstart = 1400.0, float myfogend = 1500.0)
	: cGrPerspCamera(myscreen, id, drawCurr, drawBG, 0, fovy, fovymin,
			 fovymax, fnear, ffar, myfogstart, myfogend) {
	dist = mydist;
	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }

    void limitFov(void) {
	if ((screen->getViewRatio() * fovy) > 90.0) {
	    fovy = 90.0 / screen->getViewRatio();
	}
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
    cGrCarCamSide(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
		  float fovy, float fovymin, float fovymax,
		  float mydistx, float mydisty, float mydistz,
		  float fnear, float ffar = 1500.0,
		  float myfogstart = 1400.0, float myfogend = 1500.0)
	: cGrPerspCamera(myscreen, id, drawCurr, drawBG, 0, fovy, fovymin,
			 fovymax, fnear, ffar, myfogstart, myfogend) {
	distx = mydistx;
	disty = mydisty;
	distz = mydistz;

	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }

    void limitFov(void) {
	if ((screen->getViewRatio() * fovy) > 90.0) {
	    fovy = 90.0 / screen->getViewRatio();
	}
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
    cGrCarCamUp(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
		float fovy, float fovymin, float fovymax,
		float mydistz, int axis,
		float fnear, float ffar = 1500.0,
		float myfogstart = 1600.0, float myfogend = 1700.0)
	: cGrPerspCamera(myscreen, id, drawCurr, drawBG, 0, fovy, fovymin,
			 fovymax, fnear, ffar, myfogstart, myfogend) {
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

    void limitFov(void) {
	if ((screen->getViewRatio() * fovy) > 90.0) {
	    fovy = 90.0 / screen->getViewRatio();
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
    cGrCarCamCenter(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
		    float fovy, float fovymin, float fovymax,
		    float mydistz,
		    float fnear, float ffar = 1500.0,
		    float myfogstart = 1400.0, float myfogend = 1500.0)
	: cGrPerspCamera(myscreen, id, drawCurr, drawBG, 0, fovy, fovymin,
			 fovymax, fnear, ffar, myfogstart, myfogend) {
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

    void limitFov(void) {
	if ((screen->getViewRatio() * fovy) > 90.0) {
	    fovy = 90.0 / screen->getViewRatio();
	}
    }

    void loadDefaults(char *attr) {
	sprintf(path, "%s/%d", GR_SCT_DISPMODE, screen->getId());
	locfovy = (float)GfParmGetNum(grHandle, path,
				   attr, (char*)NULL, fovydflt);
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
    cGrCarCamLookAt(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
		    float fovy, float fovymin, float fovymax,
		    int axis,
		    float eyex, float eyey, float eyez,
		    float centerx, float centery, float centerz,
		    float fnear, float ffar = 1500.0,
		    float myfogstart = 1600.0, float myfogend = 1700.0)
	: cGrPerspCamera(myscreen, id, drawCurr, drawBG, 0, fovy, fovymin,
			 fovymax, fnear, ffar, myfogstart, myfogend) {

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

    void limitFov(void) {
	if ((screen->getViewRatio() * fovy) > 90.0) {
	    fovy = 90.0 / screen->getViewRatio();
	}
    }

    void update(tCarElt *car, tSituation *s) {
    }
};


class cGrCarCamRoadNoZoom : public cGrPerspCamera
{
 protected:
    
 public:
    cGrCarCamRoadNoZoom(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
			float fovy, float fovymin, float fovymax,
			float fnear, float ffar = 1500.0,
			float myfogstart = 1400.0, float myfogend = 1500.0)
	: cGrPerspCamera(myscreen, id, drawCurr, drawBG, 0, fovy, fovymin,
			 fovymax, fnear, ffar, myfogstart, myfogend) {
	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }

    void limitFov(void) {
	if ((screen->getViewRatio() * fovy) > 90.0) {
	    fovy = 90.0 / screen->getViewRatio();
	}
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
    cGrCarCamRoadZoom(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
		      float fovy, float fovymin, float fovymax,
		      float fnear, float ffar = 1500.0,
		      float myfogstart = 1400.0, float myfogend = 1500.0)
	: cGrPerspCamera(myscreen, id, drawCurr, drawBG, 0, fovy, fovymin,
			 fovymax, fnear, ffar, myfogstart, myfogend) {
	locfar = ffar;
	locfovy = fovy;

	up[0] = 0;
	up[1] = 0;
	up[2] = 1;
    }

    void limitFov(void) {
	if ((screen->getViewRatio() * fovy) > 90.0) {
	    fovy = 90.0 / screen->getViewRatio();
	}
    }

    void loadDefaults(char *attr) {
	sprintf(path, "%s/%d", GR_SCT_DISPMODE, screen->getId());
	locfovy = (float)GfParmGetNum(grHandle, path,
				   attr, (char*)NULL, fovydflt);
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
	limitFov();
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
    int		current;

 public:
    cGrCarCamRoadZoomTVD(class cGrScreen *myscreen, int id, int drawCurr, int drawBG,
			 float fovy, float fovymin, float fovymax,
			 float fnear, float ffar = 1500.0,
			 float myfogstart = 1400.0, float myfogend = 1500.0)
	: cGrCarCamRoadZoom(myscreen, id, drawCurr, drawBG, fovy, fovymin,
			    fovymax, fnear, ffar, myfogstart, myfogend) {
	schedView = (tSchedView *)calloc(grNbCars, sizeof(tSchedView));
	if (!schedView) {
	    GfTrace("malloc error");
	    GfScrShutdown();
	    exit (1);
	}
    
	lastEventTime = 0;
	lastViewTime = 0;

	current = -1;

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

	if (current == -1) {
	    current = 0;
	    for (i = 0; i < grNbCars; i++) {
		if (car == s->cars[i]) {
		    current = i;
		    break;
		}
	    }
	}
	
    
	/* Track events */
	if (deltaEventTime > camEventInterval) {

	    memset(schedView, 0, grNbCars * sizeof(tSchedView));
	    for (i = 0; i < grNbCars; i++) {
		schedView[i].viewable = 1;
	    }
	    
	    for (i = 0; i < GR_NB_MAX_SCREEN; i++) {
		if ((screen != grScreens[i]) && grScreens[i]->isActive()) {
		    car = grScreens[i]->getCurrentCar();
		    schedView[car->index].viewable = 0;
		    schedView[car->index].prio -= 10000;
		}
	    }
	    
	    for (i = 0; i < grNbCars; i++) {
		tdble dist, fs;

		car = s->cars[i];
		schedView[car->index].prio += grNbCars - i;
		fs = GetDistToStart(car);
		if ((car->_state & RM_CAR_STATE_NO_SIMU) != 0) {
		    schedView[car->index].viewable = 0;
		} else {
		    if ((fs > (grTrack->length - 200.0)) && (car->_remainingLaps == 0)) {
			schedView[car->index].prio += 5 * grNbCars;
			event = 1;
		    }
		}
	
		if ((car->_state & RM_CAR_STATE_NO_SIMU) == 0) {
		    dist = fabs(car->_trkPos.toMiddle) - grTrack->width / 2.0;
		    /* out of track */
		    if (dist > 0) {
			schedView[car->index].prio += grNbCars;
			if (car->ctrl.raceCmd & RM_CMD_PIT_ASKED) {
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
				if (i == 0) {
				    event = 1;
				}
			    }
			}
		    }

		    if (car->priv.collision) {
			schedView[car->index].prio += grNbCars;
			event = 1;
		    }
		} else {
		    if (i == current) {
			event = 1;	/* update view */
		    }
		}
	    }


	    /* change current car */
	    if ((event && (deltaEventTime > camEventInterval)) || (deltaViewTime > camChangeInterval)) {
		int	last_current = current;

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
			current = i;
			break;
		    }
		}
		if (last_current != current) {
		    lastEventTime = s->currentTime;
		    lastViewTime = s->currentTime;

		    for (i = 0; i < grNbCars; i++) {
			s->cars[i]->priv.collision = 0;
		    }
		}
	    }
	}

	screen->setCurrentCar(s->cars[current]);
	
	cGrCarCamRoadZoom::update(s->cars[current], s);
    }
};


void
grCamCreateSceneCameraList(class cGrScreen *myscreen, tGrCamHead *cams, tdble fovFactor)
{
    int			id;
    int			c;
    class cGrCamera	*cam;
    
    /* Scene Cameras */
    c = 0;

    /* F2 */
    GF_TAILQ_INIT(&cams[c]);
    id = 0;
    
    /* cam F2 = behind near */
    cam = new cGrCarCamBehind(myscreen,
			      id,
			      1,	/* drawCurr */
			      1,	/* drawBG  */
			      40.0,	/* fovy */
			      5.0,	/* fovymin */
			      95.0,	/* fovymax */
			      10.0,	/* dist */
			      1.0,	/* near */
			      600.0 * fovFactor,	/* far */
			      300.0 * fovFactor,	/* fog */
			      600.0 * fovFactor	/* fog */
			      );
    cam->add(&cams[c]);
    id++;
    
    /* cam F2 = behind far */
    cam = new cGrCarCamBehind(myscreen,
			      id,
			      1,	/* drawCurr */
			      1,	/* drawBG  */
			      40.0,	/* fovy */
			      5.0,	/* fovymin */
			      95.0,	/* fovymax */
			      20.0,	/* dist */
			      1.0,	/* near */
			      600.0 * fovFactor,	/* far */
			      300.0 * fovFactor,	/* fog */
			      600.0 * fovFactor	/* fog */
			      );
    cam->add(&cams[c]);
    id++;
    
    /* cam F2 = car inside with car (bonnet view) */
    cam = new cGrCarCamInside(myscreen,
			      id,
			      1,	/* drawCurr */
			      1,	/* drawBG  */
			      67.5,	/* fovy */
			      50.0,	/* fovymin */
			      95.0,	/* fovymax */
			      0.3,	/* near */
			      600.0 * fovFactor,	/* far */
			      300.0 * fovFactor,	/* fog */
			      600.0 * fovFactor	/* fog */
			      );
    cam->add(&cams[c]);
    id++;
    
    /* cam F2 = car inside with car (bonnet view) fixed to the car */
    cam = new cGrCarCamInsideFixedCar(myscreen,
				      id,
				      1,	/* drawCurr */
				      1,	/* drawBG  */
				      67.5,	/* fovy */
				      50.0,	/* fovymin */
				      95.0,	/* fovymax */
				      0.3,	/* near */
				      600.0 * fovFactor,	/* far */
				      300.0 * fovFactor,	/* fog */
				      600.0 * fovFactor	/* fog */
				      );
    cam->add(&cams[c]);
    id++;

    /* cam F2 = car inside car (no car - road view) */
    cam = new cGrCarCamInsideFixedCar(myscreen,
				      id,
				      0,	/* drawCurr */
				      1,	/* drawBG  */
				      67.5,	/* fovy */
				      50.0,	/* fovymin */
				      95.0,	/* fovymax */
				      0.3,	/* near */
				      600.0 * fovFactor,	/* far */
				      300.0 * fovFactor,	/* fog */
				      600.0 * fovFactor	/* fog */
				      );
    cam->add(&cams[c]);

    /* F3 */
    c++;
    GF_TAILQ_INIT(&cams[c]);
    id = 0;

    /* cam F3 = car behind*/
    cam = new cGrCarCamBehind2(myscreen,
			       id,
			       1,	/* drawCurr */
			       1,	/* drawBG  */
			       40.0,	/* fovy */
			       5.0,	/* fovymin */
			       95.0,	/* fovymax */
			       30.0,	/* dist */
			       1.0,	/* near */
			       1000.0 * fovFactor,	/* far */
			       500.0 * fovFactor,	/* fog */
			       1000.0 * fovFactor	/* fog */
			       );
    cam->add(&cams[c]);
    id++;

    /* cam F3 = car reverse*/
    cam = new cGrCarCamFront(myscreen,
			     id,
			     1,	/* drawCurr */
			     1,	/* drawBG  */
			     30.0,	/* fovy */
			     5.0,	/* fovymin */
			     95.0,	/* fovymax */
			     20.0,	/* dist */
			     1.0,	/* near */
			     1000.0 * fovFactor,	/* far */
			     500.0 * fovFactor,	/* fog */
			     1000.0 * fovFactor	/* fog */
			     );
    cam->add(&cams[c]);

    /* F4 */
    c++;
    GF_TAILQ_INIT(&cams[c]);
    id = 0;

    /* cam F4 = car side 1*/
    cam = new cGrCarCamSide(myscreen,
			    id,
			    1,	/* drawCurr */
			    1,	/* drawBG  */
			    30.0,	/* fovy */
			    5.0,	/* fovymin */
			    60.0,	/* fovymax */
			    0.0,	/* distx */
			    -20.0,	/* disty */
			    3.0,	/* distz */
			    1.0,	/* near */
			    1000.0 * fovFactor,	/* far */
			    500.0 * fovFactor,	/* fog */
			    1000.0 * fovFactor	/* fog */
			    );
    cam->add(&cams[c]);
    id++;

    /* cam F4 = car side 2*/
    cam = new cGrCarCamSide(myscreen,
			    id,
			    1,	/* drawCurr */
			    1,	/* drawBG  */
			    30.0,	/* fovy */
			    5.0,	/* fovymin */
			    60.0,	/* fovymax */
			    0.0,	/* distx */
			    20.0,	/* disty */
			    3.0,	/* distz */
			    1.0,	/* near */
			    1000.0 * fovFactor,	/* far */
			    500.0 * fovFactor,	/* fog */
			    1000.0 * fovFactor	/* fog */
			    );
    cam->add(&cams[c]);
    id++;

    /* cam F4 = car side 3*/
    cam = new cGrCarCamSide(myscreen,
			    id,
			    1,	/* drawCurr */
			    1,	/* drawBG  */
			    30.0,	/* fovy */
			    5.0,	/* fovymin */
			    60.0,	/* fovymax */
			    -20.0,	/* distx */
			    0.0,	/* disty */
			    3.0,	/* distz */
			    1.0,	/* near */
			    1000.0 * fovFactor,	/* far */
			    500.0 * fovFactor,	/* fog */
			    1000.0 * fovFactor	/* fog */
			    );
    cam->add(&cams[c]);
    id++;

    /* cam F4 = car side 4*/
    cam = new cGrCarCamSide(myscreen,
			    id,
			    1,	/* drawCurr */
			    1,	/* drawBG  */
			    30.0,	/* fovy */
			    5.0,	/* fovymin */
			    60.0,	/* fovymax */
			    20.0,	/* distx */
			    0.0,	/* disty */
			    3.0,	/* distz */
			    1.0,	/* near */
			    1000.0 * fovFactor,	/* far */
			    500.0 * fovFactor,	/* fog */
			    1000.0 * fovFactor	/* fog */
			    );
    cam->add(&cams[c]);
    id++;

    /* cam F4 = car side 5*/
    cam = new cGrCarCamSide(myscreen,
			    id,
			    1,	/* drawCurr */
			    1,	/* drawBG  */
			    30.0,	/* fovy */
			    5.0,	/* fovymin */
			    60.0,	/* fovymax */
			    0.0,	/* distx */
			    -40.0,	/* disty */
			    6.0,	/* distz */
			    1.0,	/* near */
			    1000.0 * fovFactor,	/* far */
			    500.0 * fovFactor,	/* fog */
			    1000.0 * fovFactor	/* fog */
			    );
    cam->add(&cams[c]);
    id++;

    /* cam F4 = car side 6*/
    cam = new cGrCarCamSide(myscreen,
			    id,
			    1,	/* drawCurr */
			    1,	/* drawBG  */
			    30.0,	/* fovy */
			    5.0,	/* fovymin */
			    60.0,	/* fovymax */
			    0.0,	/* distx */
			    40.0,	/* disty */
			    6.0,	/* distz */
			    1.0,	/* near */
			    1000.0 * fovFactor,	/* far */
			    500.0 * fovFactor,	/* fog */
			    1000.0 * fovFactor	/* fog */
			    );
    cam->add(&cams[c]);
    id++;

    /* cam F4 = car side 7*/
    cam = new cGrCarCamSide(myscreen,
			    id,
			    1,	/* drawCurr */
			    1,	/* drawBG  */
			    30.0,	/* fovy */
			    5.0,	/* fovymin */
			    60.0,	/* fovymax */
			    -40.0,	/* distx */
			    0.0,	/* disty */
			    6.0,	/* distz */
			    1.0,	/* near */
			    1000.0 * fovFactor,	/* far */
			    500.0 * fovFactor,	/* fog */
			    1000.0 * fovFactor	/* fog */
			    );
    cam->add(&cams[c]);
    id++;

    /* cam F4 = car side 8*/
    cam = new cGrCarCamSide(myscreen,
			    id,
			    1,	/* drawCurr */
			    1,	/* drawBG  */
			    30.0,	/* fovy */
			    5.0,	/* fovymin */
			    60.0,	/* fovymax */
			    40.0,	/* distx */
			    0.0,	/* disty */
			    6.0,	/* distz */
			    1.0,	/* near */
			    1000.0 * fovFactor,	/* far */
			    500.0 * fovFactor,	/* fog */
			    1000.0 * fovFactor	/* fog */
			    );
    cam->add(&cams[c]);

    /* F5 */
    c++;
    GF_TAILQ_INIT(&cams[c]);
    id = 0;

    /* cam F5 = car up 1*/
    cam = new cGrCarCamUp(myscreen,
			  id,
			  1,	/* drawCurr */
			  1,	/* drawBG  */
			  30.0,	/* fovy */
			  1.0,	/* fovymin */
			  90.0,	/* fovymax */
			  300.0,	/* distz */
			  0,		/* axis */
			  200.0,	/* near */
			  1000.0 * fovFactor,/* far */
			  500.0 * fovFactor,	/* fog */
			  1000.0 * fovFactor	/* fog */
			  );
    cam->add(&cams[c]);
    id++;

    /* cam F5 = car up 2*/
    cam = new cGrCarCamUp(myscreen,
			  id,
			  1,	/* drawCurr */
			  1,	/* drawBG  */
			  30.0,	/* fovy */
			  1.0,	/* fovymin */
			  90.0,	/* fovymax */
			  300.0,	/* distz */
			  1,		/* axis */
			  200.0,	/* near */
			  1000.0 * fovFactor,/* far */
			  500.0 * fovFactor,	/* fog */
			  1000.0 * fovFactor	/* fog */
			  );
    cam->add(&cams[c]);
    id++;

    /* cam F5 = car up 3*/
    cam = new cGrCarCamUp(myscreen,
			  id,
			  1,	/* drawCurr */
			  1,	/* drawBG  */
			  30.0,	/* fovy */
			  1.0,	/* fovymin */
			  90.0,	/* fovymax */
			  300.0,	/* distz */
			  2,		/* axis */
			  200.0,	/* near */
			  1000.0 * fovFactor,/* far */
			  500.0 * fovFactor,	/* fog */
			  1000.0 * fovFactor	/* fog */
			  );
    cam->add(&cams[c]);
    id++;

    /* cam F5 = car up 4*/
    cam = new cGrCarCamUp(myscreen,
			  id,
			  1,	/* drawCurr */
			  1,	/* drawBG  */
			  30.0,	/* fovy */
			  1.0,	/* fovymin */
			  90.0,	/* fovymax */
			  300.0,	/* distz */
			  3,		/* axis */
			  200.0,	/* near */
			  1000.0 * fovFactor,/* far */
			  500.0 * fovFactor,	/* fog */
			  1000.0 * fovFactor	/* fog */
			  );
    cam->add(&cams[c]);

    /* F6 */
    c++;
    GF_TAILQ_INIT(&cams[c]);
    id = 0;

    /* cam F6 = car from circuit centre */
    cam = new cGrCarCamCenter(myscreen,
			      id,
			      1,	/* drawCurr */
			      1,	/* drawBG  */
			      21.0,	/* fovy */
			      2.0,	/* fovymin */
			      60.0,	/* fovymax */
			      120.0,	/* distz */
			      100.0,	/* near */
			      1500.0,/* far */
			      1500.0,/* fog */
			      1500.0	/* fog */
			      );
    cam->add(&cams[c]);

    /* F7 */
    c++;
    GF_TAILQ_INIT(&cams[c]);
    id = 0;

    /* cam F7 = panoramic */
    cam = new cGrCarCamLookAt(myscreen,
			      id,
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
			      grWrldMaxSize,	/* far */
			      grWrldMaxSize,	/* fog */
			      grWrldMaxSize	/* fog */
			      );
    cam->add(&cams[c]);
    id++;

    /* cam F7 = panoramic */
    cam = new cGrCarCamLookAt(myscreen,
			      id,
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
			      2 * grWrldMaxSize,	/* far */
			      2 * grWrldMaxSize,	/* fog */
			      2 * grWrldMaxSize	/* fog */
			      );
    cam->add(&cams[c]);
    id++;

    /* cam F7 = panoramic */
    cam = new cGrCarCamLookAt(myscreen,
			      id,
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
			      2 * grWrldMaxSize,	/* far */
			      2 * grWrldMaxSize,	/* fog */
			      2 * grWrldMaxSize	/* fog */
			      );
    cam->add(&cams[c]);
    id++;

    /* cam F7 = panoramic */
    cam = new cGrCarCamLookAt(myscreen,
			      id,
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
			      2 * grWrldMaxSize,	/* far */
			      2 * grWrldMaxSize,	/* fog */
			      2 * grWrldMaxSize	/* fog */
			      );
    cam->add(&cams[c]);
    id++;

    /* cam F7 = panoramic */
    cam = new cGrCarCamLookAt(myscreen,
			      id,
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
			      2 * grWrldMaxSize,	/* far */
			      2 * grWrldMaxSize,	/* fog */
			      2 * grWrldMaxSize	/* fog */
			      );
    cam->add(&cams[c]);
    id++;

    /* F8 */
    c++;
    GF_TAILQ_INIT(&cams[c]);
    id = 0;

    /* cam F8 = road cam fixed fov */

    cam = new cGrCarCamRoadNoZoom(myscreen,
				  id,
				  1,		/* drawCurr */
				  1,		/* drawBG  */
				  30.0,	/* fovy */
				  5.0,	/* fovymin */
				  60.0,	/* fovymax */
				  1.0,	/* near */
				  1000.0 * fovFactor,/* far */
				  500.0 * fovFactor,	/* fog */
				  1000.0 * fovFactor	/* fog */
				  );
    cam->add(&cams[c]);

    /* F9 */
    c++;
    GF_TAILQ_INIT(&cams[c]);
    id = 0;

    /* cam F9 = road cam zoomed */
    cam = new cGrCarCamRoadZoom(myscreen,
				id,
				1,		/* drawCurr */
				1,		/* drawBG  */
				17.0,	/* fovy */
				1.0,		/* fovymin */
				90.0,	/* fovymax */
				1.0,		/* near */
				1000.0 * fovFactor,	/* far */
				500.0 * fovFactor,	/* fog */
				1000.0 * fovFactor	/* fog */
				);
    cam->add(&cams[c]);

    /* F10 */
    c++;
    GF_TAILQ_INIT(&cams[c]);
    id = 0;

    cam = new cGrCarCamRoadZoom(myscreen,
				id,
				1,		/* drawCurr */
				1,		/* drawBG  */
				17.0,	/* fovy */
				1.0,		/* fovymin */
				90.0,	/* fovymax */
				1.0,		/* near */
				1000.0 * fovFactor,	/* far */
				500.0 * fovFactor,	/* fog */
				1000.0 * fovFactor	/* fog */
				);
    cam->add(&cams[c]);

    /* F11 */
    c++;
    GF_TAILQ_INIT(&cams[c]);
    id = 0;
    cam = new cGrCarCamRoadZoomTVD(myscreen,
				   id,
				   1,	/* drawCurr */
				   1,	/* drawBG  */
				   17.0,	/* fovy */
				   1.0,	/* fovymin */
				   90.0,	/* fovymax */
				   1.0,	/* near */
				   1000.0 * fovFactor,	/* far */
				   500.0 * fovFactor,	/* fog */
				   1000.0 * fovFactor	/* fog */
				   );
    cam->add(&cams[c]);

}
