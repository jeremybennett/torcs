/***************************************************************************

    file                 : relief.cpp
    created              : Tue Mar  6 23:15:19 CET 2001
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
#else
#include <windows.h>
#endif
#include <math.h>
#include <plib/ssg.h>
#include <GL/glut.h>

#include <tgf.h>
#include <track.h>
#include "trackgen.h"
#include "easymesh.h"

#include "relief.h"

tRingListHead	InteriorList;
tRingListHead	ExteriorList;

static tdble	GridStep;

typedef struct 
{
    tRingList	lnk;
    ssgBranch	*branch;
} tLine;

ssgEntity	*Root = NULL;

/*
 * Read the faces from AC3D file
 * separate between interior and exterior lines
 */
static ssgBranch *
hookNode(char *s)
{
    tLine	*line;
    
    line = (tLine*)calloc(1, sizeof(tLine));
    line->branch = new ssgBranch();

    if (strncmp(s, "interior", 8) == 0) {
	GfRlstAddLast(&InteriorList, (tRingList *)line);
    } else {
	GfRlstAddLast(&ExteriorList, (tRingList *)line);
    }
    return line->branch;
}


/*
  Load a simple database
*/
void
LoadRelief(void *TrackHandle, char *reliefFile)
{
    GfRlstInit(&InteriorList);
    GfRlstInit(&ExteriorList);
    
    GridStep  = GfParmGetNum(TrackHandle, TRK_SECT_TERRAIN, TRK_ATT_BSTEP, NULL, GridStep);

    ssgLoaderOptions *loaderopt = new ssgLoaderOptions();
 
    loaderopt->setCreateBranchCallback(hookNode);

    printf("\nLoading relief file %s\n", reliefFile);
    
    Root = ssgLoadAC(reliefFile, loaderopt);
}

static void
countRec(ssgEntity *e, int *nb_vert, int *nb_seg)
{
    if (e->isAKindOf(_SSG_TYPE_BRANCH)) {
	ssgBranch *br = (ssgBranch *)e;
	
	for (int i = 0; i < br->getNumKids(); i++) {
	    countRec(br->getKid(i), nb_vert, nb_seg);
	}
    } else {
	if (e->isAKindOf(_SSG_TYPE_VTXTABLE)) {
	    ssgVtxTable *vt = (ssgVtxTable *)e;
	    *nb_vert += vt->getNumVertices();
	    *nb_seg  += vt->getNumLines();
	}
    }
}

void
CountRelief(int interior, int *nb_vert, int *nb_seg)
{
    tLine		*curLine;
    tRingListHead	*curHead;
    
    *nb_vert = *nb_seg = 0;
    
    if (Root == NULL) {
	return;
    }

    if (interior) {
	curHead = &InteriorList;
    } else {
	curHead = &ExteriorList;
    }
    
    curLine = (tLine*)GfRlstGetFirst(curHead);
    while (curLine != NULL) {
	ssgBranch *br = curLine->branch->getParent(0);
	ssgBranch *br2 = new ssgBranch();
	
	br2->addKid(br);
	ssgFlatten(br);
	curLine->branch = br2;
	
	countRec((ssgEntity *)curLine->branch, nb_vert, nb_seg);

	curLine = (tLine*)GfRlstGetNext(curHead, (tRingList*)curLine);
    }
}

static void
genRec(ssgEntity *e)
{
    if (e->isAKindOf(_SSG_TYPE_BRANCH)) {
	ssgBranch *br = (ssgBranch *)e;
	
	for (int i = 0; i < br->getNumKids(); i++) {
	    genRec(br->getKid(i));
	}
    } else {
	if (e->isAKindOf(_SSG_TYPE_VTXTABLE)) {
	    ssgVtxTable *vt = (ssgVtxTable *)e;
	    int nv = vt->getNumVertices();
	    int nl = vt->getNumLines();
	    int sv = Nc;
	    int i;

	    for (i = 0; i < nv; i++) {
		float *vtx = vt->getVertex(i);
		point[Nc].x = vtx[0];
		point[Nc].y = vtx[1];
		point[Nc].z = vtx[2];
		point[Nc].F = GridStep;
		point[Nc].mark = 100000;
		Nc++;
	    }

	    for (i = 0; i < nl; i++) {
		short vv0, vv1;

		vt->getLine(i, &vv0, &vv1);

		segment[Fl].n0 = vv0 + sv;
		segment[Fl].n1 = vv1 + sv;
		segment[Fl].mark = 100000;
		
		Fl++;
	    }
	}
    }
}



void
GenRelief(int interior)
{
    tLine		*curLine;
    tRingListHead	*curHead;
    
    
    if (Root == NULL) {
	return;
    }

    if (interior) {
	curHead = &InteriorList;
    } else {
	curHead = &ExteriorList;
    }
    
    curLine = (tLine*)GfRlstGetFirst(curHead);
    while (curLine != NULL) {
	genRec((ssgEntity *)curLine->branch);

	curLine = (tLine*)GfRlstGetNext(curHead, (tRingList*)curLine);
    }
}

