/***************************************************************************

    file                 : strategy.h
    created              : Wed Sep 22 15:31:51 CET 2004
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
	Pit strategy for drivers. It defines an abstract base class, such that one can easily plug in
	different strategies.
*/

#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <tgf.h>
#include <track.h>
#include <car.h>
#include <raceman.h>
#include <robottools.h>
#include <robot.h>

#include "driver.h"

class AbstractStrategy {
	public:
		// Set Initial fuel at race start.
		virtual void setFuelAtRaceStart(tTrack* t, void **carParmHandle, tSituation *s) = 0;
		// Update internal data at every timestep.
		virtual void update(tCarElt* car, tSituation *s) = 0;
		// Do we need a pit stop? Can be called less frequently.
		virtual bool needPitstop(tCarElt* car, tSituation *s) = 0;
		// How much to refuel at pit stop.
		virtual float pitRefuel(tCarElt* car, tSituation *s) = 0;
		// How much repair at pit stop.
		virtual int pitRepair(tCarElt* car, tSituation *s) = 0;
};


class SimpleStrategy : public AbstractStrategy {
	public:
		SimpleStrategy();
		virtual ~SimpleStrategy();

		void setFuelAtRaceStart(tTrack* t, void **carParmHandle, tSituation *s);
		void update(tCarElt* car, tSituation *s);
		bool needPitstop(tCarElt* car, tSituation *s);
		float pitRefuel(tCarElt* car, tSituation *s);
		int pitRepair(tCarElt* car, tSituation *s);

	protected:
		bool fuelchecked;				// Fuel statistics updated.
		float fuelperlap;				// The maximum amount of fuel we needed for a lap.
		float lastpitfuel;				// Amount refueled, special case when we refuel.
		float lastfuel;					// the fuel available when we cross the start lane.
		float expectedfuelperlap;		// Expected fuel per lap (may be very inaccurate).

		static const float MAX_FUEL_PER_METER;	// [kg/m] fuel consumtion.
		static const int PIT_DAMMAGE;			// If damage > we request a pit stop.
};



#endif // _STRATEGY_H_


