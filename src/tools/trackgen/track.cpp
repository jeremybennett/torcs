/***************************************************************************

    file                 : track.cpp
    created              : Sun Dec 24 12:14:18 CET 2000
    copyright            : (C) 2000 by Eric Espie
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
#include <robottools.h>

#include "ac3d.h"
#include "util.h"

#include "trackgen.h"

typedef struct texElt
{
    char		*name;
    unsigned int	texid;
    struct texElt	*next;
} tTexElt;

typedef struct dispElt 
{
    int			start;
    int			nb;
    int			surfType;
    char		*name;
    int			id;
    tTexElt		*texture;
    struct dispElt	*next;
} tDispElt;
 
static tDispElt		*DispList = (tDispElt*)NULL;

#define LMAX TrackStep

static float		*trackvertices;
static float		*tracktexcoord;
static unsigned int	*trackindices;

static tdble		TrackStep;

static void
initPits(tTrackPitInfo *pits)
{
    tTrackSeg	*curMainSeg;
    tTrackSeg	*curPitSeg = NULL;
    tdble	toStart = 0;
    tdble	offset = 0;
    tTrkLocPos	curPos;
    int		changeSeg;
    int		i;

    switch (pits->type) {
    case TR_PIT_ON_TRACK_SIDE:
	pits->driversPits = (tTrackOwnPit*)calloc(pits->nMaxPits, sizeof(tTrackOwnPit));
	pits->driversPitsNb = pits->nMaxPits;
	curPos.type = TR_LPOS_MAIN;
	curMainSeg = pits->pitStart->prev;
	changeSeg = 1;
	toStart = 0;
	i = 0;
	while (i < pits->nMaxPits) {
	    if (changeSeg) {
		changeSeg = 0;
		offset = 0;
		curMainSeg = curMainSeg->next;
		switch (pits->side) {
		case TR_RGT:
		    curPitSeg = curMainSeg->rside;
		    if (curPitSeg->rside) {
			offset = curPitSeg->width;
			curPitSeg = curPitSeg->rside;
		    }
		    break;
		case TR_LFT:
		    curPitSeg = curMainSeg->lside;
		    if (curPitSeg->lside) {
			offset = curPitSeg->width;
			curPitSeg = curPitSeg->lside;
		    }
		    break;
		}
		curPos.seg = curMainSeg;
		if (toStart >= curMainSeg->length) {
		    toStart -= curMainSeg->length;
		    changeSeg = 1;
		    continue;
		}
	    }
	    /* Not the real position but the start and border one instead of center */
	    curPos.toStart = toStart;
	    switch (pits->side) {
	    case TR_RGT:
		curPos.toRight  = -offset - RtTrackGetWidth(curPitSeg, toStart);
		curPos.toLeft   = curMainSeg->width - curPos.toRight;
		curPos.toMiddle = curMainSeg->width / 2.0 - curPos.toRight;
		break;
	    case TR_LFT:
		curPos.toLeft   = -offset - RtTrackGetWidth(curPitSeg, toStart);
		curPos.toRight  = curMainSeg->width - curPos.toLeft;
		curPos.toMiddle = curMainSeg->width / 2.0 - curPos.toLeft;
		break;
	    }
	    memcpy(&(pits->driversPits[i].pos), &curPos, sizeof(curPos));
	    toStart += pits->len;
	    if (toStart >= curMainSeg->length) {
		toStart -= curMainSeg->length;
		changeSeg = 1;
	    }
	    i++;
	}
	break;
    case TR_PIT_ON_SEPARATE_PATH:
	break;
    case TR_PIT_NONE:
	break;	
    }
}

int
InitScene(tTrack *Track, void *TrackHandle)
{

    int 		i, j;
    tTrackSeg 		*seg;
    tTrackSeg 		*mseg;
    int 		nbvert;
    tdble 		width, wi2;
    tdble 		anz, ts = 0;
    tdble               radiusr, radiusl;
    tdble 		step;
    tTrkLocPos 		trkpos;
    tdble		x, y, z;
    tdble		x2, y2, z2;
    tdble		x3, y3, z3;
    int			startNeeded;

    tDispElt		*aDispElt = NULL;
    unsigned int	prevTexId;
    unsigned int	curTexId = 0;
    int			curTexType = 0;
    int			curTexLink = 0;
    tdble		curTexOffset = 0;
    tdble		curTexSeg;
    tdble		curTexSize = 0;
    tdble		curHeight;
    tTexElt		*texList = (tTexElt*)NULL;
    tTexElt		*curTexElt = NULL;
    tTrackBarrier	*curBarrier;
    tdble		texLen;
    tdble		texStep;
    tdble		texMaxT = 0;
    tTrackPitInfo	*pits;
    static int		GenTexId = 1;
    tdble		runninglentgh;

    tdble		tmWidth  = Track->graphic.turnMarksInfo.width;
    tdble		tmHeight = Track->graphic.turnMarksInfo.height;
    tdble		tmVSpace = Track->graphic.turnMarksInfo.vSpace;
    tdble		tmHSpace = Track->graphic.turnMarksInfo.hSpace;
    char		buf[256];
    int			uniqueId = 0;
    int			hasBorder;

#define	LG_STEP_MAX	50.0

    printf("++++++++++++ Track ++++++++++++\n");
    printf("name      = %s\n", Track->name);
    printf("author    = %s\n", Track->author);
    printf("filename  = %s\n", Track->filename);
    printf("nseg      = %d\n", Track->nseg);
    printf("version   = %d\n", Track->version);
    printf("length    = %f\n", Track->length);
    printf("width     = %f\n", Track->width);
    printf("XSize     = %f\n", Track->max.x);
    printf("YSize     = %f\n", Track->max.y);
    printf("ZSize     = %f\n", Track->max.z);

    tdble delatx = Track->seg->next->vertex[TR_SL].x - Track->seg->vertex[TR_EL].x;
    tdble delaty = Track->seg->next->vertex[TR_SL].y - Track->seg->vertex[TR_EL].y;
    tdble delatz = Track->seg->next->vertex[TR_SL].z - Track->seg->vertex[TR_EL].z;
    tdble delata = Track->seg->next->angle[TR_ZE] - Track->seg->angle[TR_ZS];
    
    printf("Delta X   = %f\n", delatx);
    printf("Delta Y   = %f\n", delaty);
    printf("Delta Z   = %f\n", delatz);
    printf("Delta Ang = %f (%f)\n", delata, RAD2DEG(delata));

    if ((fabs(delatx) > 1.0) || (fabs(delaty) > 1.0) || (fabs(delatz) > 1.0)) {
/* 	exit(0); */
    }

    width = Track->width;
    wi2 = width / 2.0;

    trkpos.type = TR_LPOS_MAIN;

#define SETTEXTURE(texname, mipmap) { 											\
	int found = 0;													\
	curTexElt = texList;												\
	if (curTexElt == NULL) {											\
	    curTexElt = (tTexElt*)calloc(1, sizeof(tTexElt));								\
	    curTexElt->next = curTexElt;										\
	    texList = curTexElt;											\
	    curTexElt->name = strdup(texname);										\
	    curTexElt->texid = GenTexId++;										\
	} else {													\
	    do {													\
		curTexElt = curTexElt->next;										\
		if (strcmp(texname, curTexElt->name) == 0) {								\
		    found = 1;												\
		    break;												\
		}													\
	    } while (curTexElt != texList);										\
	    if (!found) {												\
		curTexElt = (tTexElt*)calloc(1, sizeof(tTexElt));							\
		curTexElt->next = texList->next;									\
		texList->next = curTexElt;										\
		texList = curTexElt;											\
		curTexElt->name = strdup(texname);									\
	        curTexElt->texid = GenTexId++;										\
	    }														\
	}														\
	curTexId = curTexElt->texid;											\
    }

#define NBELTLIST 1

#define NEWDISPLIST(texchange, _name, _id) {			\
    if (DispList == NULL) {					\
	aDispElt = (tDispElt*)malloc(sizeof(tDispElt));		\
	aDispElt->start = nbvert;				\
	aDispElt->nb = 0;					\
	aDispElt->name = _name;					\
	aDispElt->id = _id;					\
	aDispElt->texture = curTexElt;				\
	aDispElt->next = aDispElt;				\
	aDispElt->surfType = 0;					\
	DispList = aDispElt;					\
    } else {							\
	startNeeded = texchange;				\
	if (DispList->start != nbvert) {			\
	    DispList->nb = nbvert - DispList->start;		\
	    aDispElt = (tDispElt*)malloc(sizeof(tDispElt));	\
	    aDispElt->start = nbvert;				\
	    aDispElt->nb = 0;					\
	    aDispElt->name = _name;				\
	    aDispElt->id = _id;					\
	    aDispElt->texture = curTexElt;			\
	    aDispElt->next = DispList->next;			\
	    aDispElt->surfType = 0;				\
	    DispList->next = aDispElt;				\
	    DispList = aDispElt;				\
	} else {						\
	    aDispElt->texture = curTexElt;			\
	    aDispElt->surfType = 0;				\
	}							\
    }								\
}

#define CHECKDISPLIST(mat, name, id, off) do {						\
	char *texname;									\
	int  mipmap;									\
	static char path_[256];								\
	if (Track->version < 4) {							\
	    sprintf(path_, "%s/%s/%s", TRK_SECT_SURFACES, TRK_LST_SURF, mat);		\
        } else {									\
	    sprintf(path_, "%s/%s", TRK_SECT_SURFACES, mat);				\
        }										\
	texname = GfParmGetStr(TrackHandle, path_, TRK_ATT_TEXTURE, "tr-asphalt.rgb");		\
	mipmap = (int)GfParmGetNum(TrackHandle, path_, TRK_ATT_TEXMIPMAP, (char*)NULL, 0);	\
	SETTEXTURE(texname, mipmap);							\
	if ((curTexId != prevTexId) || (startNeeded)) {					\
	    char *textype;								\
	    textype = GfParmGetStr(TrackHandle, path_, TRK_ATT_TEXTYPE, "continuous");		\
	    if (strcmp(textype, "continuous") == 0)					\
		curTexType = 1;								\
	    else									\
		curTexType = 0;								\
	    textype = GfParmGetStr(TrackHandle, path_, TRK_ATT_TEXLINK, TRK_VAL_YES);		\
	    if (strcmp(textype, TRK_VAL_YES) == 0)					\
		curTexLink = 1;								\
	    else									\
		curTexLink = 0;								\
	    textype = GfParmGetStr(TrackHandle, path_, TRK_ATT_TEXSTARTBOUNDARY, TRK_VAL_NO);	\
	    if (strcmp(textype, TRK_VAL_YES) == 0)					\
		curTexOffset = -off;							\
	    else									\
		curTexOffset = 0;							\
	    curTexSize = GfParmGetNum(TrackHandle, path_, TRK_ATT_TEXSIZE, (char*)NULL, 20.0);	\
	    prevTexId = curTexId;							\
	    NEWDISPLIST(1, name, id);							\
	}										\
    } while (0)

