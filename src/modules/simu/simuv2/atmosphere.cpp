/***************************************************************************

    file                 : atmosphere.cpp
    created              : Sun Feb 12 17:37:50 CET 2017
    copyright            : (C) 2017-2017 by Bernhard Wymann
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

#include "sim.h"

void SimAtmosphereConfig(tCar *car)
{
	// Nothing for now
}


void SimAtmosphereUpdate(tCar *car, tSituation *s)
{
	// TODO: get this later form the situation, weather simulation.
	car->localTemperature = 273.15f + 20.0f;
	car->localPressure = 101300.0f;
}
