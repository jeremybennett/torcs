/***************************************************************************

    file        : raceresults.cpp
    created     : Thu Jan  2 12:43:10 CET 2003
    copyright   : (C) 2002 by Eric Espié                        
    email       : eric.espie@torcs.org   
    version     : $Id$                                  

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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <tgf.h>
#include <robot.h>
#include <raceman.h>
#include <racemantools.h>
#include <robottools.h>

#include "racemain.h"
#include "racegl.h"
#include "raceinit.h"
#include "raceengine.h"

#include "raceresults.h"

static char buf[1024];
static char path[1024];

void
ReInitResults(void)
{
    int		nCars;
    int		i;
    struct tm	*stm;
    time_t	t;
    void	*results;
    void	*params = ReInfo->params;

    t = time(NULL);
    stm = localtime(&t);
    sprintf(buf, "results/results-%4d-%02d-%02d-%02d-%02d.xml",
	    stm->tm_year+1900,
	    stm->tm_mon+1,
	    stm->tm_mday,
	    stm->tm_hour,
	    stm->tm_min);

    ReInfo->results = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    results = ReInfo->results;
    GfParmSetStr(results, RE_SECT_HEADER, RE_ATTR_TRACK, ReInfo->track->name);
    GfParmSetNum(results, RE_SECT_HEADER, RE_ATTR_DATE, NULL, (tdble)t);

    nCars = GfParmGetEltNb(params, RM_SECT_DRIVERS);
    for (i = 1; i < nCars + 1; i++) {
	sprintf(path, "%s/%d", RM_SECT_DRIVERS, i);
	GfParmSetStr(results, path, RE_ATTR_DLL_NAME, GfParmGetStr(params, path, RM_ATTR_MODULE, ""));
	GfParmSetNum(results, path, RE_ATTR_INDEX, NULL, GfParmGetNum(params, path, RM_ATTR_IDX, (char*)NULL, 0));
    }
}

void
ReStoreRaceResults(char *race)
{
    int		i;
    tCarElt	*car;
    tSituation 	*s = ReInfo->s;
    void	*results = ReInfo->results;

    /* Store the number of laps of the race */
    if (ReInfo->s->_raceType == RM_TYPE_RACE) {
	car = s->cars[0];
	if (car->_laps > s->_totLaps) car->_laps = s->_totLaps + 1;
	sprintf(path, "%s/%s", RE_SECT_RESULTS, race);
	GfParmListClean(results, path);
	GfParmSetNum(results, path, RE_ATTR_LAPS, NULL, car->_laps - 1);
    
	for (i = 0; i < s->_ncars; i++) {
	    sprintf(path, "%s/%s/%s/%d", RE_SECT_RESULTS, race, RE_SECT_RANK, i + 1);
	    car = s->cars[i];
	    if (car->_laps > s->_totLaps) car->_laps = s->_totLaps + 1;

	    GfParmSetStr(results, path, RE_ATTR_NAME, car->_name);
	    GfParmSetNum(results, path, RE_ATTR_INDEX, NULL, car->index);

	    GfParmSetNum(results, path, RE_ATTR_LAPS, NULL, car->_laps - 1);
	    GfParmSetNum(results, path, RE_ATTR_TIME, NULL, car->_curTime);
	    GfParmSetNum(results, path, RE_ATTR_BEST_LAP_TIME, NULL, car->_bestLapTime);
	    GfParmSetNum(results, path, RE_ATTR_TOP_SPEED, NULL, car->_topSpeed);
	    GfParmSetNum(results, path, RE_ATTR_DAMMAGES, NULL, car->_dammage);
	    GfParmSetNum(results, path, RE_ATTR_NB_PIT_STOPS, NULL, car->_nbPitStops);
	}
    } else if (ReInfo->s->_raceType == RM_TYPE_PRACTICE) {
	car = s->cars[0];
	sprintf(path, "%s/%s", RE_SECT_RESULTS, race);
	GfParmSetStr(results, path, RM_ATTR_DRVNAME, car->_name);
    }
}

void
ReSavePracticeLap(tCarElt *car)
{
    void	*results = ReInfo->results;
    tReCarInfo	*info = &(ReInfo->_reCarInfo[car->index]);

    sprintf(path, "%s/%s/%d", RE_SECT_RESULTS, ReInfo->_reRaceName, car->_laps - 1);
    GfParmSetNum(results, path, RE_ATTR_TIME, NULL, car->_lastLapTime);
    GfParmSetNum(results, path, RE_ATTR_BEST_LAP_TIME, NULL, car->_bestLapTime);
    GfParmSetNum(results, path, RE_ATTR_TOP_SPEED, NULL, info->topSpd);
    GfParmSetNum(results, path, RE_ATTR_BOT_SPEED, NULL, info->botSpd);
    GfParmSetNum(results, path, RE_ATTR_DAMMAGES, NULL, car->_dammage);
    
}

int
ReDisplayResults(void)
{
    void	*params = ReInfo->params;

    if ((!strcmp(GfParmGetStr(params, ReInfo->_reRaceName, RM_ATTR_DISPRES, RM_VAL_YES), RM_VAL_YES)) ||
	(ReInfo->_displayMode == RM_DISP_MODE_NORMAL)) {
	RmShowResults(ReInfo->_reGameScreen, ReInfo);
    } else {
	ReResShowCont();
    }

    return RM_ASYNC | RM_NEXT_STEP;
}

