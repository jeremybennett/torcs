/***************************************************************************
                       racemantools.cpp -- Tools for race managers                               
                             -------------------                                         
    created              : Mon Aug 16 21:47:17 CEST 1999
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

/** @file
    		This is a set of tools useful for race managers.
    @ingroup	racemantools
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <osspec.h>
#include <racemantools.h>
#include <robottools.h>
#include <robot.h>

static char buf[256];


/** Dump the track segments on screen
    @param	track	track to dump
    @param	verbose	if set to 1 all the segments are described (long)
    @ingroup	racemantools
 */
void
RmDumpTrack(tTrack *track, int verbose)
{
    char	buf[256];
    int		i;
    tTrackSeg	*seg;
#ifdef DEBUG
    char	*stype[4] = { "", "RGT", "LFT", "STR" }; 
#endif

    RmLoadingScreenSetText("Loading Track Geometry...");
    sprintf(buf, ">>> Track Name    %s", track->name);
    RmLoadingScreenSetText(buf);
    sprintf(buf, ">>> Track Author  %s", track->author);
    RmLoadingScreenSetText(buf);
    sprintf(buf, ">>> Track Length  %.2f m", track->length);
    RmLoadingScreenSetText(buf);
    sprintf(buf, ">>> Track Width   %.2f m", track->width);
    RmLoadingScreenSetText(buf);

    GfOut("++++++++++++ Track ++++++++++++\n");
    GfOut("name     = %s\n", track->name);
    GfOut("author   = %s\n", track->author);
    GfOut("filename = %s\n", track->filename);
    GfOut("nseg     = %d\n", track->nseg);
    GfOut("version  = %d\n", track->version);
    GfOut("length   = %f\n", track->length);
    GfOut("width    = %f\n", track->width);
    GfOut("XSize    = %f\n", track->max.x);
    GfOut("YSize    = %f\n", track->max.y);
    GfOut("ZSize    = %f\n", track->max.z);
    switch (track->pits.type) {
    case TR_PIT_NONE:
	GfOut("Pits     = none\n");
	break;
    case TR_PIT_ON_TRACK_SIDE:
	GfOut("Pits     = present on track side\n");
	break;
    case TR_PIT_ON_SEPARATE_PATH:
	GfOut("Pits     = present on separate path\n");
	break;
    }
    if (verbose) {
	for (i = 0, seg = track->seg->next; i < track->nseg; i++, seg = seg->next) {
	    GfOut("	segment %d -------------- \n", seg->id);
#ifdef DEBUG
	    GfOut("        type    %s\n", stype[seg->type]);
#endif
	    GfOut("        length  %f\n", seg->length);
	    GfOut("	radius  %f\n", seg->radius);
	    GfOut("	arc	%f   Zs %f   Ze %f   Zcs %f\n", RAD2DEG(seg->arc), 
		   RAD2DEG(seg->angle[TR_ZS]), 
		   RAD2DEG(seg->angle[TR_ZE]), 
		   RAD2DEG(seg->angle[TR_CS]));
	    GfOut("	Za	%f\n", RAD2DEG(seg->angle[TR_ZS]));
	    GfOut("	vertices: %-8.8f %-8.8f %-8.8f ++++ ",
		   seg->vertex[TR_SR].x,
		   seg->vertex[TR_SR].y,
		   seg->vertex[TR_SR].z);
	    GfOut("%-8.8f %-8.8f %-8.8f\n",
		   seg->vertex[TR_SL].x,
		   seg->vertex[TR_SL].y,
		   seg->vertex[TR_SL].z);
	    GfOut("	vertices: %-8.8f %-8.8f %-8.8f ++++ ",
		   seg->vertex[TR_ER].x,
		   seg->vertex[TR_ER].y,
		   seg->vertex[TR_ER].z);
	    GfOut("%-8.8f %-8.8f %-8.8f\n",
		   seg->vertex[TR_EL].x,
		   seg->vertex[TR_EL].y,
		   seg->vertex[TR_EL].z);
	    GfOut("	prev    %d\n", seg->prev->id);
	    GfOut("	next    %d\n", seg->next->id);
	}
	GfOut("From Last To First\n");
	GfOut("Dx = %-8.8f  Dy = %-8.8f Dz = %-8.8f\n",
	       track->seg->next->vertex[TR_SR].x - track->seg->vertex[TR_ER].x,
	       track->seg->next->vertex[TR_SR].y - track->seg->vertex[TR_ER].y,
	       track->seg->next->vertex[TR_SR].z - track->seg->vertex[TR_ER].z);
	
    }
}


/** Initialize the track for a race manager.
    @param	raceInfo	the tRmInfo structure with track, simItf already stored.
    @return	<tt>0 ... </tt>Ok
		<br><tt>-1 .. </tt>Error
    @ingroup	racemantools
*/
int
RmInitTrack(tRmInfo *raceInfo)
{
    char	*trackName;
    char	*catName;
    
    trackName = GfParmGetStr(raceInfo->params, "Race/Track", "name", "");
    catName = GfParmGetStr(raceInfo->params, "Race/Track", "category", "");

    sprintf(buf, "Loading Track %s...", trackName);
    RmLoadingScreenSetText(buf);
    sprintf(buf, "tracks/%s/%s/%s.%s", catName, trackName, trackName, TRKEXT);
    raceInfo->track = raceInfo->_reTrackItf.trkBuild(buf);
    RmDumpTrack(raceInfo->track, 0);

    return 0;
}

