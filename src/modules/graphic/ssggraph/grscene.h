/***************************************************************************

    file                 : grscene.h
    created              : Mon Aug 21 20:09:40 CEST 2000
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


#ifndef _GRSCENE_H_
#define _GRSCENE_H_

#include <track.h>

extern int grWrldX;
extern int grWrldY;
extern int grWrldZ;
extern int grWrldMaxSize;
extern tTrack 	 *grTrack;

extern ssgRoot *TheScene;

extern int grInitScene(tTrack *track);
extern void grDrawScene(void);
extern void grShutdownScene(void);

struct Camera;
extern void grDrawBackground(cGrCamera *);

extern ssgStateSelector	*grEnvSelector;




#endif /* _GRSCENE_H_ */ 



