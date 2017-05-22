// Driver class declaration

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

#ifndef DRIVER_H
#define DRIVER_H

#include "car.h"
#include "raceman.h"
#include "track.h"


//! The main jeremy robot class

//! An instance of this class is declared for each driver. It holds all state
//! for the robot and provides public entry points for all the TORCS callback
//! functions.

class Driver {

public:

  // Constructor and destructor

  Driver (int  index);
  ~Driver();

  // Entry points for TORC callback functions

  void initTrack (tTrack *     t,
		  void *       carHandle,
		  void **      carParmHandle,
		  tSituation * s);

  void newRace (tCarElt *    car,
		tSituation * s);

  void drive (tSituation * s);

  int pitCmd (tSituation * s);

  void endRace (tSituation * s);

private:

  //! Our driver number

  int  mIndex;

  //! The car currently being used by the driver

  tCarElt * mCar;

};	// class Driver


#endif	// DRIVER_H


// Local Variables:
// mode: C++
// c-file-style: "gnu"
// End:
