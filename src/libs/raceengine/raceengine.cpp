/***************************************************************************

    file        : raceengine.cpp
    created     : Sat Nov 23 09:05:23 CET 2002
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
#include <tgfclient.h>
#include <robot.h>
#include <raceman.h>
#include <racemantools.h>
#include <robottools.h>

#include "racemain.h"
#include "racegl.h"
#include "raceinit.h"
#include "raceresults.h"

#include "raceengine.h"

static char	buf[1024];
static double	msgDisp;
static double	bigMsgDisp;

tRmInfo	*ReInfo = 0;



/* Compute Pit stop time */
static void
ReUpdtPitTime(tCarElt *car)
{
    tSituation	*s = ReInfo->s;
    tReCarInfo	*info = &(ReInfo->_reCarInfo[car->index]);

    info->totalPitTime = 2.0 + fabs(car->pitcmd.fuel) / 8.0 + (tdble)(fabs(car->pitcmd.repair)) * 0.007;
    car->_scheduledEventTime = s->currentTime + info->totalPitTime;
    ReInfo->_reSimItf.reconfig(car);    
}

/* Return from interactive pit information */
static void
ReUpdtPitCmd(void *pvcar)
{
    tCarElt *car = (tCarElt*)pvcar;
    
    ReUpdtPitTime(car);
    //ReStart(); /* resynchro */
    GfuiScreenActivate(ReInfo->_reGameScreen);
}

static void
ReRaceMsgUpdate(void)
{
    if (ReInfo->_reCurTime > msgDisp) {
	ReSetRaceMsg("");
    }
    if (ReInfo->_reCurTime > bigMsgDisp) {
	ReSetRaceBigMsg("");
    }
}

static void
ReRaceMsgSet(char *msg, double life)
{
    ReSetRaceMsg(msg);
    msgDisp = ReInfo->_reCurTime + life;
}


static void
ReRaceBigMsgSet(char *msg, double life)
{
    ReSetRaceBigMsg(msg);
    bigMsgDisp = ReInfo->_reCurTime + life;
}


static void
ReManage(tCarElt *car)
{
    int		i, pitok;
    tTrackSeg	*sseg;
    tdble	wseg;
    static float color[] = {0.0, 0.0, 1.0, 1.0};
    tSituation	*s = ReInfo->s;

    tReCarInfo *info = &(ReInfo->_reCarInfo[car->index]);

    if (car->_speed_x > car->_topSpeed) car->_topSpeed = car->_speed_x;

    /* For practice and qualif */
    if (car->_speed_x > info->topSpd) info->topSpd = car->_speed_x;
    if (car->_speed_x < info->botSpd) info->botSpd = car->_speed_x;

    /* PIT STOP */
    if (car->ctrl.raceCmd & RM_CMD_PIT_ASKED) {
	car->ctrl.msg[3] = "Can Pit";
	memcpy(car->ctrl.msgColor, color, sizeof(car->ctrl.msgColor));
    }
    
    if (car->_state & RM_CAR_STATE_PIT) {
	car->ctrl.raceCmd &= ~RM_CMD_PIT_ASKED; /* clear the flag */
	if (car->_scheduledEventTime < s->currentTime) {
	    car->_state &= ~RM_CAR_STATE_PIT;
	    sprintf(buf, "%s pit stop %.1fs", car->_name, info->totalPitTime);
	    ReRaceMsgSet(buf, 5);
	} else {
	    car->ctrl.msg[2] = "In Pits";
	    memcpy(car->ctrl.msgColor, color, sizeof(car->ctrl.msgColor));
	    if (car == s->cars[s->current]) {
		sprintf(buf, "%s in pits %.1fs", car->_name, s->currentTime - info->startPitTime);
		ReRaceMsgSet(buf, .1);
	    }
	}
    } else if ((car->_pit) && (car->ctrl.raceCmd & RM_CMD_PIT_ASKED)) {
	tdble lgFromStart = car->_trkPos.seg->lgfromstart;
	
	switch (car->_trkPos.seg->type) {
	case TR_STR:
	    lgFromStart += car->_trkPos.toStart;
	    break;
	default:
	    lgFromStart += car->_trkPos.toStart * car->_trkPos.seg->radius;
	    break;
	}
	if ((lgFromStart > car->_pit->lmin) && (lgFromStart < car->_pit->lmax)) {
	    pitok = 0;
	    if (ReInfo->track->pits.side == TR_RGT) {
		sseg = car->_trkPos.seg->rside;
		wseg = RtTrackGetWidth(sseg, car->_trkPos.toStart);
		if (sseg->rside) {
		    sseg = sseg->rside;
		    wseg += RtTrackGetWidth(sseg, car->_trkPos.toStart);
		}
		if (((car->_trkPos.toRight + wseg) <
		     (ReInfo->track->pits.width - car->_dimension_y / 2.0)) &&
		    (fabs(car->_speed_x) < 1.0) &&
		    (fabs(car->_speed_y) < 1.0)) {
		    pitok = 1;
		}
	    } else {
		sseg = car->_trkPos.seg->lside;
		wseg = RtTrackGetWidth(sseg, car->_trkPos.toStart);
		if (sseg->lside) {
		    sseg = sseg->lside;
		    wseg += RtTrackGetWidth(sseg, car->_trkPos.toStart);
		}
		if (((car->_trkPos.toLeft + wseg) <
		     (ReInfo->track->pits.width - car->_dimension_y / 2.0)) &&
		    (fabs(car->_speed_x) < 1.0) &&
		    (fabs(car->_speed_y) < 1.0)) {
		    pitok = 1;
		}
	    }
	    if (pitok) {
		car->_state |= RM_CAR_STATE_PIT;
		car->_nbPitStops++;
		info->startPitTime = s->currentTime;
		sprintf(buf, "%s in pits", car->_name);
		ReRaceMsgSet(buf, 5);
		if (car->robot->rbPitCmd(car->robot->index, car, s) == ROB_PIT_MENU) {
		    /* the pit cmd is modified by menu */
		    ReStop();
		    RmPitMenuStart(car, (void*)car, ReUpdtPitCmd);
		} else {
		    ReUpdtPitTime(car);
		}
	    }
	}
    }
    
    /* Start Line Crossing */
    if (info->prevTrkPos.seg != car->_trkPos.seg) {
	if ((info->prevTrkPos.seg->raceInfo & TR_LAST) && (car->_trkPos.seg->raceInfo & TR_START)) {
	    if (info->lapFlag == 0) {
		if ((car->_state & RM_CAR_STATE_FINISH) == 0) {
		    car->_laps++;
		    car->_remainingLaps--;
		    if (car->_laps > 1) {
			car->_lastLapTime = s->currentTime - info->sTime;
			car->_curTime += car->_lastLapTime;
			if (car->_bestLapTime != 0) {
			    car->_deltaBestLapTime = car->_lastLapTime - car->_bestLapTime;
			}
			if ((car->_lastLapTime < car->_bestLapTime) || (car->_bestLapTime == 0)) {
			    car->_bestLapTime = car->_lastLapTime;
			}
			if (car->_pos != 1) {
			    car->_timeBehindLeader = car->_curTime - s->cars[0]->_curTime;
			    car->_lapsBehindLeader = s->cars[0]->_laps - car->_laps;
			    car->_timeBehindPrev = car->_curTime - s->cars[car->_pos - 2]->_curTime;
			    s->cars[car->_pos - 2]->_timeBeforeNext = car->_timeBehindPrev;
			} else {
			    car->_timeBehindLeader = 0;
			    car->_lapsBehindLeader = 0;
			    car->_timeBehindPrev = 0;
			}
			info->sTime = s->currentTime;
			switch (ReInfo->s->_raceType) {
			case RM_TYPE_PRACTICE:
			    if (ReInfo->_displayMode == RM_DISP_MODE_NONE) {
				ReInfo->_refreshDisplay = 1;
				sprintf(buf,"lap: %02d   time: %s  best: %s  top spd: %.2f    min spd: %.2f    dammage: %d", 
					car->_laps - 1, GfTime2Str(car->_lastLapTime, 0), GfTime2Str(car->_bestLapTime, 0),
					info->topSpd * 3.6, info->botSpd * 3.6, car->_dammage);
				ReResScreenAddText(buf);
			    }
			    /* save the lap result */
			    ReSavePracticeLap(car);
			    break;
			    
			case RM_TYPE_QUALIF:
			    if (ReInfo->_displayMode == RM_DISP_MODE_NONE) {
				ReUpdateQualifCurRes(car);
			    }
			    break;
			}
		    } else {
			if ((ReInfo->_displayMode == RM_DISP_MODE_NONE) && (ReInfo->s->_raceType == RM_TYPE_QUALIF)) {
			    ReUpdateQualifCurRes(car);
			}
		    }

		    info->topSpd = car->_speed_x;
		    info->botSpd = car->_speed_x;
		    if ((car->_remainingLaps < 0) || (s->_raceState == RM_RACE_FINISHING)) {
			car->_state |= RM_CAR_STATE_FINISH;
			s->_raceState = RM_RACE_FINISHING;
			if (ReInfo->s->_raceType == RM_TYPE_RACE) {
			    if (car->_pos == 1) {
				sprintf(buf, "Winner %s", car->_name);
				ReRaceBigMsgSet(buf, 10);
			    } else {
				switch (car->_pos % 10) {
				case 1:
				    sprintf(buf, "%s Finished %dst", car->_name, car->_pos);
				    break;
				case 2:
				    sprintf(buf, "%s Finished %dnd", car->_name, car->_pos);
				    break;
				case 3:
				    sprintf(buf, "%s Finished %drd", car->_name, car->_pos);
				    break;
				default:
				    sprintf(buf, "%s Finished %dth", car->_name, car->_pos);
				    break;
				}
				ReRaceMsgSet(buf, 5);
			    }
			}
		    }
		} else {
		    /* prevent infinite looping of cars around track, allow one lap after finish for the first car */
		    for (i = 0; i < s->_ncars; i++) {
			s->cars[i]->_state |= RM_CAR_STATE_FINISH;
		    }
		    return;
		}
	    } else {
		info->lapFlag--;
	    }
	}
	if ((info->prevTrkPos.seg->raceInfo & TR_START) && (car->_trkPos.seg->raceInfo & TR_LAST)) {
	    /* going backward through the start line */
	    info->lapFlag++;
	}
    }
    info->prevTrkPos = car->_trkPos;
    car->_curLapTime = s->currentTime - info->sTime;
    car->_distFromStartLine = car->_trkPos.seg->lgfromstart +
	(car->_trkPos.seg->type == TR_STR ? car->_trkPos.toStart : car->_trkPos.toStart * car->_trkPos.seg->radius);
    car->_distRaced = (car->_laps - 1) * ReInfo->track->length + car->_distFromStartLine;
    
}

static void 
ReSortCars(void)
{
    int		i,j;
    tCarElt	*car;
    int		allfinish;
    tSituation	*s = ReInfo->s;

    if ((s->cars[0]->_state & RM_CAR_STATE_FINISH) == 0) {
	allfinish = 0;
    } else {
	allfinish = 1;
    }
    
    for (i = 1; i < s->_ncars; i++) {
	j = i;
	while (j > 0) {
	    if ((s->cars[j]->_state & RM_CAR_STATE_FINISH) == 0) {
		allfinish = 0;
		if (s->cars[j]->_distRaced > s->cars[j-1]->_distRaced) {
		    car = s->cars[j];
		    s->cars[j] = s->cars[j-1];
		    s->cars[j-1] = car;
		    if (s->current == j) {
			s->current = j-1;
		    } else if (s->current == j-1) {
			s->current = j;
		    }
		    s->cars[j]->_pos = j+1;
		    s->cars[j-1]->_pos = j;
		    j--;
		    continue;
		}
	    }
	    j = 0;
	}
    }
    if (allfinish) {
	ReInfo->s->_raceState = RM_RACE_ENDED;
    }
}

void
ReOneStep(void *telem)
{
    int i;
    tRobotItf *robot;
    tSituation	*s = ReInfo->s;

    if (floor(s->currentTime) == -2.0) {
	ReRaceBigMsgSet("Ready !", 1.0);
    } else if (floor(s->currentTime) == -1.0) {
	ReRaceBigMsgSet("Set !", 1.0);
    } else if (floor(s->currentTime) == 0.0) {
	ReRaceBigMsgSet("Go !", 1.0);
    }

    ReInfo->_reCurTime += RCM_MAX_DT_SIMU * ReInfo->_reTimeMult; /* "Real" time */
    s->currentTime += RCM_MAX_DT_SIMU; /* Simulated time */

    if (s->currentTime < 0) {
	/* no simu yet */
	return;
    }
    
    if (ReInfo->s->_raceState & RM_RACE_STARTING) {
	ReInfo->s->_raceState = RM_RACE_RUNNING;
	s->currentTime = 0.0; /* resynchronize */
    }
    
    START_PROFILE("rbDrive*");
    if ((s->currentTime - ReInfo->_reLastTime) >= RCM_MAX_DT_ROBOTS) {
	s->deltaTime = s->currentTime - ReInfo->_reLastTime;
	for (i = 0; i < s->_ncars; i++) {
	    if ((s->cars[i]->_state & RM_CAR_STATE_NO_SIMU) == 0) {
		robot = s->cars[i]->robot;
		robot->rbDrive(robot->index, s->cars[i], s);
	    }
	}
	ReInfo->_reLastTime = s->currentTime;
    }
    STOP_PROFILE("rbDrive*");

    START_PROFILE("_reSimItf.update*");
    if (telem) {
	ReInfo->_reSimItf.update(s, RCM_MAX_DT_SIMU, s->cars[s->current]->index);
    } else {
	ReInfo->_reSimItf.update(s, RCM_MAX_DT_SIMU, -1);
    }
    for (i = 0; i < s->_ncars; i++) {
	ReManage(s->cars[i]);
    }
    STOP_PROFILE("_reSimItf.update*");

    ReRaceMsgUpdate();
    ReSortCars();
}

void
ReStart(void)
{
    ReInfo->_reRunning = 1;
    ReInfo->_reCurTime = GfTimeClock() - RCM_MAX_DT_SIMU;
}

void
ReStop(void)
{
    ReInfo->_reRunning = 0;
}


int
ReUpdate(void)
{
    double t;

    START_PROFILE("ReUpdate");
    ReInfo->_refreshDisplay = 0;
    switch (ReInfo->_displayMode) {
    case RM_DISP_MODE_NORMAL:
	t = GfTimeClock();

	START_PROFILE("ReOneStep*");
	while (ReInfo->_reRunning && ((t - ReInfo->_reCurTime) > RCM_MAX_DT_SIMU)) {
	    ReOneStep(NULL);
	}
	STOP_PROFILE("ReOneStep*");

	GfuiDisplay();
	ReInfo->_reGraphicItf.refresh(ReInfo->s);
	glutPostRedisplay();	/* Callback -> reDisplay */
	break;
	
    case RM_DISP_MODE_NONE:
	ReOneStep(NULL);
	if (ReInfo->_refreshDisplay) {
	    GfuiDisplay();
	}
	glutPostRedisplay();	/* Callback -> reDisplay */
	break;
    }

    STOP_PROFILE("ReUpdate");
    return RM_ASYNC;
}

void
ReNextCar(void *dummy)
{
    tSituation	*s = ReInfo->s;

    s->current++;
    if (s->current == s->_ncars) {
	s->current--;
    }
    GfParmSetStr(ReInfo->_reParam, RM_SECT_DRIVERS, RM_ATTR_FOCUSED,
		 s->cars[s->current]->_modName);
    GfParmSetNum(ReInfo->_reParam, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, (char*)NULL,
		 (tdble)(s->cars[s->current]->_driverIndex));
    s->cars[s->current]->priv.collision = 0;
}

void
RePrevCar(void *dummy)
{
    tSituation	*s = ReInfo->s;

    s->current--;
    if (s->current < 0) {
	s->current = 0;
    }
    GfParmSetStr(ReInfo->_reParam, RM_SECT_DRIVERS, RM_ATTR_FOCUSED,
		 s->cars[s->current]->_modName);
    GfParmSetNum(ReInfo->_reParam, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, (char*)NULL,
		 (tdble)(s->cars[s->current]->_driverIndex));
    s->cars[s->current]->priv.collision = 0;
}

void
ReTimeMod (void *vcmd)
{
    switch ((int)vcmd) {
    case 0:
	ReInfo->_reTimeMult *= 2.0;
	if (ReInfo->_reTimeMult > 64.0) {
	    ReInfo->_reTimeMult = 64.0;
	}
	break;
    case 1:
	ReInfo->_reTimeMult *= 0.5;
	if (ReInfo->_reTimeMult < 0.25) {
	    ReInfo->_reTimeMult = 0.25;
	}
	break;
    case 2:
    default:
	ReInfo->_reTimeMult = 1.0;
	break;
    }
    sprintf(buf, "Time x%.2f", 1.0 / ReInfo->_reTimeMult);
    ReRaceMsgSet(buf, 5);
}
