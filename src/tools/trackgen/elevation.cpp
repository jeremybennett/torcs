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
#include "util.h"
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

    printf("Loading Elevation Map %s\n", imgFile);
    
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

void
SaveElevation(tTrack *track, void *TrackHandle, char *imgFile, char *meshFile)
{
    float	zmin, zmax;
    float	xmin, xmax, ymin, ymax;
    float	x, y, z;
    int		clr;
    int		i, j;
    ssgRoot	*root;

    
    Margin = GfParmGetNum(TrackHandle, TRK_SECT_TERRAIN, TRK_ATT_BMARGIN, NULL, Margin);
    
    xmin = track->min.x - Margin;
    xmax = track->max.x + Margin;
    ymin = track->min.y - Margin;
    ymax = track->max.y + Margin;
    
    width = 1024;
    height = (int)((ymax - ymin) * width / (xmax - xmin));

    printf("Generating Elevation Map %s (%d, %d)\n", imgFile, width, height);

    kX = (xmax - xmin) / width;
    dX = xmin;
    kY = (ymax - ymin) / height;
    dY = ymin;

    zmin = GfParmGetNum(TrackHandle, TRK_SECT_TERRAIN, TRK_ATT_ALT_MIN, NULL, track->min.z);
    zmax = GfParmGetNum(TrackHandle, TRK_SECT_TERRAIN, TRK_ATT_ALT_MAX, NULL, track->max.z);

    kZ = MAX_CLR / (zmax - dZ);
    dZ = - zmin * MAX_CLR / (zmax - dZ);

    ElvImage = (unsigned char*)calloc(width * height, 3);
    if (!ElvImage) {
	return;
    }

    root = (ssgRoot*)ssgLoadAC(meshFile);
    
    for (j = 0; j < height; j++) {
	printf("\rrow %d", j);
	fflush(stdout);
	for (i = 0; i < width; i++) {
	    x = i * kX + dX;
	    y = j * kY + dY;
	    z = getHOT(root, x, y);
	    if (z != -1000000.0f) {
		clr = (int)(z * kZ + dZ);
	    } else {
		clr = (int)MAX_CLR;
	    }

	    ElvImage[3 * (i + width * j)]     = (unsigned char)clr;
	    ElvImage[3 * (i + width * j) + 1] = (unsigned char)clr;
	    ElvImage[3 * (i + width * j) + 2] = (unsigned char)clr;
	}
    }

    printf("\n");
    GfImgWritePng(ElvImage, imgFile, width, height);
}
