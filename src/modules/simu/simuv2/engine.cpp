/***************************************************************************

    file                 : engine.cpp
    created              : Sun Mar 19 00:06:55 CET 2000
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

#include "sim.h"

void
SimEngineConfig(tCar *car)
{
    void	*hdle = car->params;
    int		i;
    tdble	maxTq;
    tdble	rpmMaxTq = 0;
    char	idx[64];
    tEngineCurveElem *data;
    struct {
	    tdble rpm;
	    tdble tq;
    } 		edesc[MAXPTS];

    car->engine.revsLimiter = GfParmGetNum(hdle, SECT_ENGINE, PRM_REVSLIM, (char*)NULL, 800);
    car->carElt->_enginerpmRedLine = car->engine.revsLimiter;
    car->engine.revsMax     = GfParmGetNum(hdle, SECT_ENGINE, PRM_REVSMAX, (char*)NULL, 1000);
    car->carElt->_enginerpmMax = car->engine.revsMax;
    car->engine.tickover    = GfParmGetNum(hdle, SECT_ENGINE, PRM_TICKOVER, (char*)NULL, 150);
    car->engine.I           = GfParmGetNum(hdle, SECT_ENGINE, PRM_INERTIA, (char*)NULL, 0.2423);
    car->engine.fuelcons    = GfParmGetNum(hdle, SECT_ENGINE, PRM_FUELCONS, (char*)NULL, 0.0622);
    car->engine.brakeCoeff  = GfParmGetNum(hdle, SECT_ENGINE, PRM_ENGBRKCOEFF, (char*)NULL, 0.33);
    
    for (i = 0; i < MAXPTS; i++) {
	sprintf(idx, "%s/%s/%d", SECT_ENGINE, ARR_DATAPTS, i+1);
	edesc[i].rpm = GfParmGetNum(hdle, idx, PRM_RPM, (char*)NULL, car->engine.revsMax);
	edesc[i].tq  = GfParmGetNum(hdle, idx, PRM_TQ, (char*)NULL, 0);
    }

    maxTq = 0;
    for(i = 0; i < MAXPTS; i++) {
	data = &(car->engine.curve.data[i]);

	data->rads = edesc[i+1].rpm;
	if(edesc[i+1].tq > maxTq) {
	    maxTq = edesc[i+1].tq;
	    rpmMaxTq = data->rads;
	}
	data->a = (edesc[i+1].tq - edesc[i].tq) / (edesc[i+1].rpm - edesc[i].rpm);
	data->b = edesc[i].tq - data->a * edesc[i].rpm;
    }
    car->engine.curve.maxTq = maxTq;
    car->carElt->_enginerpmMaxTq = rpmMaxTq;
    car->engine.rads = car->engine.tickover;
}

/* Update torque output with engine rpm and accelerator command */
void
SimEngineUpdateTq(tCar *car)
{
    int		i;
    tEngine	*engine = &(car->engine);
    tEngineCurve *curve = &(engine->curve);
    
    if ((car->fuel <= 0.0) || (car->carElt->_state & RM_CAR_STATE_BROKEN)) {
	engine->rads = 0;
	engine->Tq = 0;
	return;
    }

    if (engine->rads > engine->revsLimiter) {
	engine->rads = engine->revsLimiter;
	engine->Tq = 0;
    } else {
	for (i = 0; i < MAXPTS; i++) {
	    if (engine->rads < curve->data[i].rads) {
		tdble Tmax = engine->rads * curve->data[i].a + curve->data[i].b;
		tdble EngBrkK = engine->brakeCoeff * (engine->rads - engine->tickover) / (engine->revsMax - engine->tickover);
		
		engine->Tq =  Tmax * (car->ctrl->accelCmd * (1.0 + EngBrkK) - EngBrkK);
		car->fuel -= engine->Tq * engine->rads * engine->fuelcons * 0.0000001 * SimDeltaTime;
		if (car->fuel <= 0.0) {
		    car->fuel = 0.0;
		}
		return;
	    }
	}
    } 
}

/*
 * Function
 *	SimEngineUpdateRpm
 *
 * Description
 *	update engine RPM with wheels RPM
 *
 * Parameters
 *	car and axle RPM
 *
 * Return
 *	axle rpm for wheel update
 *	0 if no wheel update
 */
tdble
SimEngineUpdateRpm(tCar *car, tdble axleRpm)
{
    tTransmission	*trans = &(car->transmission);
    tEngine		*engine = &(car->engine);

    if (car->fuel <= 0.0) {
	engine->rads = 0;
	trans->clutch.state = CLUTCH_APPLIED;
	return 0.0;
    }
    if ((trans->clutch.state == CLUTCH_RELEASED) && (trans->gearbox.gear)) {
	engine->rads = axleRpm * trans->curOverallRatio;
	if (engine->rads < engine->tickover) {
	    engine->rads = engine->tickover;
	} else if (engine->rads > engine->revsMax) {
	    engine->rads = engine->revsMax;
	    return engine->revsMax / trans->curOverallRatio;
	}
    } else {
	//engine->rads = engine->tickover + (car->ctrl->accelCmd * (engine->revsLimiter - engine->tickover));
	engine->rads += engine->Tq / engine->I * SimDeltaTime;
    }
    return 0.0;
}
