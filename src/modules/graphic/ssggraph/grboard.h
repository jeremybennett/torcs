/***************************************************************************

    file                 : grboard.h
    created              : Thu Aug 17 23:55:47 CEST 2000
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

#ifndef _GRBOARD_H_
#define _GRBOARD_H_

#include <raceman.h>

extern void grDispDebug(float fps, tCarElt *car, tSituation *s);
extern void grDispCarBoard(tCarElt *car, tSituation *s);
extern void grDispLeaderBoard(tCarElt *car, tSituation *s);
extern void grDispCounterBoard(tCarElt *car);
extern void grDispCounterBoard2(tCarElt *car);
extern void grDispPause(void);
extern void grInitBoard(void);
extern void grShutdownBoard(void);
extern void grSelectBoard(void *vp);
extern void grDispGGraph(tCarElt *car);
extern void grInitBoardCar(tCarElt *car);

extern void grRefreshBoard(tSituation *s, float Fps, int forceArcade, int curr);
extern void grLoadBoardParams(void);

#endif /* _GRBOARD_H_ */ 



