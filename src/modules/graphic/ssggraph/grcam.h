/***************************************************************************

    file                 : grcam.h
    created              : Mon Aug 21 20:55:02 CEST 2000
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

#ifndef _GRCAM_H_
#define _GRCAM_H_

#include <track.h>
#include <car.h>
#include <raceman.h>
#ifdef WIN32
#include <float.h>
#endif

extern float grviewRatio;
struct Camera;

typedef void (*tfcam)(struct Camera *, tCarElt *);
typedef void (*tfcams)(struct Camera *, tCarElt *, tSituation *);

typedef struct Camera
{
    /* ring list should be first */
    tRingList		l;
    
    int projtype;
#define CAM_NOTPRESENT	0
#define CAM_PERSPEC	2
#define CAM_ORTHO	3
#define CAM_FCTPERSPEC	4
    union 
    {
	struct
	{
	    float fovy;
	    float fnear;
	    float ffar;
	    float fovymin, fovymax, fovydflt;
	    tfcam fcam;
	    float cfovy;
	    float cnear;
	    float cfar;
	} fpersp;

	struct
	{
	    float fovy;
	    float fnear;
	    float ffar;
	    float fovymin, fovymax, fovydflt;
	} persp;
	
	struct
	{
	    tdble left, right, bottom, top;
	} ortho;
    } uproj;
    
    int   camtype;
#define CAM_INIT   0
#define CAM_LOOKAT 1
#define CAM_FCT    3
#define CAM_FCTS   2
    union 
    {
	struct 
	{
	    sgVec3 eye;
	    sgVec3 center;
	    sgVec3 up;
	} lookat;
	
	struct 
	{
	    sgVec3 eye;
	    sgVec3 center;
	    sgVec3 up;
	    tfcam  fcam;
	} fcam;
	
	struct 
	{
	    sgVec3 eye;
	    sgVec3 center;
	    sgVec3 up;
	    tfcams fcams;
	} fcams;
	
    } ucam;

    int id;		/* Camera Id */
    int drawCurrent;	/* flag to draw the current car */
    int drawBackground;	/* flag to draw the background */

} tCamera;

typedef struct CameraHead
{
    tRingListHead	cams;
} tCameraHead;



extern int grScissorflag;
extern tCameraHead grCams[];    /* from F1 to F12 */
extern tCamera *grCurCam;   /* the current camera */
extern int	grCurCamHead;
extern tCamera *grBoardCam; /* the board camera */
extern t3Dd	grCamPos;

extern int scrx, scry, scrw, scrh; /* screen size */


extern void grSetView(int x, int y, int w, int h);
extern void grUpdateCamera(tCamera *cam, tCarElt *car, tSituation *s);
extern void grSetCamera(tCamera *cam, tCarElt *car);
extern void grInitCams(void);
extern void grShutdownCams(void);
extern void grSelectCamera(void *vp);
extern void grSetZoom(void *vp);
extern void grInitTVDirectorView(tSituation *s);

#endif /* _GRCAM_H_ */ 



