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
#include <unistd.h>
#include <math.h>

#include <tgf.h>
#include <track.h>
#include <robottools.h>

#include "easymesh.h"

#include "trackgen.h"

#define CFG_FILE	"tools/trackgen/trackgen.xml"

tModList	*modlist = NULL;
void		*cfg;

tTrackItf	TrackItf;
tTrack		*Track;

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

static float borderHeight = 0.6;

static void
initPits(tTrackPitInfo *pits)
{
    tTrackSeg	*curMainSeg;
    tTrackSeg	*curPitSeg = NULL;
    tdble	toStart = 0;
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
		curMainSeg = curMainSeg->next;
		switch (pits->side) {
		case TR_RGT:
		    curPitSeg = curMainSeg->rside;
		    break;
		case TR_LFT:
		    curPitSeg = curMainSeg->lside;
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
		curPos.toRight  = -RtTrackGetWidth(curPitSeg, toStart);
		curPos.toLeft   = curMainSeg->width - curPos.toRight;
		curPos.toMiddle = curMainSeg->width / 2.0 - curPos.toRight;
		break;
	    case TR_LFT:
		curPos.toLeft   = -RtTrackGetWidth(curPitSeg, toStart);
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
LoadTrackModule(void)
{
    char	*trackdllname;
    char	buf[256];

    sprintf(buf, "%s/%s", INSTBASE, CFG_FILE);
    cfg = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    trackdllname = GfParmGetStr(cfg, "Modules", "track", "track");
    sprintf(buf, "%s/modules/track/%s.%s", INSTBASE, trackdllname, DLLEXT);
    if (GfModLoad(TRK_IDENT, buf, &modlist) < 0) {
	GfOut("Failed to find the track module %s", buf);
	return -1;
    }
    return modlist->modInfo->fctInit(modlist->modInfo->index, &TrackItf);
}

int
InitScene(tTrack *track)
{

    int 		i;
    void		*hndl;
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
    int			nbSets;
    tdble		tr;
    int			startNeeded;

    tDispElt		*aDispElt = NULL;
    unsigned int	prevTexId;
    unsigned int	curTexId = 0;
    int			curTexType = 0;
    int			curTexLink = 0;
    tdble		curTexOffset = 0;
    tdble		curTexSeg;
    tdble		curTexSize = 0;
    tTexElt		*texList = (tTexElt*)NULL;
    tTexElt		*curTexElt = NULL;
    tdble		texLen;
    tdble		texStep;
    tdble		texMaxT = 0;
    tTrackPitInfo	*pits;
    static int		GenTexId = 1;
    tdble		runninglentgh;

    tdble		tmWidth  = track->graphic.turnMarksInfo.width;
    tdble		tmHeight = track->graphic.turnMarksInfo.height;
    tdble		tmVSpace = track->graphic.turnMarksInfo.vSpace;
    tdble		tmHSpace = track->graphic.turnMarksInfo.hSpace;
    char		buf[256];
    int			uniqueId = 0;
    
    
    
#define	LG_STEP_MAX	50.0

    printf("++++++++++++ Track ++++++++++++\n");
    printf("name      = %s\n", track->name);
    printf("author    = %s\n", track->author);
    printf("filename  = %s\n", track->filename);
    printf("nseg      = %d\n", track->nseg);
    printf("version   = %d\n", track->version);
    printf("length    = %f\n", track->length);
    printf("width     = %f\n", track->width);
    printf("XSize     = %f\n", track->max.x);
    printf("YSize     = %f\n", track->max.y);
    printf("ZSize     = %f\n", track->max.z);

    tdble delatx = track->seg->next->vertex[TR_SL].x - track->seg->vertex[TR_EL].x;
    tdble delaty = track->seg->next->vertex[TR_SL].y - track->seg->vertex[TR_EL].y;
    tdble delatz = track->seg->next->vertex[TR_SL].z - track->seg->vertex[TR_EL].z;
    tdble delata = track->seg->next->angle[TR_ZE] - track->seg->angle[TR_ZS];
    
    printf("Delta X   = %f\n", delatx);
    printf("Delta Y   = %f\n", delaty);
    printf("Delta Z   = %f\n", delatz);
    printf("Delta Ang = %f (%f)\n", delata, RAD2DEG(delata));

    if ((fabs(delatx) > 1.0) || (fabs(delaty) > 1.0) || (fabs(delatz) > 1.0)) {
/* 	exit(0); */
    }

    width = track->width;
    wi2 = width / 2.0;

    trkpos.type = TR_LPOS_MAIN;
    hndl = GfParmReadFile(track->filename, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

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
	char path_[256];								\
	sprintf(path_, "%s/%s/%s", TRK_SECT_SURFACES, TRK_LST_SURF, mat);		\
	texname = GfParmGetStr(hndl, path_, TRK_ATT_TEXTURE, "tr-asphalt.rgb");		\
	mipmap = (int)GfParmGetNum(hndl, path_, TRK_ATT_TEXMIPMAP, (char*)NULL, 0);	\
	SETTEXTURE(texname, mipmap);							\
	if ((curTexId != prevTexId) || (startNeeded)) {					\
	    char *textype;								\
	    textype = GfParmGetStr(hndl, path_, TRK_ATT_TEXTYPE, "continuous"); 	\
	    if (strcmp(textype, "continuous") == 0)					\
		curTexType = 1;								\
	    else									\
		curTexType = 0;								\
	    textype = GfParmGetStr(hndl, path_, TRK_ATT_TEXLINK, TRK_VAL_YES);		\
	    if (strcmp(textype, TRK_VAL_YES) == 0)					\
		curTexLink = 1;								\
	    else									\
		curTexLink = 0;								\
	    textype = GfParmGetStr(hndl, path_, TRK_ATT_TEXSTARTBOUNDARY, TRK_VAL_NO);	\
	    if (strcmp(textype, TRK_VAL_YES) == 0)					\
		curTexOffset = -off;							\
	    else									\
		curTexOffset = 0;							\
	    curTexSize = GfParmGetNum(hndl, path_, TRK_ATT_TEXSIZE, (char*)NULL, 20.0); \
	    prevTexId = curTexId;							\
	    NEWDISPLIST(1, name, id);							\
	}										\
    } while (0)

#define CHECKDISPLIST2(texture, mipmap, name, id) {		\
	char texname[256];					\
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
    
/*     cggrWrldX = (int)(track->max.x - track->min.x + 1); */
/*     cggrWrldY = (int)(track->max.y - track->min.y + 1); */
/*     cggrWrldZ = (int)(track->max.z - track->min.z + 1); */
/*     cggrWrldMaxSize = (int)(MAX(MAX(cggrWrldX, cggrWrldY), cggrWrldZ)); */

    nbSets = 5;
    
    /* Count the number of vertice to allocate */
    nbvert = 0;
    for (i = 0, seg = track->seg->next; i < track->nseg; i++, seg = seg->next) {
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
    nbvert *= 11;
    nbvert+=58; /* start bridge */
    nbvert+=12 + 10 * track->pits.driversPitsNb;
    nbvert+=1000;
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
    for (i = 0, seg = track->seg->next; i < track->nseg; i++, seg = seg->next) {
	uniqueId++;
	CHECKDISPLIST(seg->material, "tkMn", uniqueId, seg->lgfromstart);
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
	    tracktexcoord[2*nbvert+1] = 0.0;
	    
	    trackvertices[3*nbvert]   = seg->vertex[TR_SR].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_SR].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_SR].z;
	    trackindices[nbvert]      = nbvert++;
	    
	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = texMaxT;
	    
	    trackvertices[3*nbvert]   = seg->vertex[TR_SL].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_SL].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_SL].z;
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
		trkpos.toRight = 0;
		RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0.0;

		trackvertices[3*nbvert]   = x;
		trackvertices[3*nbvert+1] = y;
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		trackindices[nbvert]      = nbvert++;

		trkpos.toRight = width;
		RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = texMaxT;

		trackvertices[3*nbvert]   = x;
		trackvertices[3*nbvert+1] = y;
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		trackindices[nbvert]      = nbvert++;

		ts += LMAX;
	    }
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
		/* right */
		trkpos.toRight = 0;
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0.0;

		trackvertices[3*nbvert]   = seg->center.x + radiusr * sin(anz);
		trackvertices[3*nbvert+1] = seg->center.y - radiusr * cos(anz);
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		trackindices[nbvert]      = nbvert++;

		/* left */
		trkpos.toRight = width;
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = texMaxT;

		trackvertices[3*nbvert]   = seg->center.x + radiusl * sin(anz);
		trackvertices[3*nbvert+1] = seg->center.y - radiusl * cos(anz);
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);

		trackindices[nbvert]      = nbvert++;

		ts += step;
		anz += step;
	    }
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
		/* right */
		trkpos.toStart = ts;
		trkpos.toRight = 0;
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0;

		trackvertices[3*nbvert]   = seg->center.x - radiusr * sin(anz);
		trackvertices[3*nbvert+1] = seg->center.y + radiusr * cos(anz);
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		trackindices[nbvert]      = nbvert++;
		/* left */
		trkpos.toRight = width;
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = texMaxT;

		trackvertices[3*nbvert]   = seg->center.x - radiusl * sin(anz);
		trackvertices[3*nbvert+1] = seg->center.y + radiusl * cos(anz);
		trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		trackindices[nbvert]      = nbvert++;
		ts += step;
		anz -= step;
	    }
	    break;
	}
	texLen = (curTexSeg + seg->length) / curTexSize;
	tracktexcoord[2*nbvert]   = texLen;
	tracktexcoord[2*nbvert+1] = 0;

	trackvertices[3*nbvert]   = seg->vertex[TR_ER].x;
	trackvertices[3*nbvert+1] = seg->vertex[TR_ER].y;
	trackvertices[3*nbvert+2] = seg->vertex[TR_ER].z;
	trackindices[nbvert]      = nbvert++;

	tracktexcoord[2*nbvert]   = texLen;
	tracktexcoord[2*nbvert+1] = texMaxT;

	trackvertices[3*nbvert]   = seg->vertex[TR_EL].x;
	trackvertices[3*nbvert+1] = seg->vertex[TR_EL].y;
	trackvertices[3*nbvert+2] = seg->vertex[TR_EL].z;
	trackindices[nbvert]      = nbvert++;
	startNeeded = 0;
	runninglentgh += seg->length;
    }

    /* Right Side */
    prevTexId = 0;
    texLen = 0;
    startNeeded = 1;
    runninglentgh = 0;
    uniqueId++;
    NEWDISPLIST(0, "tkRtSd", uniqueId);
    for (i = 0, mseg = track->seg->next; i < track->nseg; i++, mseg = mseg->next) {
	if ((mseg->rside != NULL) && (mseg->ralt == NULL)) {
	    seg = mseg->rside;
	    uniqueId++;
	    CHECKDISPLIST(seg->material, "tkRtSd", uniqueId, mseg->lgfromstart);
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
		//if (curTexType == 0) texLen = 0;
		ts = 0;
		texMaxT = RtTrackGetWidth(seg, ts);
		texMaxT = (curTexType == 1 ? texMaxT / curTexSize : 1.0 + floor(texMaxT / curTexSize));
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = texMaxT;
		trackvertices[3*nbvert]   = seg->vertex[TR_SR].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SR].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SR].z;
		trackindices[nbvert]      = nbvert++;

		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0;
		trackvertices[3*nbvert]   = seg->vertex[TR_SL].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SL].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SL].z;
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
		    trkpos.toRight = 0 ;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = texMaxT;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;
		    trkpos.toRight = width;
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
		    /* right */
		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = texMaxT;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;
		    /* left */
		    trkpos.toRight = width;
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
		    /* right */
		    trkpos.toStart = ts;
		    width = RtTrackGetWidth(seg, ts);
		    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));
		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = texMaxT;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;
		    /* left */
		    trkpos.toRight = width;
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
		break;
	    }
	    texLen = (curTexSeg + mseg->length) / curTexSize;

	    width = RtTrackGetWidth(seg, ts);
	    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));
	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = texMaxT;
	    trackvertices[3*nbvert]   = seg->vertex[TR_ER].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_ER].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_ER].z;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = 0;
	    trackvertices[3*nbvert]   = seg->vertex[TR_EL].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_EL].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_EL].z;
	    trackindices[nbvert]      = nbvert++;
	    startNeeded = 0;
	    runninglentgh += seg->length;
	} else {
	    uniqueId++;
	    NEWDISPLIST(0, "tkRtSd", uniqueId);
	    startNeeded = 1;
	}
    }


    /* Left Side */
    prevTexId = 0;
    texLen = 0;
    startNeeded = 1;
    runninglentgh = 0;
    uniqueId++;
    NEWDISPLIST(0, "tkLtSd", uniqueId);
    for (i = 0, mseg = track->seg->next; i < track->nseg; i++, mseg = mseg->next) {
	if ((mseg->lside != NULL) && (mseg->lalt == NULL)) {
	    seg = mseg->lside;
	    uniqueId++;
	    CHECKDISPLIST(seg->material, "tkLtSd", uniqueId, mseg->lgfromstart);
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
		//if (curTexType == 0) texLen = 0;
		runninglentgh = 0;
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0;
		trackvertices[3*nbvert]   = seg->vertex[TR_SR].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SR].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SR].z;
		trackindices[nbvert]      = nbvert++;
		ts = 0;
		width = RtTrackGetWidth(seg, ts);
		texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = texMaxT;
		trackvertices[3*nbvert]   = seg->vertex[TR_SL].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SL].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SL].z;
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
		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;
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
		    ts += LMAX;
		    texLen += texStep;
		}
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
		    /* right */
		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;
		    /* left */
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
		    ts += step;
		    texLen += texStep;
		    anz += step;
		}
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
		    /* right */
		    trkpos.toStart = ts;
		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;
		    /* left */
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
		    ts += step;
		    texLen += texStep;
		    anz -= step;
		}
		break;
	    }
	    texLen = (curTexSeg + mseg->length) / curTexSize;
	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = 0;
	    trackvertices[3*nbvert]   = seg->vertex[TR_ER].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_ER].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_ER].z;
	    trackindices[nbvert]      = nbvert++;

	    width = RtTrackGetWidth(seg, ts);
	    texMaxT = (curTexType == 1 ?  width / curTexSize : 1.0 + floor(width / curTexSize));
	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = texMaxT;
	    trackvertices[3*nbvert]   = seg->vertex[TR_EL].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_EL].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_EL].z;
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
    prevTexId = 0;
    texLen = 0;
    startNeeded = 1;
    runninglentgh = 0;
    uniqueId++;
    NEWDISPLIST(0, "brRt", uniqueId);
    for (i = 0, mseg = track->seg->next; i < track->nseg; i++, mseg = mseg->next) {
	if ((mseg->ralt != NULL) || ((mseg->rside != NULL) && (mseg->rside->raceInfo & TR_PIT))) {
	    startNeeded = 1;
	    runninglentgh = 0;
	    uniqueId++;
	    NEWDISPLIST(0, "brRt", uniqueId);
	} else {
	    uniqueId++;
	    CHECKDISPLIST("barrier", "brRt", uniqueId, 0);
	    if (!curTexLink) {
		curTexSeg = 0;
	    } else {
		curTexSeg = mseg->lgfromstart;
	    }
	    texLen = curTexSeg / curTexSize;
	    if (mseg->rside != NULL) {
		seg = mseg->rside;
		tr = -seg->width;
	    } else {
		seg = mseg;
		tr = 0;
	    }
	    if (startNeeded || (runninglentgh > LG_STEP_MAX)) {
		uniqueId++;
		NEWDISPLIST(0, "brRt", uniqueId);
		if (curTexType == 0) texLen = 0;
		runninglentgh = 0;
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0;
		trackvertices[3*nbvert]   = seg->vertex[TR_SR].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SR].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SR].z;
		trackindices[nbvert]      = nbvert++;

		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 1.0;
		trackvertices[3*nbvert]   = seg->vertex[TR_SR].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SR].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SR].z + borderHeight;
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
		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 1.0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos) + borderHeight;
		    trackindices[nbvert]      = nbvert++;
		    ts += LMAX;
		    texLen += texStep;
		}
		break;
	    case TR_LFT:
		step = LMAX / (mseg->radiusr);
		texStep = step * mseg->radius / curTexSize;
		anz = seg->angle[TR_ZS] + step;
		ts = step;
		texLen += texStep;
		radiusr = seg->radiusr;
		trkpos.seg = seg;
		trkpos.toRight = 0;
		while (anz < seg->angle[TR_ZE]) {
		    trkpos.toStart = ts;
		    /* right */
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 1.0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos) + borderHeight;
		    trackindices[nbvert]      = nbvert++;
		    ts += step;
		    texLen += texStep;
		    anz += step;
		}
		break;
	    case TR_RGT:
		step = LMAX / (mseg->radiusl);
		texStep = step * mseg->radius / curTexSize;
		anz = seg->angle[TR_ZS] - step;
		ts = step;
		texLen += texStep;
		radiusr = seg->radiusr;
		trkpos.seg = seg;
		trkpos.toRight = 0;
		while (anz > seg->angle[TR_ZE]) {
		    trkpos.toStart = ts;
		    /* right */
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 1.0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos) + borderHeight;
		    trackindices[nbvert]      = nbvert++;
		    ts += step;
		    texLen += texStep;
		    anz -= step;
		}
		break;
	    }
	    texLen = (curTexSeg + mseg->length) / curTexSize;
	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = 0;
	    trackvertices[3*nbvert]   = seg->vertex[TR_ER].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_ER].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_ER].z;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = 1.0;
	    trackvertices[3*nbvert]   = seg->vertex[TR_ER].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_ER].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_ER].z + borderHeight;
	    trackindices[nbvert]      = nbvert++;
	    startNeeded = 0;
	    runninglentgh += seg->length;
	}
    }

    /* Left Barrier */
    prevTexId = 0;
    texLen = 0;
    startNeeded = 1;
    runninglentgh = 0;
    uniqueId++;
    NEWDISPLIST(0, "BrLt", uniqueId);
    for (i = 0, mseg = track->seg->next; i < track->nseg; i++, mseg = mseg->next) {
	if ((mseg->lalt != NULL) || ((mseg->lside != NULL) && (mseg->lside->raceInfo & TR_PIT))) {
	    runninglentgh = 0;
	    startNeeded = 1;
	    uniqueId++;
	    NEWDISPLIST(0, "BrLt", uniqueId);
	} else {
	    uniqueId++;
	    CHECKDISPLIST("barrier", "BrLt", uniqueId, 0);
	    if (!curTexLink) {
		curTexSeg = 0;
	    } else {
		curTexSeg = mseg->lgfromstart;
	    }
	    texLen = curTexSeg / curTexSize;
	    if (mseg->lside) {
		seg = mseg->lside;
		tr = width + seg->width;
	    } else {
		seg = mseg;
		tr = width;
	    }
	    if (startNeeded || (runninglentgh > LG_STEP_MAX)) {
		uniqueId++;
		NEWDISPLIST(0, "BrLt", uniqueId);
		runninglentgh = 0;
		if (curTexType == 0) texLen = 0;
		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 0;
		trackvertices[3*nbvert]   = seg->vertex[TR_SL].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SL].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SL].z;
		trackindices[nbvert]      = nbvert++;

		tracktexcoord[2*nbvert]   = texLen;
		tracktexcoord[2*nbvert+1] = 1.0;
		trackvertices[3*nbvert]   = seg->vertex[TR_SL].x;
		trackvertices[3*nbvert+1] = seg->vertex[TR_SL].y;
		trackvertices[3*nbvert+2] = seg->vertex[TR_SL].z + borderHeight;
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
		    trkpos.toRight = RtTrackGetWidth(seg, ts);
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 1.0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos) + borderHeight;
		    trackindices[nbvert]      = nbvert++;
		    ts += LMAX;
		    texLen += texStep;
		}
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
		    /* left */
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 1.0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos) + borderHeight;
		    trackindices[nbvert]      = nbvert++;
		    ts += step;
		    texLen += texStep;
		    anz += step;
		}
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
		    /* left */
		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos);
		    trackindices[nbvert]      = nbvert++;

		    tracktexcoord[2*nbvert]   = texLen;
		    tracktexcoord[2*nbvert+1] = 1.0;
		    trackvertices[3*nbvert]   = x;
		    trackvertices[3*nbvert+1] = y;
		    trackvertices[3*nbvert+2] = RtTrackHeightL(&trkpos) + borderHeight;
		    trackindices[nbvert]      = nbvert++;
		    ts += step;
		    texLen += texStep;
		    anz -= step;
		}
		break;
	    }
	    texLen = (curTexSeg + mseg->length) / curTexSize;
	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = 0;
	    trackvertices[3*nbvert]   = seg->vertex[TR_EL].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_EL].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_EL].z;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = texLen;
	    tracktexcoord[2*nbvert+1] = 1.0;
	    trackvertices[3*nbvert]   = seg->vertex[TR_EL].x;
	    trackvertices[3*nbvert+1] = seg->vertex[TR_EL].y;
	    trackvertices[3*nbvert+2] = seg->vertex[TR_EL].z + borderHeight;
	    trackindices[nbvert]      = nbvert++;
	    startNeeded = 0;
	    runninglentgh += seg->length;
	}
    }

    /* Turn Marks */
    for (i = 0, seg = track->seg->next; i < track->nseg; i++, seg = seg->next) {
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
		    lgfs += track->length;
		}
		for (k = 0, mseg = track->seg->next; k < track->nseg; k++, mseg = mseg->next) {
		    if ((lgfs >= mseg->lgfromstart) && (lgfs < (mseg->lgfromstart + mseg->length))) {
			break;
		    }
		}
		
		if (seg->type == TR_RGT) {
		    sprintf(buf, "turn%dR", marks[j]);
		    trkpos.toRight = track->width + tmHSpace + tmWidth;
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
    mseg = track->seg->next;
    if (mseg->rside) {
	seg = mseg->rside;
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
    CHECKDISPLIST2("pylon2", 4, "StBg", uniqueId);


    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    y -= BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    x += BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    y += BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;
    
    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    x -= BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;
    
    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x + BR_WIDTH_0;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    y -= BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;
    
    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x + BR_WIDTH_0;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    y += BR_WIDTH_1;	/* back to origin */
    
    uniqueId++;
    CHECKDISPLIST2("pylon1", 4, "StBg", uniqueId);

    if (mseg->lside) {
	seg = mseg->lside;
    } else {
	seg = mseg;
    }
    x2 = seg->vertex[TR_SL].x;
    y2 = seg->vertex[TR_SL].y + 0.1;
    z2 = seg->vertex[TR_SL].z;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    x2 += BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    y2 += BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    x2 -= BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    y2 -= BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    uniqueId++;
    CHECKDISPLIST2("pylon2", 4, "StBg", uniqueId);

    y2 += BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2 + BR_WIDTH_0;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    y2 -= BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2 + BR_WIDTH_0;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    x2 += BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    y2 += BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 2;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    x2 -= BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 3;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    y2 -= BR_WIDTH_1;

    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 4;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

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
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    x += BR_WIDTH_0;
    x2 += BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 2;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 2;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    uniqueId++;
    NEWDISPLIST(0, "StBg", uniqueId);

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_1;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    uniqueId++;
    CHECKDISPLIST2("pylon1", 4, "StBg", uniqueId);

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 1;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    x -= BR_WIDTH_0;
    x2 -= BR_WIDTH_0;

    tracktexcoord[2*nbvert]   = 0;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x;
    trackvertices[3*nbvert+1] = y;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;

    tracktexcoord[2*nbvert]   = 1;
    tracktexcoord[2*nbvert+1] = 0;
    trackvertices[3*nbvert]   = x2;
    trackvertices[3*nbvert+1] = y2;
    trackvertices[3*nbvert+2] = z + BR_HEIGHT_2;
    trackindices[nbvert]      = nbvert++;


    /* draw the pits */
#define PIT_HEIGHT	5.0
#define PIT_DEEP	10.0
#define PIT_TOP		0.2

    pits = &(track->pits);
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

	    tracktexcoord[2*nbvert]   = 0;
	    tracktexcoord[2*nbvert+1] = 0;
	    trackvertices[3*nbvert]   = x3;
	    trackvertices[3*nbvert+1] = y3;
	    trackvertices[3*nbvert+2] = z3 + PIT_HEIGHT - PIT_TOP;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = pits->len;
	    tracktexcoord[2*nbvert+1] = 0;
	    trackvertices[3*nbvert]   = x2;
	    trackvertices[3*nbvert+1] = y2;
	    trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT - PIT_TOP;
	    trackindices[nbvert]      = nbvert++;

	    dx = PIT_TOP * normvec.x;
	    dy = PIT_TOP * normvec.y;

	    tracktexcoord[2*nbvert]   = 0;
	    tracktexcoord[2*nbvert+1] = PIT_TOP;
	    trackvertices[3*nbvert]   = x3 + dx;
	    trackvertices[3*nbvert+1] = y3 + dy;
	    trackvertices[3*nbvert+2] = z3 + PIT_HEIGHT - PIT_TOP;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = pits->len;
	    tracktexcoord[2*nbvert+1] = PIT_TOP;
	    trackvertices[3*nbvert]   = x2 + dx;
	    trackvertices[3*nbvert+1] = y2 + dy;
	    trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT - PIT_TOP;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = 0;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP;
	    trackvertices[3*nbvert]   = x3 + dx;
	    trackvertices[3*nbvert+1] = y3 + dy;
	    trackvertices[3*nbvert+2] = z3 + PIT_HEIGHT;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = pits->len;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP;
	    trackvertices[3*nbvert]   = x2 + dx;
	    trackvertices[3*nbvert+1] = y2 + dy;
	    trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT;
	    trackindices[nbvert]      = nbvert++;

	    dx = - PIT_DEEP * normvec.x;
	    dy = - PIT_DEEP * normvec.y;

	    tracktexcoord[2*nbvert]   = 0;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP + PIT_DEEP;
	    trackvertices[3*nbvert]   = x3 + dx;
	    trackvertices[3*nbvert+1] = y3 + dy;
	    trackvertices[3*nbvert+2] = z3 + PIT_HEIGHT;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = pits->len;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP + PIT_DEEP;
	    trackvertices[3*nbvert]   = x2 + dx;
	    trackvertices[3*nbvert+1] = y2 + dy;
	    trackvertices[3*nbvert+2] = z2 + PIT_HEIGHT;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = 0;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP + PIT_DEEP + PIT_HEIGHT;
	    trackvertices[3*nbvert]   = x3 + dx;
	    trackvertices[3*nbvert+1] = y3 + dy;
	    trackvertices[3*nbvert+2] = z3;
	    trackindices[nbvert]      = nbvert++;

	    tracktexcoord[2*nbvert]   = pits->len;
	    tracktexcoord[2*nbvert+1] = 2 * PIT_TOP + PIT_DEEP + PIT_HEIGHT;
	    trackvertices[3*nbvert]   = x2 + dx;
	    trackvertices[3*nbvert+1] = y2 + dy;
	    trackvertices[3*nbvert+2] = z2;
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

    }

    CLOSEDISPLIST();
    

    printf("=== Indices really used = %d\n", nbvert);
    
    return 0;
}

int NbMainTrackObjects;
FILE *save_fd;

static int
StartOutputFile(char *filename)
{
    save_fd = fopen(filename, "wa");

    if (save_fd == NULL) {
	    GfOut("Failed to open '%s' for writing", filename);
	    return -1;
    }

    fprintf(save_fd, "AC3Db\n");
    fprintf(save_fd, "MATERIAL \"\" rgb 1 1 1  amb 1 1 1  emis 0 0 0  spec 0 0 0  shi 0  trans 0\n");
    
    fprintf(save_fd, "OBJECT world\n");
    fprintf(save_fd, "kids 1\n");
    fprintf(save_fd, "OBJECT group\n");
    fprintf(save_fd, "name \"track\"\n");
    fprintf(save_fd, "kids %d\n", NbMainTrackObjects);

    return 0;
}

void
EndOutputFile(void)
{
    fclose(save_fd);
}


void
CountMainTrack(void)
{
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
}



static void
saveObject(int nb, int start, char *texture, char *name, int surfType)
{
    int	i, index;
    
    fprintf(save_fd, "OBJECT poly\n");
    fprintf(save_fd, "name \"%s\"\n", name);    
    fprintf(save_fd, "texture \"%s\"\n", texture);
    fprintf(save_fd, "numvert %d\n", nb);

    for (i = 0; i < nb; i++) {
	index = 3 * (start + i);
	fprintf(save_fd, "%f %f %f\n", trackvertices[index], trackvertices[index+2], -trackvertices[index+1]);
    }

    fprintf(save_fd, "numsurf %d\n", nb - 2);
    if (surfType) {
	fprintf(save_fd, "SURF 0x10\n");
    } else {
	fprintf(save_fd, "SURF 0x30\n");
    }
    fprintf(save_fd, "mat 0\n");
    fprintf(save_fd, "refs 3\n");
    fprintf(save_fd, "%d %f %f\n", 0, tracktexcoord[2*start], tracktexcoord[2*start+1]);
    fprintf(save_fd, "%d %f %f\n", 1, tracktexcoord[2*(start+1)], tracktexcoord[2*(start+1)+1]);
    fprintf(save_fd, "%d %f %f\n", 2, tracktexcoord[2*(start+2)], tracktexcoord[2*(start+2)+1]);
   
    /* triangle strip conversion to triangles */
    for (i = 2; i < nb-1; i++) {
	if (surfType) {
	    fprintf(save_fd, "SURF 0x10\n");
	} else {
	    fprintf(save_fd, "SURF 0x30\n");
	}
	fprintf(save_fd, "mat 0\n");
	fprintf(save_fd, "refs 3\n");
	if ((i % 2) == 0) {
	    index = i;
	    fprintf(save_fd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	    index = i - 1;
	    fprintf(save_fd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	    index = i + 1;
	    fprintf(save_fd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	} else {
	    index = i - 1;
	    fprintf(save_fd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	    index = i;
	    fprintf(save_fd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	    index = i + 1;
	    fprintf(save_fd, "%d %f %f\n", index, tracktexcoord[2*(start+index)], tracktexcoord[2*(start+index)+1]);
	}
    }
    fprintf(save_fd, "kids 0\n");
}


static void
SaveMainTrack(void)
{
    tDispElt	*aDispElt;
    char	buf[256];

    if (DispList != NULL) {
	aDispElt = DispList;
	do {
	    aDispElt = aDispElt->next;
	    if (aDispElt->nb != 0) {
		sprintf(buf, "%s %d", aDispElt->name, aDispElt->id);
		saveObject(aDispElt->nb, aDispElt->start, aDispElt->texture->name, buf, aDispElt->surfType);
	    }
	} while (aDispElt != DispList);
    }
}

/** Generate the terrain mesh.
    @param	rightside	1 if use the right side
				0 if use the left side
    @param	reverse		1 if reverse the points order
				0 if keep the track order
    @param	exterior	1 if it is the exterior
				0 if it is the interior
    @param	
    @return	None.
*/
static void
GenerateMesh(tTrack *track, int rightside, int reverse, int exterior)
{
    int		startNeeded;
    int		i, j, nbvert;
    tdble	ts, step, anz;
    char	buf[256];
    tTrackSeg 	*seg;
    tTrackSeg 	*mseg;
    tTrkLocPos 	trkpos;
    tdble	x, y;
    tdble 	radiusr, radiusl;
    struct nod	*point2;
    int		nb_relief_vtx, nb_relief_seg;

    CountRelief(1 - exterior, &nb_relief_vtx, &nb_relief_seg);
    
    /* Estimation of the number of points */
    point = (struct nod*)calloc((int)(track->length) + nb_relief_vtx, sizeof(struct nod));
    
    if (rightside) {
	nbvert = 0;

	if (exterior && !reverse) {
	    point[nbvert].x = -Margin;
	    point[nbvert].y = -Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = track->max.x + Margin;
	    point[nbvert].y = -Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = track->max.x + Margin;
	    point[nbvert].y = track->max.y + Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = -Margin;
	    point[nbvert].y = track->max.y + Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	}

	/* Right side */
	startNeeded = 1;
	for (i = 0, mseg = track->seg->next; i < track->nseg; i++, mseg = mseg->next) {
	    if (mseg->rside != NULL) {
		seg = mseg->rside;
	    } else {
		seg = mseg;
	    }
	    if (startNeeded) {
		point[nbvert].x = seg->vertex[TR_SR].x;
		point[nbvert].y = seg->vertex[TR_SR].y;
		point[nbvert].z = seg->vertex[TR_SR].z;
		point[nbvert].F = GridStep;
		point[nbvert].mark = i+1;
		nbvert++;
	    }
	    switch (seg->type) {
	    case TR_STR:
		ts = LMAX;
		trkpos.seg = seg;
		while (ts < seg->length) {
		    trkpos.toStart = ts;
		    trkpos.toRight = 0;
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    point[nbvert].x = x;
		    point[nbvert].y = y;
		    point[nbvert].z = RtTrackHeightL(&trkpos);
		    point[nbvert].F = GridStep;
		    point[nbvert].mark = i+1;
		    nbvert++;
		    ts += LMAX;
		}
		break;
	    case TR_LFT:
		step = LMAX / (mseg->radiusr);
		anz = seg->angle[TR_ZS] + step;
		ts = step;
		radiusr = seg->radiusr;
		trkpos.seg = seg;
		trkpos.toRight = 0;
		while (anz < seg->angle[TR_ZE]) {
		    trkpos.toStart = ts;
		    /* right */
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    point[nbvert].x = x;
		    point[nbvert].y = y;
		    point[nbvert].z = RtTrackHeightL(&trkpos);
		    point[nbvert].F = GridStep;
		    point[nbvert].mark = i+1;
		    nbvert++;
		    ts += step;
		    anz += step;
		}
		break;
	    case TR_RGT:
		step = LMAX / (mseg->radiusl);
		anz = seg->angle[TR_ZS] - step;
		ts = step;
		radiusr = seg->radiusr;
		trkpos.seg = seg;
		trkpos.toRight = 0;
		while (anz > seg->angle[TR_ZE]) {
		    trkpos.toStart = ts;
		    /* right */
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    point[nbvert].x = x;
		    point[nbvert].y = y;
		    point[nbvert].z = RtTrackHeightL(&trkpos);
		    point[nbvert].F = GridStep;
		    point[nbvert].mark = i+1;
		    nbvert++;
		    ts += step;
		    anz -= step;
		}
		break;
	    }
	    if (i != (track->nseg - 1)) {
		point[nbvert].x = seg->vertex[TR_ER].x;
		point[nbvert].y = seg->vertex[TR_ER].y;
		point[nbvert].z = seg->vertex[TR_ER].z;
		point[nbvert].F = GridStep;
		point[nbvert].mark = i+1;
		nbvert++;
		startNeeded = 0;
	    }
	}

	if (exterior && reverse) {
	    point[nbvert].x = -Margin;
	    point[nbvert].y = track->max.y + Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = track->max.x + Margin;
	    point[nbvert].y = track->max.y + Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = track->max.x + Margin;
	    point[nbvert].y = -Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = -Margin;
	    point[nbvert].y = -Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	}

    } else {
	nbvert = 0;

	if (exterior && !reverse) {
	    point[nbvert].x = -Margin;
	    point[nbvert].y = -Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = track->max.x + Margin;
	    point[nbvert].y = -Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = track->max.x + Margin;
	    point[nbvert].y = track->max.y + Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = -Margin;
	    point[nbvert].y = track->max.y + Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	}

	/* Left Side */
	startNeeded = 1;
	for (i = 0, mseg = track->seg->next; i < track->nseg; i++, mseg = mseg->next) {
	    if (mseg->lside) {
		seg = mseg->lside;
	    } else {
		seg = mseg;
	    }
	    if (startNeeded) {
		point[nbvert].x = seg->vertex[TR_SL].x;
		point[nbvert].y = seg->vertex[TR_SL].y;
		point[nbvert].z = seg->vertex[TR_SL].z;
		point[nbvert].F = GridStep;
		point[nbvert].mark = i+1;
		nbvert++;
	    }
	    
	    switch (seg->type) {
	    case TR_STR:
		ts = LMAX;
		trkpos.seg = seg;
		while (ts < seg->length) {
		    trkpos.toStart = ts;
		    trkpos.toRight = RtTrackGetWidth(seg, ts);
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    point[nbvert].x = x;
		    point[nbvert].y = y;
		    point[nbvert].z = RtTrackHeightL(&trkpos);
		    point[nbvert].F = GridStep;
		    point[nbvert].mark = i+1;
		    nbvert++;
		    ts += LMAX;
		}
		break;
	    case TR_LFT:
		step = LMAX / (mseg->radiusr);
		anz = seg->angle[TR_ZS] + step;
		ts = step;
		radiusl = seg->radiusl;
		trkpos.seg = seg;
		while (anz < seg->angle[TR_ZE]) {
		    trkpos.toStart = ts;
		    trkpos.toRight = RtTrackGetWidth(seg, ts);
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    /* left */
		    point[nbvert].x = x;
		    point[nbvert].y = y;
		    point[nbvert].z = RtTrackHeightL(&trkpos);
		    point[nbvert].F = GridStep;
		    point[nbvert].mark = i+1;
		    nbvert++;
		    ts += step;
		    anz += step;
		}
		break;
	    case TR_RGT:
		step = LMAX / (mseg->radiusl);
		anz = seg->angle[TR_ZS] - step;
		ts = step;
		radiusl = seg->radiusl;
		trkpos.seg = seg;
		while (anz > seg->angle[TR_ZE]) {
		    trkpos.toStart = ts;
		    trkpos.toRight = RtTrackGetWidth(seg, ts);
		    RtTrackLocal2Global(&trkpos, &x, &y, TR_TORIGHT);
		    /* left */
		    point[nbvert].x = x;
		    point[nbvert].y = y;
		    point[nbvert].z = RtTrackHeightL(&trkpos);
		    point[nbvert].F = GridStep;
		    point[nbvert].mark = i+1;
		    nbvert++;
		    ts += step;
		    anz -= step;
		}
		break;
	    }
	    if (i != (track->nseg - 1)) {
		point[nbvert].x = seg->vertex[TR_EL].x;
		point[nbvert].y = seg->vertex[TR_EL].y;
		point[nbvert].z = seg->vertex[TR_EL].z;
		point[nbvert].F = GridStep;
		point[nbvert].mark = i+1;
		nbvert++;
		startNeeded = 0;
	    }
	}

	if (exterior && reverse) {
	    point[nbvert].x = -Margin;
	    point[nbvert].y = track->max.y + Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = track->max.x + Margin;
	    point[nbvert].y = track->max.y + Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = track->max.x + Margin;
	    point[nbvert].y = -Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	    point[nbvert].x = -Margin;
	    point[nbvert].y = -Margin;
	    point[nbvert].z = ExtHeight;
	    point[nbvert].F = GridStep;
	    point[nbvert].mark = 100000;
	    nbvert++;
	}
    }

    
    Nc = nbvert;
    segment = (struct seg *)calloc(Nc + 1 + nb_relief_seg, sizeof(struct seg));
    segment[Nc].n0 = -1;
    segment[Nc].n1 = -1;

    if (reverse){
	    
	/* reverse order */
	point2 = (struct nod*)calloc(Nc + 1 + nb_relief_vtx, sizeof(struct nod));
	for (i = 0; i < Nc; i++) {
	    memcpy(&(point2[i]), &(point[Nc-i-1]), sizeof(struct nod));
	}
	free(point);
	point = point2;
    }
    if (exterior) {
	segment[0].n0 = 0;
	segment[0].n1 = 1;
	segment[0].mark = 1;
	segment[1].n0 = 1;
	segment[1].n1 = 2;
	segment[1].mark = 1;
	segment[2].n0 = 2;
	segment[2].n1 = 3;
	segment[2].mark = 1;
	segment[3].n0 = 3;
	segment[3].n1 = 0;
	segment[3].mark = 1;

	i = 0;
	j = 0;
	do {
	    segment[j+4].n0 = i+4;
	    i = (i + 1) % (Nc - 4);
	    segment[j+4].n1 = i+4;
	    segment[j+4].mark = 2;
	    j++;
	} while (i != 0);
	
    } else {
	i = 0;
	j = 0;
	do {
	    segment[j].n0 = i;
	    i = (i + 1) % Nc;
	    segment[j].n1 = i;
	    segment[j].mark = 1;
	    j++;
	} while (i != 0);
    }
    sprintf(buf, "%s", OutputFileName);
    if (exterior) {
	char *s;
	s = strrchr(buf, '.');
	sprintf(s, "_ext.ac");

	Fl = Nc;
	GenRelief(0);
    } else {
	char *s;
	s = strrchr(buf, '.');
	sprintf(s, "_in.ac");

	Fl = Nc;
	GenRelief(1);
    }
    GfOut("Output filename: %s", buf);
    generate_mesh(buf);
}

int
GetFilename(char *filename, char *filepath, char *buf)
{
    char	*c1, *c2;
    int		found = 0;
    int		lg;
    
    if (filepath) {
	c1 = filepath;
	c2 = c1;
	while ((!found) && (c2 != NULL)) {
	    c2 = strchr(c1, ';');
	    if (c2 == NULL) {
		sprintf(buf, "%s/%s", c1, filename);
	    } else {
		lg = c2 - c1;
		strncpy(buf, c1, lg);
		buf[lg] = '/';
		strcpy(buf + lg + 1, filename);
	    }
	    if (ulFileExists(buf)) {
		found = 1;
	    }
	    c1 = c2 + 1;
	}
    } else {
	strcpy(buf, filename);
	if (ulFileExists(buf)) {
	    found = 1;
	}
    }
    if (!found) {
	printf("File %s not found\n", filename);
	printf("File Path was %s\n", filepath);
	return 0;
    }

    return 1;
}


void
GenerateTrack(char *trackname)
{
    tTrack	*track;
    void	*hndl;
    char	outfile[256];
    char	reliefFile[256];
    char	buf[256];

    if (LoadTrackModule()) {
	GfOut("Track Module Loading Failure.");
	return;
    }
    track = TrackItf.trkBuildEx(trackname);

    hndl = GfParmReadFile(trackname, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    OutputFileName = GfParmGetStr(hndl, TRK_SECT_GRAPH, TRK_ATT_3DDESC, NULL);
    if (OutputFileName == 0) {
	GfOut("Missing \"%s\" parameter in section \"%s\" of trackfile", TRK_ATT_3DDESC, TRK_SECT_GRAPH);
	return;
    }
    sprintf(outfile, "tracks/%s/%s", track->internalname, OutputFileName);
    GfOut("Output file: %s", outfile);
    OutputFileName = strdup(outfile);
    
    TrackStep = GfParmGetNum(hndl, TRK_SECT_TERRAIN, TRK_ATT_TSTEP, NULL, TrackStep);
    GfOut("Track step: %.2f", TrackStep);
    Margin    = GfParmGetNum(hndl, TRK_SECT_TERRAIN, TRK_ATT_BMARGIN, NULL, Margin);
    GridStep  = GfParmGetNum(hndl, TRK_SECT_TERRAIN, TRK_ATT_BSTEP, NULL, GridStep);
    ExtHeight = GfParmGetNum(hndl, TRK_SECT_TERRAIN, TRK_ATT_BHEIGHT, NULL, ExtHeight);
    GfOut("Border margin: %.2f    step: %.2f    height: %.2f", Margin, GridStep, ExtHeight);
    
    if (strncmp(TRK_VAL_CLOCK,
		GfParmGetStr(hndl, TRK_SECT_TERRAIN, TRK_ATT_ORIENT, TRK_VAL_CLOCK),
		strlen(TRK_VAL_CLOCK)) == 0) {
	Orientation = CLOCKWISE;
	GfOut("Orientation: clockwise");
    } else {
	Orientation = ANTICLOCKWISE;
	GfOut("Orientation: counter-clockwise");
    }

    ReliefFileName = GfParmGetStr(hndl, TRK_SECT_TERRAIN, TRK_ATT_RELIEF, NULL);
    if (ReliefFileName) {
	sprintf(buf, "tracks/%s;.", track->internalname);
	if (GetFilename(ReliefFileName, buf, reliefFile)) {
	    GfOut("Relief file: %s", reliefFile);
	    LoadRelief(reliefFile);
	}
    }
    
	
    InitScene(track);

    CountMainTrack();
    StartOutputFile(outfile);
    SaveMainTrack();

    EndOutputFile();

    if (Orientation == CLOCKWISE) {
	GenerateMesh(track, 1 /* right */, 1 /* reverse */, 0 /* interior */);
	GenerateMesh(track, 0 /* left */,  0 /* normal */,  1 /* exterior */);
    } else {
	GenerateMesh(track, 0 /* left */,  0 /* normal */,  0 /* interior */);
	GenerateMesh(track, 1 /* right */, 1 /* reverse */, 1 /* exterior */);
    }
}