#define CHECKDISPLIST2(texture, mipmap, name, id) {		\
	static char texname[256];				\
	sprintf(texname, "%s.rgb", texture);			\
	SETTEXTURE(texname, mipmap);				\
	if (curTexId != prevTexId) {				\
	    prevTexId = curTexId;				\
	    NEWDISPLIST(1, name, id);				\
	}							\
    }

#define CHECKDISPLIST3(texture, mipmap, name, id) {		\
	SETTEXTURE(texture, mipmap);				\
	if (curTexId != prevTexId) {				\
	    prevTexId = curTexId;				\
	    NEWDISPLIST(1, name, id);				\
	}							\
    }

#define CLOSEDISPLIST() {				\
	DispList->nb = nbvert - DispList->start;	\
}


#define SETPOINT(t1, t2, x, y, z) do {			\
	    tracktexcoord[2*nbvert]   = t1;		\
	    tracktexcoord[2*nbvert+1] = t2;		\
	    trackvertices[3*nbvert]   = x;		\
	    trackvertices[3*nbvert+1] = y;		\
	    trackvertices[3*nbvert+2] = z;		\
	    trackindices[nbvert]      = nbvert++;	\
    } while (0)

#define SETPOINT2(t1, t2, x, y, z) do {											\
	    tracktexcoord[2*nbvert]   = t1;										\
	    tracktexcoord[2*nbvert+1] = t2;										\
	    trackvertices[3*nbvert]   = x;										\
	    trackvertices[3*nbvert+1] = y;										\
	    trackvertices[3*nbvert+2] = z;										\
	    trackindices[nbvert]      = nbvert++;									\
	    printf("x=%f y=%f z=%f  u=%f v=%f\n", (tdble)(x), (tdble)(y), (tdble)(z), (tdble)(t1), (tdble)(t2));	\
    } while (0)


    /* Count the number of vertice to allocate */
    nbvert = 0;
    for (i = 0, seg = Track->seg->next; i < Track->nseg; i++, seg = seg->next) {
	    nbvert++;
	switch (seg->type) {
	case TR_STR:
	    nbvert += (int)(seg->length /  LMAX);
	    break;
	case TR_LFT:
	    nbvert += (int)(seg->arc * (seg->radiusr) / LMAX);
	    break;
	case TR_RGT:
	    nbvert += (int)(seg->arc * (seg->radiusl) / LMAX);
	    break;
	}
    }

    nbvert++;
    nbvert *= 30;
    nbvert+=58; /* start bridge */
    nbvert+=12 + 10 * Track->pits.driversPitsNb;
    nbvert+=1000; /* safety margin */
    printf("=== Indices Array Size   = %d\n", nbvert);
    printf("=== Vertex Array Size    = %d\n", nbvert * 3);
    printf("=== Tex Coord Array Size = %d\n", nbvert * 2);
    trackindices  = (unsigned int*)malloc(sizeof(unsigned int) * nbvert);
    trackvertices = (float*)malloc(sizeof(GLfloat)*(nbvert * 3));
    tracktexcoord = (float*)malloc(sizeof(GLfloat)*(nbvert * 2));

    nbvert = 0;

    /* Main track */
    prevTexId = 0;
    texLen = 0;
    startNeeded = 1;
    runninglentgh = 0;
    for (i = 0, seg = Track->seg->next; i < Track->nseg; i++, seg = seg->next) {
	uniqueId++;
	CHECKDISPLIST(seg->surface->material, "tkMn", uniqueId, seg->lgfromstart);
	if (!curTexLink) {
	    curTexSeg = 0;
	} else {
	    curTexSeg = seg->lgfromstart;
	}
	curTexSeg += curTexOffset;
	texLen = curTexSeg / curTexSize;
	if (startNeeded || (runninglentgh > LG_STEP_MAX)) {
	    uniqueId++;
	    NEWDISPLIST(0, "tkMn", uniqueId);
	    runninglentgh = 0;
	    ts = 0;
	    texMaxT = (curTexType == 1 ? width / curTexSize : 1.0 + floor(width / curTexSize));

	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = texMaxT;
	    trackvertices[3*nbvert]   = seg->vertex[TR_SL].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_SL].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_SL].z;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = 0.0;
	    trackvertices[3*nbvert]   = seg->vertex[TR_SR].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_SR].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_SR].z;
	    trackindices[nbvert]      = nbvert++;
	}
	    
	switch (seg->type) {
	case TR_STR:
	    ts = LMAX;
	    texStep = LMAX / curTexSize;
	    trkpos.seg = seg;
	    while (ts < seg->length) {
		texLen += texStep;
		trkpos.toStart = ts;

		trkpos.toRight = width;
		RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);

		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = texMaxT;
		trackvertices[3*nbvert]   = x;
		trackvertices[3*nbvert+1] = y;
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		trackindices[nbvert]      = nbvert++;

		trkpos.toRight = 0;
		RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);

		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0.0;
		trackvertices[3*nbvert]   = x;
		trackvertices[3*nbvert+1] = y;
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		trackindices[nbvert]      = nbvert++;

		ts += LMAX;
	    }
	    ts = seg->length;
	    break;
	case TR_LFT:
	    step = LMAX / (seg->radiusr);
	    texStep = step * seg->radius / curTexSize;
	    anz = seg->angle[TR_ZS] + step;
	    ts = step;
	    radiusr = seg->radiusr;
	    radiusl = seg->radiusl;
	    trkpos.seg = seg;
	    while (anz < seg->angle[TR_ZE]) {
		texLen += texStep;
		trkpos.toStart = ts;

		/* left */
		trkpos.toRight = width;
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = texMaxT;
		trackvertices[3*nbvert]   = seg->center.x + radiusl * sin(anz);
		trackvertices[3*nbvert+1] = seg->center.y - radiusl * cos(anz);
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		trackindices[nbvert]      = nbvert++;

		/* right */
		trkpos.toRight = 0;
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0.0;
		trackvertices[3*nbvert]   = seg->center.x + radiusr * sin(anz);
		trackvertices[3*nbvert+1] = seg->center.y - radiusr * cos(anz);
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		trackindices[nbvert]      = nbvert++;

		ts += step;
		anz += step;
	    }
	    ts = seg->arc;
	    break;
	case TR_RGT:
	    step = LMAX / (seg->radiusl);
	    texStep = step * seg->radius / curTexSize;
	    anz = seg->angle[TR_ZS] - step;
	    ts = step;
	    radiusr = seg->radiusr;
	    radiusl = seg->radiusl;
	    trkpos.seg = seg;
	    while (anz > seg->angle[TR_ZE]) {
		texLen += texStep;
		trkpos.toStart = ts;

		/* left */
		trkpos.toRight = width;
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = texMaxT;
		trackvertices[3*nbvert]   = seg->center.x - radiusl * sin(anz);
		trackvertices[3*nbvert+1] = seg->center.y + radiusl * cos(anz);
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		trackindices[nbvert]      = nbvert++;

		/* right */
		trkpos.toRight = 0;
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0;
		trackvertices[3*nbvert]   = seg->center.x - radiusr * sin(anz);
		trackvertices[3*nbvert+1] = seg->center.y + radiusr * cos(anz);
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		trackindices[nbvert]      = nbvert++;

		ts += step;
		anz -= step;
	    }
	    ts = seg->arc;
	    break;
	}
	texLen = (curTexSeg + seg->length) / curTexSize;

	tracktexcoord[2*nbvert]   = texLen;
	tracktexcoord[2*nbvert+1] = texMaxT;
	trackvertices[3*nbvert]   = seg->vertex[TR_EL].x;
	trackvertices[3*nbvert+1] = seg->vertex[TR_EL].y;
	trackvertices[3*nbvert+2] = seg->vertex[TR_EL].z;
	trackindices[nbvert]      = nbvert++;

	tracktexcoord[2*nbvert]   = texLen;
	tracktexcoord[2*nbvert+1] = 0;
	trackvertices[3*nbvert]   = seg->vertex[TR_ER].x;
	trackvertices[3*nbvert+1] = seg->vertex[TR_ER].y;
	trackvertices[3*nbvert+2] = seg->vertex[TR_ER].z;
	trackindices[nbvert]      = nbvert++;

	startNeeded = 0;
	runninglentgh += seg->length;
    }


    /* Right Border */
    for (j = 0; j < 3; j++) {
	prevTexId = 0;
	texLen = 0;
	startNeeded = 1;
	runninglentgh = 0;
	uniqueId++;
	NEWDISPLIST(0, "tkRtBr", uniqueId);
	for (i = 0, mseg = Track->seg->next; i < Track->nseg; i++, mseg = mseg->next) {
	    if ((mseg->rside != NULL) && (mseg->rside->type2 == TR_RBORDER)) {
		seg = mseg->rside;
		uniqueId++;
		CHECKDISPLIST(seg->surface->material, "tkRtBr", uniqueId, mseg->lgfromstart);
		if (!curTexLink) {
		    curTexSeg = 0;
		} else {
		    curTexSeg = mseg->lgfromstart;
		}
		curTexSeg += curTexOffset;
		texLen = curTexSeg / curTexSize;
		if (startNeeded || (runninglentgh > LG_STEP_MAX)) {
		    uniqueId++;
		    NEWDISPLIST(0, "tkRtBr", uniqueId);
		    runninglentgh = 0;
		    ts = 0;

		    width = RtTrackGetWidth(seg, ts);
		    texMaxT = (curTexType == 1 ? width / curTexSize : 1.0 + floor(width / curTexSize));

		    switch (seg->style) {
		    case TR_PLAN:
			if (j == 0) {
			    SETPOINT(texLen, 0,       seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z);
			    SETPOINT(texLen, texMaxT, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z);
			}
			break;
		    case TR_CURB:
			if (j == 0) {
			    if (!mseg->prev->rside || (mseg->prev->rside->type2 != TR_RBORDER) || (mseg->prev->rside->style != TR_CURB)) {
/* 				SETPOINT(texLen, 0,       seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z); */
				SETPOINT(texLen, texMaxT, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z);
			    }
			    SETPOINT(texLen, 0,       seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z);
			    SETPOINT(texLen, texMaxT, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z + seg->height);
			} else if (j == 1) {
			    SETPOINT(texLen, texMaxT, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z + seg->height);
			    SETPOINT(texLen, texMaxT, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z);
			}
			break;
		    case TR_WALL:
			switch (j) {
			case 0:
			    SETPOINT(texLen, 0,   seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z);
			    SETPOINT(texLen, .33, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z + seg->height);
			    break;
			case 1:
			    SETPOINT(texLen, 0.33, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z + seg->height);
			    SETPOINT(texLen, 0.66, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z + seg->height);
			    break;
			case 2:
			    if (!mseg->prev->rside || (mseg->prev->rside->type2 != TR_RBORDER) || (mseg->prev->rside->style != TR_WALL)) {
				SETPOINT(texLen - seg->width/curTexSize, 0.66, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z + seg->height);
				SETPOINT(texLen - seg->width/curTexSize, 1.00, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z);
			    }
			    SETPOINT(texLen, 0.66, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z + seg->height);
			    SETPOINT(texLen, 1.0,  seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z);
			    break;
			}
			break;
		    }
		    
		}
	    
		switch (seg->type) {
		case TR_STR:
		    ts = LMAX;
		    texStep = LMAX / curTexSize;
		    texLen += texStep;
		    trkpos.seg = seg;
		    while (ts < seg->length) {
			trkpos.toStart = ts;
			width = RtTrackGetWidth(seg, ts);
			texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

			switch (seg->style) {
			case TR_PLAN:
			    if (j == 0) {
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
				trkpos.toRight = 0 ;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_CURB:
			    if (j == 0) {
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
				trkpos.toRight = 0 ;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
			    } else if (j == 1) {
				trkpos.toRight = 0 ;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_WALL:
			    switch (j) {
			    case 0:
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0,    x, y, RtTrackHeightL(&trkpos));
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 1:
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				trkpos.toRight = 0 ;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 2:
				trkpos.toRight = 0 ;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				SETPOINT(texLen, 1.0,  x, y, RtTrackHeightL(&trkpos));
				break;
			    }
			    break;
			}

			ts += LMAX;
			texLen += texStep;
		    }
		    ts = seg->length;
		    break;
		case TR_LFT:
		    step = LMAX / (mseg->radiusr);
		    texStep = step * mseg->radius / curTexSize;
		    anz = seg->angle[TR_ZS] + step;
		    ts = step;
		    texLen += texStep;
		    radiusr = seg->radiusr;
		    radiusl = seg->radiusl;
		    trkpos.seg = seg;
		    while (anz < seg->angle[TR_ZE]) {
			trkpos.toStart = ts;
			width = RtTrackGetWidth(seg, ts);
			texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

			switch (seg->style) {
			case TR_PLAN:
			    if (j == 0) {
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_CURB:
			    if (j == 0) {
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
			    } else if (j == 1) {
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_WALL:
			    switch (j) {
			    case 0:
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0,    x, y, RtTrackHeightL(&trkpos));
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 1:
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 2:
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				SETPOINT(texLen, 1.0,  x, y, RtTrackHeightL(&trkpos));
				break;
			    }
			    break;
			}

			ts += step;
			texLen += texStep;
			anz += step;
		    }
		    ts = seg->arc;
		    break;
		case TR_RGT:
		    step = LMAX / (mseg->radiusl);
		    texStep = step * mseg->radius / curTexSize;
		    anz = seg->angle[TR_ZS] - step;
		    ts = step;
		    texLen += texStep;
		    radiusr = seg->radiusr;
		    radiusl = seg->radiusl;
		    trkpos.seg = seg;
		    while (anz > seg->angle[TR_ZE]) {
			trkpos.toStart = ts;
			width = RtTrackGetWidth(seg, ts);
			texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

			switch (seg->style) {
			case TR_PLAN:
			    if (j == 0) {
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_CURB:
			    if (j == 0) {
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
			    } else if (j == 1) {
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_WALL:
			    switch (j) {
			    case 0:
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0,    x, y, RtTrackHeightL(&trkpos));
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 1:
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 2:
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				SETPOINT(texLen, 1.0, x, y, RtTrackHeightL(&trkpos));
				break;
			    }
			    break;
			}

			ts += step;
			texLen += texStep;
			anz -= step;
		    }
		    ts = seg->arc;
		    break;
		}
		texLen = (curTexSeg + mseg->length) / curTexSize;

		switch (seg->style) {
		case TR_PLAN:
		    if (j == 0) {
			width = RtTrackGetWidth(seg, ts);
			texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));
			SETPOINT(texLen, 0,       seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z);
			SETPOINT(texLen, texMaxT, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z);
		    }
		    break;
		case TR_CURB:
		    if (j == 0) {
			width = RtTrackGetWidth(seg, ts);
			texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));
			SETPOINT(texLen, 0,       seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z);
			SETPOINT(texLen, texMaxT, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z + seg->height);
			if (mseg->next->rside && ((mseg->next->rside->type2 != TR_RBORDER) || (mseg->next->rside->style != TR_CURB))) {
/* 			    SETPOINT(texLen, 0,       seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z); */
			    SETPOINT(texLen, texMaxT, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z);
			}
		    } else if (j == 1) {
			width = RtTrackGetWidth(seg, ts);
			texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));
			SETPOINT(texLen, texMaxT, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z + seg->height);
			SETPOINT(texLen, texMaxT, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z);
		    }
		    break;
		case TR_WALL:
		    switch (j) {
		    case 0:
			SETPOINT(texLen, 0,    seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z);
			SETPOINT(texLen, 0.33, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z + seg->height);
			break;
		    case 1:
			SETPOINT(texLen, 0.33, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z + seg->height);
			SETPOINT(texLen, 0.66, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z + seg->height);
			break;
		    case 2:
			SETPOINT(texLen, 0.66, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z + seg->height);
			SETPOINT(texLen, 1.0,  seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z);
			if (mseg->next->rside && ((mseg->next->rside->type2 != TR_RBORDER) || (mseg->next->rside->style != TR_WALL))) {
			    SETPOINT(texLen + seg->width/curTexSize, 0.66, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z + seg->height);
			    SETPOINT(texLen + seg->width/curTexSize, 1.00, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z);
			}
			break;
		    }
		    break;
		}

		startNeeded = 0;
		runninglentgh += seg->length;
	    } else {
		uniqueId++;
		NEWDISPLIST(0, "tkRtBr", uniqueId);
		startNeeded = 1;
	    }
	}
    }
    

    /* Right Side */
    prevTexId = 0;
    texLen = 0;
    startNeeded = 1;
    runninglentgh = 0;
    hasBorder = 0;
    uniqueId++;
    NEWDISPLIST(0, "tkRtSd", uniqueId);
    for (i = 0, mseg = Track->seg->next; i < Track->nseg; i++, mseg = mseg->next) {
	if ((mseg->rside != NULL) &&
	    ((mseg->rside->type2 == TR_RSIDE) || (mseg->rside->rside != NULL))) {
	    seg = mseg->rside;
	    if (seg->rside != NULL) {
		seg = seg->rside;
		if (hasBorder == 0) {
		    startNeeded = 1;
		    hasBorder = 1;
		}
	    } else {
		if (hasBorder) {
		    startNeeded = 1;
		    hasBorder = 0;
		}
	    }
	    uniqueId++;
	    CHECKDISPLIST(seg->surface->material, "tkRtSd", uniqueId, mseg->lgfromstart);
	    if (!curTexLink) {
		curTexSeg = 0;
	    } else {
		curTexSeg = mseg->lgfromstart;
	    }
	    curTexSeg += curTexOffset;
	    texLen = curTexSeg / curTexSize;
	    if (startNeeded || (runninglentgh > LG_STEP_MAX)) {
		uniqueId++;
		NEWDISPLIST(0, "tkRtSd", uniqueId);
		runninglentgh = 0;
		ts = 0;

		width = RtTrackGetWidth(seg, ts);
		texMaxT = (curTexType == 1 ? width / curTexSize : 1.0 + floor(width / curTexSize));

		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0;
		trackvertices[3*nbvert]   = seg->vertex[TR_SL].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SL].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SL].z;
		trackindices[nbvert]      = nbvert++;

		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = texMaxT;
		trackvertices[3*nbvert]   = seg->vertex[TR_SR].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SR].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SR].z;
		trackindices[nbvert]      = nbvert++;
	    }
	    
	    switch (seg->type) {
	    case TR_STR:
		ts = LMAX;
		texStep = LMAX / curTexSize;
		texLen += texStep;
		trkpos.seg = seg;
		while (ts < seg->length) {
		    trkpos.toStart = ts;

		    width = RtTrackGetWidth(seg, ts);
		    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

		    trkpos.toRight = width;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    trkpos.toRight = 0 ;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = texMaxT;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    ts += LMAX;
		    texLen += texStep;
		}
		ts = seg->length;
		break;
	    case TR_LFT:
		step = LMAX / (mseg->radiusr);
		texStep = step * mseg->radius / curTexSize;
		anz = seg->angle[TR_ZS] + step;
		ts = step;
		texLen += texStep;
		radiusr = seg->radiusr;
		radiusl = seg->radiusl;
		trkpos.seg = seg;
		while (anz < seg->angle[TR_ZE]) {
		    trkpos.toStart = ts;
		    width = RtTrackGetWidth(seg, ts);
		    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

		    /* left */
		    trkpos.toRight = width;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    /* right */
		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = texMaxT;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    ts += step;
		    texLen += texStep;
		    anz += step;
		}
		ts = seg->arc;
		break;
	    case TR_RGT:
		step = LMAX / (mseg->radiusl);
		texStep = step * mseg->radius / curTexSize;
		anz = seg->angle[TR_ZS] - step;
		ts = step;
		texLen += texStep;
		radiusr = seg->radiusr;
		radiusl = seg->radiusl;
		trkpos.seg = seg;
		while (anz > seg->angle[TR_ZE]) {
		    trkpos.toStart = ts;
		    width = RtTrackGetWidth(seg, ts);
		    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

		    /* left */
		    trkpos.toRight = width;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    /* right */
		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = texMaxT;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    ts += step;
		    texLen += texStep;
		    anz -= step;
		}
		ts = seg->arc;
		break;
	    }
	    texLen = (curTexSeg + mseg->length) / curTexSize;

	    width = RtTrackGetWidth(seg, ts);
	    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = 0;
	    trackvertices[3*nbvert]   = seg->vertex[TR_EL].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_EL].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_EL].z;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = texMaxT;
	    trackvertices[3*nbvert]   = seg->vertex[TR_ER].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_ER].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_ER].z;
	    trackindices[nbvert]      = nbvert++;

	    startNeeded = 0;
	    runninglentgh += seg->length;
	} else {
	    uniqueId++;
	    NEWDISPLIST(0, "tkRtSd", uniqueId);
	    startNeeded = 1;
	}
    }


    /* Left Border */
    for (j = 0; j < 3; j++) {
	prevTexId = 0;
	texLen = 0;
	startNeeded = 1;
	runninglentgh = 0;
	uniqueId++;
	NEWDISPLIST(0, "tkLtBr", uniqueId);
	for (i = 0, mseg = Track->seg->next; i < Track->nseg; i++, mseg = mseg->next) {
	    if ((mseg->lside != NULL) && (mseg->lside->type2 == TR_LBORDER)) {
		seg = mseg->lside;
		uniqueId++;
		CHECKDISPLIST(seg->surface->material, "tkLtBr", uniqueId, mseg->lgfromstart);
		if (!curTexLink) {
		    curTexSeg = 0;
		} else {
		    curTexSeg = mseg->lgfromstart;
		}
		curTexSeg += curTexOffset;
		texLen = curTexSeg / curTexSize;
		if (startNeeded || (runninglentgh > LG_STEP_MAX)) {
		    uniqueId++;
		    NEWDISPLIST(0, "tkLtBr", uniqueId);
		    runninglentgh = 0;
		    ts = 0;
		    width = RtTrackGetWidth(seg, ts);
		    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));
		    switch (seg->style) {
		    case TR_PLAN:
			if (j == 0) {
			    SETPOINT(texLen, texMaxT, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z);
			    SETPOINT(texLen, 0, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z);
			}
			break;
		    case TR_CURB:
			if (j == 0) {
			    SETPOINT(texLen, texMaxT, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z);
			    SETPOINT(texLen, texMaxT, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z + seg->height);
			} else if (j == 1) {
			    if (!mseg->prev->rside || (mseg->prev->rside->type2 != TR_RBORDER) || (mseg->prev->rside->style != TR_CURB)) {
				SETPOINT(texLen, texMaxT, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z);
/* 				SETPOINT(texLen, 0, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z); */
			    }
			    SETPOINT(texLen, texMaxT, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z + seg->height);
			    SETPOINT(texLen, 0, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z);
			}
			break;
		    case TR_WALL:
			switch (j) {
			case 0:
			    if (!mseg->prev->rside || (mseg->prev->rside->type2 != TR_RBORDER) || (mseg->prev->rside->style != TR_WALL)) {
				SETPOINT(texLen - seg->width/curTexSize, 1.00, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z);
				SETPOINT(texLen - seg->width/curTexSize, 0.66, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z + seg->height);
			    }
			    SETPOINT(texLen, 1.0,  seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z);
			    SETPOINT(texLen, 0.66, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z + seg->height);
			    break;
			case 1:
			    SETPOINT(texLen, 0.66, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z + seg->height);
			    SETPOINT(texLen, 0.33, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z + seg->height);
			    break;
			case 2:
			    SETPOINT(texLen, 0.33, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z + seg->height);
			    SETPOINT(texLen, 0.0,  seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z);
			    break;
			}
			break;
		    }

		}
	    
		switch (seg->type) {
		case TR_STR:
		    ts = LMAX;
		    texStep = LMAX / curTexSize;
		    texLen += texStep;
		    trkpos.seg = seg;
		    while (ts < seg->length) {
			trkpos.toStart = ts;
			width = RtTrackGetWidth(seg, ts);
			texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

			switch (seg->style) {
			case TR_PLAN:
			    if (j == 0) {
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_CURB:
			    if (j == 0) {
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
			    } else if (j == 1) {
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_WALL:
			    switch (j) {
			    case 0:
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 1.0,  x, y, RtTrackHeightL(&trkpos));
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 1:
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 2:
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				SETPOINT(texLen, 0.0,  x, y, RtTrackHeightL(&trkpos));
				break;
			    }
			    break;
			}

			ts += LMAX;
			texLen += texStep;
		    }
		    ts = seg->length;
		    break;
		case TR_LFT:
		    step = LMAX / (mseg->radiusr);
		    texStep = step * mseg->radius / curTexSize;
		    anz = seg->angle[TR_ZS] + step;
		    ts = step;
		    texLen += texStep;
		    radiusr = seg->radiusr;
		    radiusl = seg->radiusl;
		    trkpos.seg = seg;
		    while (anz < seg->angle[TR_ZE]) {
			trkpos.toStart = ts;
			width = RtTrackGetWidth(seg, ts);
			texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

			switch (seg->style) {
			case TR_PLAN:
			    if (j == 0) {
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_CURB:
			    if (j == 0) {
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
			    } else if (j == 1) {
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_WALL:
			    switch (j) {
			    case 0:
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 1.0,  x, y, RtTrackHeightL(&trkpos));
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 1:
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 2:
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				SETPOINT(texLen, 0.0,  x, y, RtTrackHeightL(&trkpos));
				break;
			    }
			    break;
			}


			ts += step;
			texLen += texStep;
			anz += step;
		    }
		    ts = seg->arc;
		    break;
		case TR_RGT:
		    step = LMAX / (mseg->radiusl);
		    texStep = step * mseg->radius / curTexSize;
		    anz = seg->angle[TR_ZS] - step;
		    ts = step;
		    texLen += texStep;
		    radiusr = seg->radiusr;
		    radiusl = seg->radiusl;
		    trkpos.seg = seg;
		    while (anz > seg->angle[TR_ZE]) {
			trkpos.toStart = ts;
			width = RtTrackGetWidth(seg, ts);
			texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

			switch (seg->style) {
			case TR_PLAN:
			    if (j == 0) {
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_CURB:
			    if (j == 0) {
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos));
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
			    } else if (j == 1) {
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, texMaxT, x, y, RtTrackHeightL(&trkpos) + seg->height);
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0, x, y, RtTrackHeightL(&trkpos));
			    }
			    break;
			case TR_WALL:
			    switch (j) {
			    case 0:
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 1.0,  x, y, RtTrackHeightL(&trkpos));
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 1:
				/* left */
				trkpos.toRight = width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, RtTrackHeightL(&trkpos) + seg->height);
				/* right */
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				break;
			    case 2:
				trkpos.toRight = 0;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, RtTrackHeightL(&trkpos) + seg->height);
				SETPOINT(texLen, 0.0,  x, y, RtTrackHeightL(&trkpos));
				break;
			    }
			    break;
			}

			ts += step;
			texLen += texStep;
			anz -= step;
		    }
		    ts = seg->arc;
		    break;
		}
		texLen = (curTexSeg + mseg->length) / curTexSize;

		width = RtTrackGetWidth(seg, ts);
		texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

		switch (seg->style) {
		case TR_PLAN:
 		    if (j == 0) {
			SETPOINT(texLen, texMaxT, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z);
			SETPOINT(texLen, 0, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z);
		    }
		    break;
		case TR_CURB:
		    if (j == 0) {
			SETPOINT(texLen, texMaxT, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z);
			SETPOINT(texLen, texMaxT, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z + seg->height);
		    } else if (j == 1) {
			SETPOINT(texLen, texMaxT, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z + seg->height);
			SETPOINT(texLen, 0, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z);
			if (mseg->next->lside && ((mseg->next->lside->type2 != TR_LBORDER) || (mseg->next->lside->style != TR_CURB))) {
			    SETPOINT(texLen, texMaxT, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z);
/* 			    SETPOINT(texLen, 0, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z); */
			}
		    }
		    break;
		case TR_WALL:
		    switch (j) {
		    case 0:
			SETPOINT(texLen, 1.0,  seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z);
			SETPOINT(texLen, 0.66, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z + seg->height);
			if (mseg->next->lside && ((mseg->next->lside->type2 != TR_LBORDER) || (mseg->next->lside->style != TR_WALL))) {
			    SETPOINT(texLen + seg->width/curTexSize, 1.00, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z);
			    SETPOINT(texLen + seg->width/curTexSize, 0.66,  seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z + seg->height);
			}
			break;
		    case 1:
			SETPOINT(texLen, 0.66, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z + seg->height);
			SETPOINT(texLen, 0.33, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z + seg->height);
			break;
		    case 2:
			SETPOINT(texLen, 0.33, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z + seg->height);
			SETPOINT(texLen, 0.0,  seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z);
			break;
		    }
		    break;
		}

		startNeeded = 0;
		runninglentgh += seg->length;
	    } else {
		uniqueId++;
		NEWDISPLIST(0, "tkLtBr", uniqueId);
		startNeeded = 1;
	    }
	}
    }
    
    /* Left Side */
    prevTexId = 0;
    texLen = 0;
    startNeeded = 1;
    runninglentgh = 0;
    hasBorder = 0;
    uniqueId++;
    NEWDISPLIST(0, "tkLtSd", uniqueId);
    for (i = 0, mseg = Track->seg->next; i < Track->nseg; i++, mseg = mseg->next) {
	if ((mseg->lside != NULL) &&
	    ((mseg->lside->type2 == TR_LSIDE) || (mseg->lside->lside != NULL))) {
	    seg = mseg->lside;
	    if (seg->lside) {
		seg = seg->lside;
		if (hasBorder == 0) {
		    startNeeded = 1;
		    hasBorder = 1;
		}
	    } else {
		if (hasBorder) {
		    startNeeded = 1;
		    hasBorder = 0;
		}
	    }
	    uniqueId++;
	    CHECKDISPLIST(seg->surface->material, "tkLtSd", uniqueId, mseg->lgfromstart);
	    if (!curTexLink) {
		curTexSeg = 0;
	    } else {
		curTexSeg = mseg->lgfromstart;
	    }
	    curTexSeg += curTexOffset;
	    texLen = curTexSeg / curTexSize;
	    if (startNeeded || (runninglentgh > LG_STEP_MAX)) {
		uniqueId++;
		NEWDISPLIST(0, "tkLtSd", uniqueId);
		runninglentgh = 0;

		ts = 0;
		width = RtTrackGetWidth(seg, ts);
		texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = texMaxT;
		trackvertices[3*nbvert]   = seg->vertex[TR_SL].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SL].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SL].z;
		trackindices[nbvert]      = nbvert++;

		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0;
		trackvertices[3*nbvert]   = seg->vertex[TR_SR].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SR].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SR].z;
		trackindices[nbvert]      = nbvert++;
	    }
	    
	    switch (seg->type) {
	    case TR_STR:
		ts = LMAX;
		texStep = LMAX / curTexSize;
		texLen += texStep;
		trkpos.seg = seg;
		while (ts < seg->length) {
		    trkpos.toStart = ts;

		    width = RtTrackGetWidth(seg, ts);
		    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

		    trkpos.toRight = width;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = texMaxT;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    ts += LMAX;
		    texLen += texStep;
		}
		ts = seg->length;
		break;
	    case TR_LFT:
		step = LMAX / (mseg->radiusr);
		texStep = step * mseg->radius / curTexSize;
		anz = seg->angle[TR_ZS] + step;
		ts = step;
		texLen += texStep;
		radiusr = seg->radiusr;
		radiusl = seg->radiusl;
		trkpos.seg = seg;
		while (anz < seg->angle[TR_ZE]) {
		    trkpos.toStart = ts;
		    width = RtTrackGetWidth(seg, ts);
		    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

		    /* left */
		    trkpos.toRight = width;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = texMaxT;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    /* right */
		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    ts += step;
		    texLen += texStep;
		    anz += step;
		}
		ts = seg->arc;
		break;
	    case TR_RGT:
		step = LMAX / (mseg->radiusl);
		texStep = step * mseg->radius / curTexSize;
		anz = seg->angle[TR_ZS] - step;
		ts = step;
		texLen += texStep;
		radiusr = seg->radiusr;
		radiusl = seg->radiusl;
		trkpos.seg = seg;
		while (anz > seg->angle[TR_ZE]) {
		    trkpos.toStart = ts;
		    width = RtTrackGetWidth(seg, ts);
		    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

		    /* left */
		    trkpos.toRight = width;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = texMaxT;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    /* right */
		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    ts += step;
		    texLen += texStep;
		    anz -= step;
		}
		ts = seg->arc;
		break;
	    }
	    texLen = (curTexSeg + mseg->length) / curTexSize;

	    width = RtTrackGetWidth(seg, ts);
	    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));

	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = texMaxT;
	    trackvertices[3*nbvert]   = seg->vertex[TR_EL].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_EL].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_EL].z;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = 0;
	    trackvertices[3*nbvert]   = seg->vertex[TR_ER].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_ER].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_ER].z;
	    trackindices[nbvert]      = nbvert++;

	    startNeeded = 0;
	    runninglentgh += seg->length;
	} else {
	    uniqueId++;
	    NEWDISPLIST(0, "tkLtSd", uniqueId);
	    startNeeded = 1;
	}
    }


    /* Right barrier */
    for (j = 0; j < 3; j++) {
	prevTexId = 0;
	texLen = 0;
	startNeeded = 1;
	runninglentgh = 0;
	uniqueId++;
	NEWDISPLIST(0, "BrRt", uniqueId);
	for (i = 0, mseg = Track->seg->next; i < Track->nseg; i++, mseg = mseg->next) {
	    if ((mseg->rside != NULL) && (mseg->rside->raceInfo & TR_PIT)) {
		startNeeded = 1;
		runninglentgh = 0;
		uniqueId++;
		NEWDISPLIST(0, "BrRt", uniqueId);
	    } else {
		curBarrier = mseg->barrier[0];
		uniqueId++;
		CHECKDISPLIST(curBarrier->surface->material, "BrRt", uniqueId, 0);
		if (!curTexLink) {
		    curTexSeg = 0;
		} else {
		    curTexSeg = mseg->lgfromstart;
		}
		texLen = curTexSeg / curTexSize;
		if (mseg->rside) {
		    seg = mseg->rside;
		    if (seg->rside) {
			seg = seg->rside;
		    }
		} else {
		    seg = mseg;
		}
		trkpos.seg = seg;
		if (startNeeded || (runninglentgh > LG_STEP_MAX)) {
		    uniqueId++;
		    NEWDISPLIST(0, "brRt", uniqueId);
		    if (curTexType == 0) texLen = 0;
		    runninglentgh = 0;

		    switch (curBarrier->style) {
		    case TR_FENCE:
			if (j == 0) {
			    SETPOINT(texLen, 0,   seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z);
			    SETPOINT(texLen, 1.0, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z + curBarrier->height);
			}
			break;
		    case TR_WALL:	
			switch (j) {
			case 0:
			    SETPOINT(texLen, 0,    seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z);
			    SETPOINT(texLen, 0.33, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z + curBarrier->height);
			    break;
			case 1:
			    trkpos.toStart = 0;
			    trkpos.toRight = -curBarrier->width;
			    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			    SETPOINT(texLen, 0.33, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z + curBarrier->height);
			    SETPOINT(texLen, 0.66, x, y, seg->vertex[TR_SR].z + curBarrier->height);
			    break;
			case 2:
			    trkpos.toStart = 0;
			    trkpos.toRight = -curBarrier->width;
			    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			    if ((mseg->prev->barrier[0]->style != TR_WALL) || (mseg->prev->barrier[0]->height != curBarrier->height)) {
				SETPOINT(texLen - curBarrier->width/curTexSize, 0.66, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z + curBarrier->height);
				SETPOINT(texLen - curBarrier->width/curTexSize, 1.00, seg->vertex[TR_SR].x, seg->vertex[TR_SR].y, seg->vertex[TR_SR].z);
			    }
			    SETPOINT(texLen, 0.66, x, y, seg->vertex[TR_SR].z + curBarrier->height);
			    SETPOINT(texLen, 1.0,  x, y, seg->vertex[TR_SR].z);
			    break;
			}
			break;
		    }
		}
		switch (seg->type) {
		case TR_STR:
		    ts = LMAX;
		    texStep = LMAX / curTexSize;
		    texLen += texStep;
		    trkpos.seg = seg;
		    while (ts < seg->length) {
			trkpos.toStart = ts;
			trkpos.toRight = 0;
			RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			curHeight = RtTrackHeightL(&trkpos);
			
			switch (curBarrier->style) {
			case TR_FENCE:
			    if (j == 0) {
				SETPOINT(texLen, 0,   x, y, curHeight);
				SETPOINT(texLen, 1.0, x, y, curHeight + curBarrier->height);
			    }
			    break;
			case TR_WALL:	
			    switch (j) {
			    case 0:
				SETPOINT(texLen, 0.0,  x, y, curHeight);
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				break;
			    case 1:
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				trkpos.toRight = -curBarrier->width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				break;
			    case 2:
				trkpos.toRight = -curBarrier->width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				SETPOINT(texLen, 1.0,  x, y, curHeight);
				break;
			    }
			    break;
			}

			ts += LMAX;
			texLen += texStep;
		    }
		    ts = seg->length;
		    break;
		case TR_LFT:
		    step = LMAX / (mseg->radiusr);
		    texStep = step * mseg->radius / curTexSize;
		    anz = seg->angle[TR_ZS] + step;
		    ts = step;
		    texLen += texStep;
		    radiusr = seg->radiusr;
		    trkpos.seg = seg;
		    while (anz < seg->angle[TR_ZE]) {
			trkpos.toStart = ts;
			trkpos.toRight = 0;
			RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			curHeight = RtTrackHeightL(&trkpos);

			switch (curBarrier->style) {
			case TR_FENCE:
			    if (j == 0) {
				SETPOINT(texLen, 0.0, x, y, curHeight);
				SETPOINT(texLen, 1.0, x, y, curHeight + curBarrier->height);
			    }
			    break;
			case TR_WALL:	
			    switch (j) {
			    case 0:
				SETPOINT(texLen, 0.0,  x, y, curHeight);
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				break;
			    case 1:
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				trkpos.toRight = -curBarrier->width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				break;
			    case 2:
				trkpos.toRight = -curBarrier->width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				SETPOINT(texLen, 1.0,  x, y, curHeight);
				break;
			    }
			    break;
			}

			ts += step;
			texLen += texStep;
			anz += step;
		    }
		    ts = seg->arc;
		    break;
		case TR_RGT:
		    step = LMAX / (mseg->radiusl);
		    texStep = step * mseg->radius / curTexSize;
		    anz = seg->angle[TR_ZS] - step;
		    ts = step;
		    texLen += texStep;
		    radiusr = seg->radiusr;
		    trkpos.seg = seg;
		    while (anz > seg->angle[TR_ZE]) {
			trkpos.toStart = ts;
			trkpos.toRight = 0;
			RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			curHeight = RtTrackHeightL(&trkpos);

			switch (curBarrier->style) {
			case TR_FENCE:
			    if (j == 0) {
				SETPOINT(texLen, 0.0, x, y, curHeight);
				SETPOINT(texLen, 1.0, x, y, curHeight + curBarrier->height);
			    }
			    break;
			case TR_WALL:	
			    switch (j) {
			    case 0:
				SETPOINT(texLen, 0.0,  x, y, curHeight);
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				break;
			    case 1:
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				trkpos.toRight = -curBarrier->width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				break;
			    case 2:
				trkpos.toRight = -curBarrier->width;
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				SETPOINT(texLen, 1.0,  x, y, curHeight);
				break;
			    }
			    break;
			}
			ts += step;
			texLen += texStep;
			anz -= step;
		    }
		    ts = seg->arc;
		    break;
		}
		texLen = (curTexSeg + mseg->length) / curTexSize;
		switch (curBarrier->style) {
		case TR_FENCE:
		    if (j == 0) {
			SETPOINT(texLen, 0.0, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z);
			SETPOINT(texLen, 1.0, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z + curBarrier->height);
		    }
		    break;
		case TR_WALL:	
		    switch (j) {
		    case 0:
			SETPOINT(texLen, 0.0,  seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z);
			SETPOINT(texLen, 0.33, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z + curBarrier->height);
			break;
		    case 1:
			SETPOINT(texLen, 0.33, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z + curBarrier->height);
			trkpos.toStart = ts;
			trkpos.toRight = -curBarrier->width;
			RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			SETPOINT(texLen, 0.66, x, y, seg->vertex[TR_ER].z + curBarrier->height);
			break;
		    case 2:
			trkpos.toStart = ts;
			trkpos.toRight = -curBarrier->width;
			RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			SETPOINT(texLen, 0.66, x, y, seg->vertex[TR_ER].z + curBarrier->height);
			SETPOINT(texLen, 1.00, x, y, seg->vertex[TR_ER].z);
			if ((mseg->next->barrier[0]->style != TR_WALL) || (mseg->next->barrier[0]->height != curBarrier->height)) {
			    SETPOINT(texLen + curBarrier->width/curTexSize, 0.66, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z + curBarrier->height);
			    SETPOINT(texLen + curBarrier->width/curTexSize, 1.00, seg->vertex[TR_ER].x, seg->vertex[TR_ER].y, seg->vertex[TR_ER].z);
			}
			break;
		    }
		    break;
		}
		startNeeded = 0;
		runninglentgh += seg->length;
	    }
	}
    }
    
    /* Left Barrier */
    for (j = 0; j < 3; j++) {
	prevTexId = 0;
	texLen = 0;
	startNeeded = 1;
	runninglentgh = 0;
	uniqueId++;
	NEWDISPLIST(0, "BrLt", uniqueId);
	for (i = 0, mseg = Track->seg->next; i < Track->nseg; i++, mseg = mseg->next) {
	    if ((mseg->lside != NULL) && (mseg->lside->raceInfo & TR_PIT)) {
		runninglentgh = 0;
		startNeeded = 1;
		uniqueId++;
		NEWDISPLIST(0, "BrLt", uniqueId);
	    } else {
		curBarrier = mseg->barrier[1];
		uniqueId++;
		CHECKDISPLIST(curBarrier->surface->material, "BrLt", uniqueId, 0);
		if (!curTexLink) {
		    curTexSeg = 0;
		} else {
		    curTexSeg = mseg->lgfromstart;
		}
		texLen = curTexSeg / curTexSize;
		if (mseg->lside) {
		    seg = mseg->lside;
		    if (seg->lside) {
			seg = seg->lside;
		    }
		} else {
		    seg = mseg;
		}
		if (startNeeded || (runninglentgh > LG_STEP_MAX)) {
		    uniqueId++;
		    NEWDISPLIST(0, "BrLt", uniqueId);
		    runninglentgh = 0;
		    if (curTexType == 0) texLen = 0;


		    switch (curBarrier->style) {
		    case TR_FENCE:
			if (j == 0) {
			    SETPOINT(texLen, 1.0, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z + curBarrier->height);
			    SETPOINT(texLen, 0.0, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z);
			}
			break;
		    case TR_WALL:	
			switch (j) {
			case 0:
			    trkpos.toStart = 0;
			    trkpos.toRight = curBarrier->width + RtTrackGetWidth(seg, 0);
			    trkpos.seg = seg;
			    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			    if ((mseg->prev->barrier[1]->style != TR_WALL) || (mseg->prev->barrier[1]->height != curBarrier->height)) {
				SETPOINT(texLen - curBarrier->width/curTexSize, 1.00, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z);
				SETPOINT(texLen - curBarrier->width/curTexSize, 0.66, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z + curBarrier->height);
			    }
			    SETPOINT(texLen, 1.0,  x, y, seg->vertex[TR_SL].z);
			    SETPOINT(texLen, 0.66, x, y, seg->vertex[TR_SL].z + curBarrier->height);
			    break;
			case 1:
			    trkpos.toStart = 0;
			    trkpos.toRight = curBarrier->width + RtTrackGetWidth(seg, 0);
			    trkpos.seg = seg;
			    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			    SETPOINT(texLen, 0.66, x, y, seg->vertex[TR_SL].z + curBarrier->height);
			    SETPOINT(texLen, 0.33, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z + curBarrier->height);
			    break;
			case 2:
			    SETPOINT(texLen, 0.33, seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z + curBarrier->height);
			    SETPOINT(texLen, 0.0,  seg->vertex[TR_SL].x, seg->vertex[TR_SL].y, seg->vertex[TR_SL].z);
			    break;
			}
			break;
		    }
		}
	    
		switch (seg->type) {
		case TR_STR:
		    ts = LMAX;
		    texStep = LMAX / curTexSize;
		    texLen += texStep;
		    trkpos.seg = seg;
		    while (ts < seg->length) {
			trkpos.toStart = ts;
			trkpos.toRight = RtTrackGetWidth(seg, ts);
			RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			curHeight = RtTrackHeightL(&trkpos);

			switch (curBarrier->style) {
			case TR_FENCE:
			    if (j == 0) {
				SETPOINT(texLen, 1.0, x, y, curHeight + curBarrier->height);
				SETPOINT(texLen, 0,   x, y, curHeight);
			    }
			    break;
			case TR_WALL:	
			    switch (j) {
			    case 0:
				trkpos.toRight = curBarrier->width + RtTrackGetWidth(seg, ts);
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 1.0,  x, y, curHeight);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				break;
			    case 1:
				trkpos.toRight = curBarrier->width + RtTrackGetWidth(seg, ts);
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				trkpos.toRight = RtTrackGetWidth(seg, ts);
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				break;
			    case 2:
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				SETPOINT(texLen, 0,    x, y, curHeight);
				break;
			    }
			    break;
			}

			ts += LMAX;
			texLen += texStep;
		    }
		    ts = seg->length;
		    break;
		case TR_LFT:
		    step = LMAX / (mseg->radiusr);
		    texStep = step * mseg->radius / curTexSize;
		    anz = seg->angle[TR_ZS] + step;
		    ts = step;
		    texLen += texStep;
		    radiusl = seg->radiusl;
		    trkpos.seg = seg;
		    while (anz < seg->angle[TR_ZE]) {
			trkpos.toStart = ts;
			trkpos.toRight = RtTrackGetWidth(seg, ts);
			RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			curHeight = RtTrackHeightL(&trkpos);

			switch (curBarrier->style) {
			case TR_FENCE:
			    if (j == 0) {
				SETPOINT(texLen, 1.0, x, y, curHeight + curBarrier->height);
				SETPOINT(texLen, 0,   x, y, curHeight);
			    }
			    break;
			case TR_WALL:	
			    switch (j) {
			    case 0:
				trkpos.toRight = curBarrier->width + RtTrackGetWidth(seg, ts);
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 1.0,  x, y, curHeight);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				break;
			    case 1:
				trkpos.toRight = curBarrier->width + RtTrackGetWidth(seg, ts);
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				trkpos.toRight = RtTrackGetWidth(seg, ts);
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				break;
			    case 2:
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				SETPOINT(texLen, 0,    x, y, curHeight);
				break;
			    }
			    break;
			}

			ts += step;
			texLen += texStep;
			anz += step;
		    }
		    ts = seg->arc;
		    break;
		case TR_RGT:
		    step = LMAX / (mseg->radiusl);
		    texStep = step * mseg->radius / curTexSize;
		    anz = seg->angle[TR_ZS] - step;
		    ts = step;
		    texLen += texStep;
		    radiusl = seg->radiusl;
		    trkpos.seg = seg;
		    while (anz > seg->angle[TR_ZE]) {
			trkpos.toStart = ts;
			trkpos.toRight = RtTrackGetWidth(seg, ts);
			RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			curHeight = RtTrackHeightL(&trkpos);

			switch (curBarrier->style) {
			case TR_FENCE:
			    if (j == 0) {
				SETPOINT(texLen, 1.0, x, y, curHeight + curBarrier->height);
				SETPOINT(texLen, 0,   x, y, curHeight);
			    }
			    break;
			case TR_WALL:	
			    switch (j) {
			    case 0:
				trkpos.toRight = curBarrier->width + RtTrackGetWidth(seg, ts);
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 1.0,  x, y, curHeight);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				break;
			    case 1:
				trkpos.toRight = curBarrier->width + RtTrackGetWidth(seg, ts);
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.66, x, y, curHeight + curBarrier->height);
				trkpos.toRight = RtTrackGetWidth(seg, ts);
				RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				break;
			    case 2:
				SETPOINT(texLen, 0.33, x, y, curHeight + curBarrier->height);
				SETPOINT(texLen, 0,    x, y, curHeight);
				break;
			    }
			    break;
			}

			ts += step;
			texLen += texStep;
			anz -= step;
		    }
		    ts = seg->arc;
		    break;
		}
		texLen = (curTexSeg + mseg->length) / curTexSize;

		switch (curBarrier->style) {
		case TR_FENCE:
		    if (j == 0) {
			SETPOINT(texLen, 1.0, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z + curBarrier->height);
			SETPOINT(texLen, 0,   seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z);
		    }
		    break;
		case TR_WALL:	
		    switch (j) {
		    case 0:
			trkpos.toStart = ts;
			trkpos.toRight = curBarrier->width + RtTrackGetWidth(seg, ts);
			RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			SETPOINT(texLen, 1.0,  x, y, seg->vertex[TR_EL].z);
			SETPOINT(texLen, 0.66, x, y, seg->vertex[TR_EL].z + curBarrier->height);
			if ((mseg->next->barrier[1]->style != TR_WALL) || (mseg->next->barrier[1]->height != curBarrier->height)) {
			    SETPOINT(texLen + curBarrier->width/curTexSize, 1.00, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z);
			    SETPOINT(texLen + curBarrier->width/curTexSize, 0.66, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z + curBarrier->height);
			}
			break;
		    case 1:
			trkpos.toStart = ts;
			trkpos.toRight = curBarrier->width + RtTrackGetWidth(seg, ts);
			RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
			SETPOINT(texLen, 0.66, x, y, seg->vertex[TR_EL].z + curBarrier->height);
			SETPOINT(texLen, 0.33, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z + curBarrier->height);
			break;
		    case 2:
			SETPOINT(texLen, 0.33, seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z + curBarrier->height);
			SETPOINT(texLen, 0.0,  seg->vertex[TR_EL].x, seg->vertex[TR_EL].y, seg->vertex[TR_EL].z);
			break;
		    }
		    break;
		}

		startNeeded = 0;
		runninglentgh += seg->length;
	    }
	}
    }


    /* Turn Marks */
    for (i = 0, seg = Track->seg->next; i < Track->nseg; i++, seg = seg->next) {
	if (seg->ext) {
	    t3Dd	normvec;
	    int 	nbMarks = seg->ext->nbMarks;
	    int 	*marks  = seg->ext->marks;
	    int		j, k;

	    for (j = 0; j < nbMarks; j++) {
		uniqueId++;
		NEWDISPLIST(0, "TuMk", uniqueId);
		aDispElt->surfType = 0x10;
		/* find the segment */
		tdble lgfs = seg->lgfromstart - (tdble)marks[j];
		if (lgfs < 0) {
		    lgfs += Track->length;
		}
		for (k = 0, mseg = Track->seg->next; k < Track->nseg; k++, mseg = mseg->next) {
		    if ((lgfs >= mseg->lgfromstart) && (lgfs < (mseg->lgfromstart + mseg->length))) {
			break;
		    }
		}
		
		if (seg->type == TR_RGT) {
		    sprintf(buf, "turn%dR", marks[j]);
		    trkpos.toRight = Track->width + tmHSpace + tmWidth;
		} else {
		    sprintf(buf, "turn%dL", marks[j]);
		    trkpos.toRight = -tmHSpace;
		}
		trkpos.toStart = lgfs - mseg->lgfromstart;
		if (mseg->type != TR_STR) {
		    trkpos.toStart = trkpos.toStart / mseg->radius;
		}
		trkpos.seg = mseg;
		RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		z = tmVSpace + RtTrackHeightL(&trkpos);
		if (seg->type == TR_LFT) {
		    RtTrackSideNormalG(mseg, x, y, TR_RGT, &normvec);
		    normvec.x = -normvec.x;
		    normvec.y = -normvec.y;
		} else {
		    RtTrackSideNormalG(mseg, x, y, TR_LFT, &normvec);
		}
		uniqueId++;
		CHECKDISPLIST2(buf, 0, "TuMk", uniqueId);
		aDispElt->surfType = 0x10;
		tracktexcoord[2*nbvert]   = 0.0;
		tracktexcoord[2*nbvert+1] = 0.0;
		trackvertices[3*nbvert]   = x;
		trackvertices[3*nbvert+1] = y;
		trackvertices[3*nbvert+2] = z;
		trackindices[nbvert]      = nbvert++;

		tracktexcoord[2*nbvert]   = 1.0;
		tracktexcoord[2*nbvert+1] = 0.0;
		trackvertices[3*nbvert]   = x + tmWidth * normvec.x;
		trackvertices[3*nbvert+1] = y + tmWidth * normvec.y;
		trackvertices[3*nbvert+2] = z;
		trackindices[nbvert]      = nbvert++;

		tracktexcoord[2*nbvert]   = 0.0;
		tracktexcoord[2*nbvert+1] = 1.0;
		trackvertices[3*nbvert]   = x;
		trackvertices[3*nbvert+1] = y;
		trackvertices[3*nbvert+2] = z + tmHeight;
		trackindices[nbvert]      = nbvert++;

		tracktexcoord[2*nbvert]   = 1.0;
		tracktexcoord[2*nbvert+1] = 1.0;
		trackvertices[3*nbvert]   = x + tmWidth * normvec.x;
		trackvertices[3*nbvert+1] = y + tmWidth * normvec.y;
		trackvertices[3*nbvert+2] = z + tmHeight;
		trackindices[nbvert]      = nbvert++;

		uniqueId++;
		CHECKDISPLIST2("back-sign", 0, "TuMk", uniqueId);
		aDispElt->surfType = 0x10;
		tracktexcoord[2*nbvert]   = 0.0;
		tracktexcoord[2*nbvert+1] = 0.0;
		trackvertices[3*nbvert]   = x + tmWidth * normvec.x;
		trackvertices[3*nbvert+1] = y + tmWidth * normvec.y;
		trackvertices[3*nbvert+2] = z;
		trackindices[nbvert]      = nbvert++;

		tracktexcoord[2*nbvert]   = 1.0;
		tracktexcoord[2*nbvert+1] = 0.0;
		trackvertices[3*nbvert]   = x;
		trackvertices[3*nbvert+1] = y;
		trackvertices[3*nbvert+2] = z;
		trackindices[nbvert]      = nbvert++;

		tracktexcoord[2*nbvert]   = 0.0;
		tracktexcoord[2*nbvert+1] = 1.0;
		trackvertices[3*nbvert]   = x + tmWidth * normvec.x;
		trackvertices[3*nbvert+1] = y + tmWidth * normvec.y;
		trackvertices[3*nbvert+2] = z + tmHeight;
		trackindices[nbvert]      = nbvert++;

		tracktexcoord[2*nbvert]   = 1.0;
		tracktexcoord[2*nbvert+1] = 1.0;
		trackvertices[3*nbvert]   = x;
		trackvertices[3*nbvert+1] = y;
		trackvertices[3*nbvert+2] = z + tmHeight;
		trackindices[nbvert]      = nbvert++;

		printf("(%f, %f, %f), (%f, %f, %f)\n", x, y, z, x + tmWidth * normvec.x, y + tmWidth * normvec.y, z + tmHeight);
		
	    }
	}
    }
    
		
    

    /* Start Bridge */
    uniqueId++;
    CHECKDISPLIST2("pylon1", 4, "StBg", uniqueId);
#define BR_HEIGHT_1	8.0
#define BR_HEIGHT_2	6.0
#define BR_WIDTH_0	2.0
#define BR_WIDTH_1	2.0
    mseg = Track->seg->next;
    if (mseg->rside) {
	seg = mseg->rside;
	if (seg->rside) {
	    seg = seg->rside;
	}
    } else {
	seg = mseg;
    }

    x = seg->vertex[TR_SR].x;
    y = seg->vertex[TR_SR].y - 0.1;
    z = seg->vertex[TR_SR].z;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    x += BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    y -= BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    x -= BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z;
    trackindices[nbvert]      = nbvert++;
    
    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    y += BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z;
    trackindices[nbvert]      = nbvert++;
    
    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    
    uniqueId++;
    NEWDISPLIST(0, "StBg", uniqueId);

    if (mseg->lside) {
	seg = mseg->lside;
	if (seg->lside) {
	    seg = seg->lside;
	}
    } else {
	seg = mseg;
    }
    x2 = seg->vertex[TR_SL].x;
    y2 = seg->vertex[TR_SL].y + 0.1;
    z2 = seg->vertex[TR_SL].z;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z2;
    trackindices[nbvert]      = nbvert++;

    x2 += BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z2;
    trackindices[nbvert]      = nbvert++;

    y2 += BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z2;
    trackindices[nbvert]      = nbvert++;

    x2 -= BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z2;
    trackindices[nbvert]      = nbvert++;

    y2 -= BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z2;
    trackindices[nbvert]      = nbvert++;


















    uniqueId++;
    CHECKDISPLIST2("pylon2", 4, "StBg", uniqueId);


    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    y -= BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    x += BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    y += BR_WIDTH_1;
    
    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    x -= BR_WIDTH_0;
    
    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x + BR_WIDTH_0;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    y -= BR_WIDTH_1;
    
    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x + BR_WIDTH_0;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    y += BR_WIDTH_1;	/* back to origin */

    uniqueId++;
    NEWDISPLIST(0, "StBg", uniqueId);

    y2 += BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2 + BR_WIDTH_0;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    y2 -= BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2 + BR_WIDTH_0;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    x2 += BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    y2 += BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    x2 -= BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    y2 -= BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    /* Middle on the bridge */
    uniqueId++;
    CHECKDISPLIST2("pylon3", 4, "StBg", uniqueId);

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0.25;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0.25;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    x += BR_WIDTH_0;
    x2 += BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0.5;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0.5;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;


    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0.75;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0.75;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    x -= BR_WIDTH_0;
    x2 -= BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;




    /* draw the pits */
#define PIT_HEIGHT	5.0
#define PIT_DEEP	10.0
#define PIT_TOP		0.2

    pits = &(Track->pits);
    initPits(pits);
    
    if (pits->type == TR_PIT_ON_TRACK_SIDE) {
	t3Dd	normvec;

	uniqueId++;
	NEWDISPLIST(0, "Pits", uniqueId);
	uniqueId++;
	CHECKDISPLIST3("concrete2.rgb", 4, "Pits", uniqueId);

	RtTrackLocal2Global(&(pits->driversPits[0].pos), &x, &y, pits->driversPits[0].pos.type);
	RtTrackSideNormalG(pits->driversPits[0].pos.seg, x, y, pits->side, &normvec);
	z2 = RtTrackHeightG(pits->driversPits[0].pos.seg, x, y);

	x2 = x + PIT_TOP * normvec.x;
	y2 = y + PIT_TOP * normvec.y;

	tracktexcoord[2*nbvert]   = 1.0 - PIT_TOP;
	tracktexcoord[2*nbvert+1] = PIT_HEIGHT - PIT_TOP;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT - PIT_TOP;
	trackindices[nbvert]      = nbvert++;

	tracktexcoord[2*nbvert]   = 1.0 - PIT_TOP;
	tracktexcoord[2*nbvert+1] = PIT_HEIGHT;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT;
	trackindices[nbvert]      = nbvert++;

	x2 = x;
	y2 = y;

	tracktexcoord[2*nbvert]   = 1.0;
	tracktexcoord[2*nbvert+1] = PIT_HEIGHT - PIT_TOP;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT - PIT_TOP;
	trackindices[nbvert]      = nbvert++;

	x2 = x - PIT_DEEP * normvec.x;
	y2 = y - PIT_DEEP * normvec.y;

	tracktexcoord[2*nbvert]   = 1.0 + PIT_DEEP;
	tracktexcoord[2*nbvert+1] = PIT_HEIGHT;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT;
	trackindices[nbvert]      = nbvert++;

	x2 = x;
	y2 = y;

	tracktexcoord[2*nbvert]   = 1.0;
	tracktexcoord[2*nbvert+1] = 0;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2;
	trackindices[nbvert]      = nbvert++;

	x2 = x - PIT_DEEP * normvec.x;
	y2 = y - PIT_DEEP * normvec.y;

	tracktexcoord[2*nbvert]   = 1.0 + PIT_DEEP;
	tracktexcoord[2*nbvert+1] = 0;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2;
	trackindices[nbvert]      = nbvert++;
	
	for (i = 0; i < pits->driversPitsNb; i++) {
	    tdble dx, dy;

	    uniqueId++;
	    NEWDISPLIST(0, "Pits", uniqueId);
	    uniqueId++;
	    CHECKDISPLIST3("concrete.rgb", 4, "Pits", uniqueId);

	    RtTrackLocal2Global(&(pits->driversPits[i].pos), &x, &y, pits->driversPits[i].pos.type);
	    RtTrackSideNormalG(pits->driversPits[i].pos.seg, x, y, pits->side, &normvec);
	    x2 = x;
	    y2 = y;
	    z2 = RtTrackHeightG(pits->driversPits[i].pos.seg, x2, y2);
	    
	    if (pits->side == TR_RGT) {
		x3 = x + pits->len * normvec.y;
		y3 = y - pits->len * normvec.x;
	    } else {
		x3 = x - pits->len * normvec.y;
		y3 = y + pits->len * normvec.x;
	    }

	    z3 = RtTrackHeightG(pits->driversPits[i].pos.seg, x3, y3);

	    tracktexcoord[2*nbvert]   = pits->len;
	    tracktexcoord[2*nbvert+1] = 0;
	    trackvertices[3*nbvert]   = x2;
	    trackvertices[3*nbvert+1] = y2;
	    trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT - PIT_TOP;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = 0;
	    tracktexcoord[2*nbvert+1] = 0;
	    trackvertices[3*nbvert]   = x3;
	    trackvertices[3*nbvert+1] = y3;
	    trackvertices[3*nbvert+2] = z3 + PIT_HEIGHT - PIT_TOP;
	    trackindices[nbvert]      = nbvert++;

	    dx = PIT_TOP * normvec.x;
	    dy = PIT_TOP * normvec.y;

	    tracktexcoord[2*nbvert]   = pits->len;
	    tracktexcoord[2*nbvert+1] = PIT_TOP;
	    trackvertices[3*nbvert]   = x2 + dx;
	    trackvertices[3*nbvert+1] = y2 + dy;
	    trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT - PIT_TOP;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = 0;
	    tracktexcoord[2*nbvert+1] = PIT_TOP;
	    trackvertices[3*nbvert]   = x3 + dx;
	    trackvertices[3*nbvert+1] = y3 + dy;
	    trackvertices[3*nbvert+2] = z3 + PIT_HEIGHT - PIT_TOP;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = pits->len;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP;
	    trackvertices[3*nbvert]   = x2 + dx;
	    trackvertices[3*nbvert+1] = y2 + dy;
	    trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = 0;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP;
	    trackvertices[3*nbvert]   = x3 + dx;
	    trackvertices[3*nbvert+1] = y3 + dy;
	    trackvertices[3*nbvert+2] = z3 + PIT_HEIGHT;
	    trackindices[nbvert]      = nbvert++;

	    dx = - PIT_DEEP * normvec.x;
	    dy = - PIT_DEEP * normvec.y;

	    tracktexcoord[2*nbvert]   = pits->len;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP + PIT_DEEP;
	    trackvertices[3*nbvert]   = x2 + dx;
	    trackvertices[3*nbvert+1] = y2 + dy;
	    trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = 0;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP + PIT_DEEP;
	    trackvertices[3*nbvert]   = x3 + dx;
	    trackvertices[3*nbvert+1] = y3 + dy;
	    trackvertices[3*nbvert+2] = z3 + PIT_HEIGHT;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = pits->len;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP + PIT_DEEP + PIT_HEIGHT;
	    trackvertices[3*nbvert]   = x2 + dx;
	    trackvertices[3*nbvert+1] = y2 + dy;
	    trackvertices[3*nbvert+2] = z2;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = 0;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP + PIT_DEEP + PIT_HEIGHT;
	    trackvertices[3*nbvert]   = x3 + dx;
	    trackvertices[3*nbvert+1] = y3 + dy;
	    trackvertices[3*nbvert+2] = z3;
	    trackindices[nbvert]      = nbvert++;

	}
	uniqueId++;
	NEWDISPLIST(0, "Pits", uniqueId);
	uniqueId++;
	CHECKDISPLIST3("concrete2.rgb", 4, "Pits", uniqueId);

	i--;
	RtTrackLocal2Global(&(pits->driversPits[i].pos), &x, &y, pits->driversPits[i].pos.type);
	RtTrackSideNormalG(pits->driversPits[i].pos.seg, x, y, pits->side, &normvec);

	if (pits->side == TR_RGT) {
	    x = x + pits->len * normvec.y;
	    y = y - pits->len * normvec.x;
	} else {
	    x = x - pits->len * normvec.y;
	    y = y + pits->len * normvec.x;
	}
	

	z2 = RtTrackHeightG(pits->driversPits[i].pos.seg, x, y);

	x2 = x + PIT_TOP * normvec.x;
	y2 = y + PIT_TOP * normvec.y;

	tracktexcoord[2*nbvert]   = 1.0 - PIT_TOP;
	tracktexcoord[2*nbvert+1] = PIT_HEIGHT;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT;
	trackindices[nbvert]      = nbvert++;

	tracktexcoord[2*nbvert]   = 1.0 - PIT_TOP;
	tracktexcoord[2*nbvert+1] = PIT_HEIGHT - PIT_TOP;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT - PIT_TOP;
	trackindices[nbvert]      = nbvert++;

	x2 = x - PIT_DEEP * normvec.x;
	y2 = y - PIT_DEEP * normvec.y;

	tracktexcoord[2*nbvert]   = 1.0 + PIT_DEEP;
	tracktexcoord[2*nbvert+1] = PIT_HEIGHT;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT;
	trackindices[nbvert]      = nbvert++;

	x2 = x;
	y2 = y;

	tracktexcoord[2*nbvert]   = 1.0;
	tracktexcoord[2*nbvert+1] = PIT_HEIGHT - PIT_TOP;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT - PIT_TOP;
	trackindices[nbvert]      = nbvert++;

	x2 = x - PIT_DEEP * normvec.x;
	y2 = y - PIT_DEEP * normvec.y;

	tracktexcoord[2*nbvert]   = 1.0 + PIT_DEEP;
	tracktexcoord[2*nbvert+1] = 0;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2;
	trackindices[nbvert]      = nbvert++;

	x2 = x;
	y2 = y;

	tracktexcoord[2*nbvert]   = 1.0;
	tracktexcoord[2*nbvert+1] = 0;
	trackvertices[3*nbvert]   = x2;
	trackvertices[3*nbvert+1] = y2;
	trackvertices[3*nbvert+2] = z2;
	trackindices[nbvert]      = nbvert++;

    }

    CLOSEDISPLIST();
    

    printf("=== Indices really used = %d\n", nbvert);
    
    return 0;
}



