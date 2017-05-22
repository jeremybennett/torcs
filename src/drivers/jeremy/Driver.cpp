// Driver class definition

// Copyright (C) 2017 Jeremy Bennett
// Contributor: Jeremy Bennett <jeremy@jeremybennett.com>

// This file is part of the jeremy robot for TORCS

// The jeremy robot for TORCS is free software: you can redistribute
// it and/or modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "Driver.h"

#include "robot.h"


//! Constructor

//! For now this just records our driver number.  Other methods will do the
//! hard work.

//! @param[in] index  Our driver number.

Driver::Driver (int index)
{
  mIndex = index;

}	// Driver::Driver ()


//! Destructor.

//! Give back anything we created. At the moment that's nothing.

Driver::~Driver()
{
}	// Driver::~Driver ()


//! New track or new race

//! @param[in]  t              The track being initialized.
//! @param      carHandle      What is this?
//! @param[out] carParmHandle  What is this?
//! @param[in]  s              Info about the current state

void
Driver::initTrack (tTrack *     t,
		   void *       carHandle __attribute__ ((unused)),
		   void **      carParmHandle __attribute__ ((unused)),
		   tSituation * s)
{
}	// Driver::initTrack ()


//! New race

//! Remember the car

//! @param[in] car  The car for this race.
//! @param[in] s    Info about the current state

void
Driver::newRace (tCarElt *    car,
		 tSituation * s)
{
  mCar = car;

}	// Driver::newRace ()


//! Driver the car

//! Called ever 20ms to allow the car to be updated.

//! @param[in] s    Info about the current state

void
Driver::drive (tSituation * s)
{
  memset (&(mCar->ctrl), 0, sizeof (mCar->ctrl));

  mCar->_steerCmd  = 0.0;
  mCar->_gearCmd   = 6;
  mCar->_accelCmd  = 1.0;
  mCar->_brakeCmd  = 0.0;
  mCar->_clutchCmd = 0.0;

}	// Driver::drive ()


//! Handle a pit stop

//! @param[in] s    Info about the current state
//! @return  What action to take next (enumeration)

int
Driver::pitCmd (tSituation * s)
{
  return ROB_PIT_IM;			// Only available response.

}	// Driver::pitCmd ()


//! Race has ended

//! @param[in] s    Info about the current state

void
Driver::endRace (tSituation * s)
{
}	// Driver::endRace ()


// Local Variables:
// mode: C++
// c-file-style: "gnu"
// End:
