/***************************************************************************

    file                 : grcar.h
    created              : Mon Aug 21 18:21:15 CEST 2000
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

 
#ifndef _GRCAR_H_
#define _GRCAR_H_

typedef struct
{
    ssgSimpleState	*texture;
    GLuint		CounterList;
    GLuint		needleList;
    tdble		needleXCenter, needleYCenter;
    tdble		digitXCenter, digitYCenter;
    tdble		minValue, maxValue;
    tdble		minAngle, maxAngle;
    tdble		*monitored;
    tdble		prevVal;
} tgrCarInstrument;


typedef struct 
{
    float		iconColor[4];
    ssgTransform	*carTransform;
    ssgSelector		*LODSelector;
    int			LODSelectMask[32];
    float		LODThreshold[32];
    ssgStateSelector	*envSelector;
    ssgTransform	*wheelPos[4];
    ssgTransform	*wheelRot[4];
    ssgColourArray	*brkColor[4];
    ssgSelector		*wheelselector[4];
    ssgState		*wheelTexture;
    ssgVtxTable		*pit;
    ssgVtxTableShadow	*shadowBase;
    ssgVtxTableShadow	*shadowCurr;
    ssgBranch		*shadowAnchor;
    tgrSkidmarks         *skidmarks;
    sgMat4		carPos;
    tgrCarInstrument	instrument[2];
    tdble               distFromStart;
    tdble               envAngle;
} tgrCarInfo;

extern tgrCarInfo	*grCarInfo;

extern void grInitCar(tCarElt *car);
extern void grDrawCar(tCarElt*, tCarElt *, int);
extern void grDrawShadow(tCarElt *car);
extern void grInitShadow(tCarElt *car);
extern tdble grGetDistToStart(tCarElt *car);
#endif /* _GRCAR_H_ */ 



