/***************************************************************************

    file                 : elevation.cpp
    created              : Mon May 20 22:31:09 CEST 2002
    copyright            : (C) 2001 by Eric Espie
    email                : eric.espie@torcs.org
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

/** @file   
    		
    @author	<a href=mailto:eric.espie@torcs.org>Eric Espie</a>
    @version	$Id$
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <math.h>

#include <tgf.h>
#include <track.h>

#include "trackgen.h"
#include "elevation.h"

static unsigned char	*ElvImage;
static int	ElvOk = 0;
static tdble 	Margin;

static tdble	kX, kY, dX, dY;
static tdble	kZ, dZ;
static int	width, height;

#define MAX_CLR	255.0

void
LoadElevation(tTrack *track, void *TrackHandle, char *imgFile)
{
    tdble	zmin, zmax;
    tdble	xmin, xmax, ymin, ymax;

    ElvImage = GfImgReadPng(imgFile, &width, &height, 2.2);
    if (!ElvImage) {
	return;
    }

    Margin = GfParmGetNum(TrackHandle, TRK_SECT_TERRAIN, TRK_ATT_BMARGIN, NULL, Margin);
    
    xmin = track->min.x - Margin;
    xmax = track->max.x + Margin;
    ymin = track->min.y - Margin;
    ymax = track->max.y + Margin;
    
    kX = (tdble)(width - 1) / (xmax - xmin);
    dX = -xmin * kX;
    kY = (tdble)(height - 1) / (ymax - ymin);
    dY = -ymin * kY;
    ElvOk = 1;

    zmin = GfParmGetNum(TrackHandle, TRK_SECT_TERRAIN, TRK_ATT_ALT_MIN, NULL, track->min.z);
    zmax = GfParmGetNum(TrackHandle, TRK_SECT_TERRAIN, TRK_ATT_ALT_MAX, NULL, track->max.z);

    dZ = zmin;
    kZ = (zmax - dZ) / MAX_CLR;
}


tdble
GetElevation(tdble x, tdble y, tdble z)
{
    int iX, iY;
    int clr;
    
    if (ElvOk) {
	iX = (int)(x * kX + dX);
	iY = (int)(y * kY + dY);
	/* RGBA */
	clr = ElvImage[4 * (iY * width + iX)];
	return (tdble)clr * kZ + dZ;
    }
    
    return z;
}