int
CountMainTrack(void)
{
    int		NbMainTrackObjects;
    tDispElt	*aDispElt;

    NbMainTrackObjects = 0;
    if (DispList != NULL) {
	aDispElt = DispList;
	do {
	    aDispElt = aDispElt->next;
	    if (aDispElt->nb != 0) {
		NbMainTrackObjects++;
	    }
	} while (aDispElt != DispList);
    }
    return NbMainTrackObjects;
}



static void
saveObject(FILE *curFd, int nb, int start, char *texture, char *name, int surfType)
{
    int	i, index;
    
    fprintf(curFd, "OBJECT poly\n");
    fprintf(curFd, "name \"%s\"\n", name);    
    fprintf(curFd, "texture \"%s\"\n", texture);
    fprintf(curFd, "numvert %d\n", nb);

    for (i = 0; i < nb; i++) {
	index = 3 * (start + i);
	fprintf(curFd, "%f %f %f\n", trackvertices[index], trackvertices[index+2], -trackvertices[index+1]);
    }

    fprintf(curFd, "numsurf %d\n", nb - 2);
    if (surfType) {
	fprintf(curFd, "SURF 0x10\n");
    } else {
	fprintf(curFd, "SURF 0x30\n");
    }
    fprintf(curFd, "mat 0\n");
    fprintf(curFd, "refs 3\n");
    fprintf(curFd, "%d %f %f\n", 0, tracktexcoord[2*start], tracktexcoord[2*start+1]);
    fprintf(curFd, "%d %f %f\n", 1, tracktexcoord[2*(start+1)], tracktexcoord[2*(start+1)+1]);
    fprintf(curFd, "%d %f %f\n", 2, tracktexcoord[2*(start+2)], tracktexcoord[2*(start+2)+1]);
   
    /* triangle strip conversion to triangles */
    for (i = 2; i < nb-1; i++) {
	if (surfType) {
	    fprintf(curFd, "SURF 0x10\n");
	} else {
	    fprintf(curFd, "SURF 0x30\n");
	}
	fprintf(curFd, "mat 0\n");
	fprintf(curFd, "refs 3\n");
	if ((i % 2) == 0) {
	    index = i;
	    fprintf(curFd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	    index = i - 1;
	    fprintf(curFd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	    index = i + 1;
	    fprintf(curFd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	} else {
	    index = i - 1;
	    fprintf(curFd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	    index = i;
	    fprintf(curFd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	    index = i + 1;
	    fprintf(curFd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	}
    }
    fprintf(curFd, "kids 0\n");
}


static void
SaveMainTrack(FILE *curFd)
{
    tDispElt	*aDispElt;
    char	buf[256];

    if (DispList != NULL) {
	aDispElt = DispList;
	do {
	    aDispElt = aDispElt->next;
	    if (aDispElt->nb != 0) {
		sprintf(buf, "%s %d", aDispElt->name, aDispElt->id);
		saveObject(curFd, aDispElt->nb, aDispElt->start, aDispElt->texture->name, buf, aDispElt->surfType);
	    }
	} while (aDispElt != DispList);
    }
}


/** Generate the track AC3D file(s).
    @param	Track	track structure
    @param	TrackHandle	handle on the track description
    @param	outFile	output file name for track only
    @param	AllFd	fd of the merged file
    @return	none
*/
void
GenerateTrack(tTrack * Track, void *TrackHandle, char *outFile, FILE *AllFd)
{
    FILE *curFd;
    
    TrackStep = GfParmGetNum(TrackHandle, TRK_SECT_TERRAIN, TRK_ATT_TSTEP, NULL, TrackStep);
    GfOut("Track step: %.2f", TrackStep);

    InitScene(Track, TrackHandle);

    if (outFile) {
	curFd = Ac3dOpen(outFile, 1);
	Ac3dGroup(curFd, "track", CountMainTrack());
	SaveMainTrack(curFd);
	Ac3dClose(curFd);
    }
    
    if (AllFd) {
	Ac3dGroup(AllFd, "track", CountMainTrack());
	SaveMainTrack(AllFd);
    }
    
}
