/***************************************************************************

    file                 : strategy.cpp
    created              : Wed Sep 22 15:32:21 CET 2004
    copyright            : (C) 2004 Bernhard Wymann
    email                : berniw@bluewin.ch
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

/*
	Very simple stategy sample implementation.
*/


#include "strategy.h"

const float SimpleStrategy::MAX_FUEL_PER_METER = 0.0008f;	// [kg/m] fuel consumtion.
const int SimpleStrategy::PIT_DAMMAGE = 5000;				// [-]


SimpleStrategy::SimpleStrategy() :
	fuelchecked(false),
	fuelperlap(0.0),
	lastpitfuel(0.0)
{
	// Nothing so far.
}


SimpleStrategy::~SimpleStrategy()
{
	// Nothing so far.
}


// Trivial strategy: fill in as much fuel as required for the whole race, or if the tank is
// too small fill the tank completely.
void SimpleStrategy::setFuelAtRaceStart(tTrack* t, void **carParmHandle, tSituation *s)
{
	// Load and set parameters.
	float fuel = GfParmGetNum(*carParmHandle, BT_SECT_PRIV, BT_ATT_FUELPERLAP, (char*) NULL, t->length*MAX_FUEL_PER_METER);
	expectedfuelperlap = fuel;
	float maxfuel = GfParmGetNum(*carParmHandle, SECT_CAR, PRM_TANK, (char*) NULL, 100.0);
	fuel *= (s->_totLaps + 1.0);
	lastfuel = MIN(fuel, maxfuel);
	GfParmSetNum(*carParmHandle, SECT_CAR, PRM_FUEL, (char*) NULL, lastfuel);
}


void SimpleStrategy::update(tCarElt* car, tSituation *s)
{
	// Fuel statistics update.
	int id = car->_trkPos.seg->id;
	// Range must include enough segments to be executed once guaranteed.
	if (id >= 0 && id < 5 && !fuelchecked) {
		if (car->race.laps > 1) {
			fuelperlap = MAX(fuelperlap, (lastfuel+lastpitfuel-car->priv.fuel));
		}
		lastfuel = car->priv.fuel;
		lastpitfuel = 0.0;
		fuelchecked = true;
	} else if (id > 5) {
		fuelchecked = false;
	}
}


bool SimpleStrategy::needPitstop(tCarElt* car, tSituation *s)
{
	// Do we need to refuel?
	int laps = car->_remainingLaps-car->_lapsBehindLeader;
	if (laps > 0) {
		float cmpfuel = (fuelperlap == 0.0) ? expectedfuelperlap : fuelperlap;
		if (car->_fuel < 1.5*cmpfuel &&
			car->_fuel < laps*cmpfuel)
		{
				return true;
		}
	}

	// Do we need to repair?
	if (car->_dammage > PIT_DAMMAGE) {
		return true;
	}

	return false;
}


float SimpleStrategy::pitRefuel(tCarElt* car, tSituation *s)
{
	float fuel;
	float cmpfuel = (fuelperlap == 0.0) ? expectedfuelperlap : fuelperlap;
	fuel = MAX(MIN((car->_remainingLaps+1.0)*cmpfuel - car->_fuel,
					car->_tank - car->_fuel),
			   0.0);
	lastpitfuel = fuel;
	return fuel;
}


int SimpleStrategy::pitRepair(tCarElt* car, tSituation *s)
{
	return car->_dammage;
}


