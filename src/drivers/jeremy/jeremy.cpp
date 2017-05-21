// Main entry point for the robot

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

#include <stdlib.h>
#include <string.h>

#include "Driver.h"
#include <math.h>


//! Maximum number of drivers we can control.  This really ought to be set
//! system wide.

static const int MAX_DRIVERS 10;

//! Static array of instances of the drivers.

static Driver *driver[MAX_DRIVERS];


//! Callback for every track change or new race.

//! @param[in] index          Number of the driver pitting
//! @param[in] track          The track we are using
//! @param[in] carHandle      What is this?
//! @param[in] carParmHandle  What is this?
//! @param[in] s              All the info about the race

static void
initTrack (int          index,
	   tTrack *     track,
	   void *       carHandle,
	   void **      carParmHandle,
	   tSituation * s)
{
  driver[index]->initTrack (track, carHandle, carParmHandle, s);

}	//! initTrack ()


//! Callback at start of a new race

//! This is the one time we use the car argument. It is stored within the
//! Driver class instance, so we don't need to pass it in future.

//! @param[in]     index  Number of the driver pitting
//! @param[in,out] car    Car to be processed.
//! @param[in]     s      All the info about the race

static void
newRace (int          index,
	 tCarElt    * car __attribute__ ((unused)),
	 tSituation * s)
{
  driver[index]->newRace (car, s);

}	// newRace ()


//! Callback to control driving during race.

//! Called every 20ms to adjust the parameters controlling the car
//! - steering
//! - accelleration
//! - breaking
//! - gear selection
//! - clutch usage

//! @param[in]     index  Number of the driver
//! @param[in,out] car    Car to be processed (unused).
//! @param[in]     s      All the info about the race

static void
drive (int          index,
	 tCarElt    * car __attribute__ ((unused)),
	 tSituation * s)
{
  driver[index]->drive (s);

}	// drive ()


//! Callback when pitting

//! @param[in]     index  Number of the driver pitting
//! @param[in,out] car    Car to be processed (unused).
//! @param[in]     s      All the info about the race

static void
pitCmd (int          index,
	 tCarElt    * car __attribute__ ((unused)),
	 tSituation * s)
{
  driver[index]->pitCmd (s);

}	// pitCmd ()


//! Callback at end of race.

//! @param[in]     index  Number of the driver whose race has ended
//! @param[in,out] car    Car to be processed (unused).
//! @param[in]     s      All the info about the race

static void
endRace (int          index,
	 tCarElt    * car __attribute__ ((unused)),
	 tSituation * s)
{
  driver[index]->endRace (s);

}	// endRace ()


//! Callback before unloading a driver.

//! @param[in] index  Number of the driver to shut down

static void
shutdown (int index)
{
  delete driver[index];

}	// shutdown ()


//! Initialize the robot for a driver

//! @param[in]  index  Number of the driver to initialize
//! @param[out] pt     Pointer to the robot interface to be initialized,
//!                    passed as void * and cast to the correct type for use.
//! @return Zero on success, non-zero otherwise.

static int
initFunc (int   index,
	  void * pt)
{
  tRobotItf * itf  = static_cast <<tRobotItf *>> pt;

  driver[index] = new Driver (index);	// Each driver knows its index

  itf->rbNewTrack = initTrack;	// Called for every track change or new race
  itf->rbNewRace  = newRace;	// Called at the start of a new race
  itf->rbDrive    = drive;	// Called every 20ms when racing
  itf->rbPitCmd   = pitCmd;	// Called when pitting
  itf->rbEndRace  = endRace;	// Called at end of race
  itf->rbShutdown = shutdown;	// Called when robot is unloaded
  itf->index      = index; 	// Driver number

  return 0;

}	// initFunc ()


//! Module entry point

//! The critical thing is to specify the initialization function for each
//! driver.

//! This function requires C linkage

//! @param[in,out] modInfo  Module info for each driver
//! @return Zero on success, non-zero otherwise.

extern "C" int
jeremy (tModInfo * modInfo)
{
  char *buf = malloc (strlen ("jeremy 10"));	// In which to build name
  int   i;					// Loop counter

  memset (modInfo, 0, MAX_DRIVERS * sizeof (*modInfo));

  // We set this up for every possible driver. Other code just sets up the
  // number of drivers  being declared.

  for (i = 0; i < MAX_DRIVERS; i++)
    {
      sprintf (buf, "jeremy %d", i);
      modInfo[i].name    = strdup (buf);	// short name of the module
      modInfo[i].desc    = strdup("");		// long desc of the module
      modInfo[i].fctInit = initFunc;		// init function - important
      modInfo[i].gfId    = ROB_IDENT;		// supported framework version
      modInfo[i].index   = i;
    }

  free buf;
  return 0;				// We always succeed :)

}	// jeremy ()

// Local Variables:
// mode: C++
// c-file-style: "gnu"
// End:
