/***************************************************************************

    file                 : simu.h
    created              : Sun Jan 30 12:02:05 CET 2000
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
 
 
#ifndef _SIMUV1_H_
#define _SIMUV1_H_

#include <ttypes.h>
#include <track.h>

#define SIM_IDENT	(CAR_IDENT|TRK_IDENT)

struct Situation;

typedef void (*tfSimInit)(int);
typedef void (*tfSimConfig)(tCarElt*);
typedef void (*tfSimReConfig)(tCarElt*);
typedef void (*tfSimUpdate)(struct Situation*, tdble, int);
typedef void (*tfSimShutdown)(void);

typedef struct
{
    tfSimInit	  init;
    tfSimConfig   config;
    tfSimReConfig reconfig;
    tfSimUpdate   update;
    tfSimShutdown shutdown;
} tSimItf;



#endif /* _SIMUV1_H_ */ 



