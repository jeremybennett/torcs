/***************************************************************************

    file                 : graphic.h
    created              : Sun Jan 30 22:58:45 CET 2000
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
 
 
#ifndef _GRAPHV1_H_
#define _GRAPHV1_H_

#include <ttypes.h>
#include <track.h>
#include <car.h>
#include <raceman.h>

#define GRX_IDENT	(TRK_IDENT|RCM_IDENT|CAR_IDENT)


/* graphic functions prototypes */

typedef int (*tfGraphicInitTrack)(tTrack *);
typedef int (*tfGraphicInitCars)(tSituation *); 
typedef int (*tfGraphicInitView)(int /*x*/, int /*y*/, int /*width*/, int /*height*/, int /*flag*/, void * /*screen*/);
#define GR_VIEW_STD  0 /* full screen view */
#define GR_VIEW_PART 1 /* partial screen view (scissor test) */

typedef int (*tfGraphicRefresh)(tSituation *);
typedef void (*tfGraphicShutdwnCars)(void);
typedef void (*tfGraphicShutdwnTrack)(void);


/* Interface with the graphic lib */
typedef struct {
    tfGraphicInitTrack	    inittrack;	    /* Graphic init function */
    tfGraphicInitView       initview;       /* Graphic init function */
    tfGraphicInitCars	    initcars;	    /* Graphic init function */
    tfGraphicRefresh	    refresh;	    /* Graphic refresh function */
    tfGraphicShutdwnCars    shutdowncars;   /* Graphic shutdown function */
    tfGraphicShutdwnTrack   shutdowntrack;  /* Graphic shutdown function */
} tGraphicItf;


    

#endif /* _GRAPHV1_H_ */ 



