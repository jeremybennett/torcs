/***************************************************************************

    file                 : common.h
    created              : Sun Oct 24 14:19:43 CEST 1999
    copyright            : (C) 1999 by Eric Espie
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
 

#ifndef _COMMON_H_
#define _COMMON_H_

extern tdble Tright[10];
extern tdble MaxSpeed[10];
extern tdble hold[10];
extern tdble shiftThld[10][MAX_GEARS+1];
extern tTrack *DmTrack;


extern void InitGears(tCarElt* car, int idx);
extern void SpeedStrategy(tCarElt* car, int idx, tdble Vtarget, tSituation *s, tdble aspect);
extern tdble GetDistToStart(tCarElt *car);
extern void CollDet(tCarElt* car, int idx, tSituation *s, tdble Curtime, tdble dny);
extern tdble GetDistToStart2(tTrkLocPos *trkPos);


#endif /* _COMMON_H_ */ 



