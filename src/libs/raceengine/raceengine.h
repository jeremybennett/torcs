/***************************************************************************

    file        : raceengine.h
    created     : Sat Nov 23 09:35:21 CET 2002
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
    		
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/

#ifndef _RACEENGINE_H_
#define _RACEENGINE_H_

extern int  ReRacePrepare(void);
extern int  ReRaceEnd(void);
extern int  ReRaceCleanDrivers(void);

extern void ReStart(void);
extern void ReStop(void);
extern void ReUpdate(void);
extern void ReNextCar(void *dummy);
extern void RePrevCar(void *dummy);
extern void ReTimeMod (void *vcmd);
extern void ReOneStep(void *telem);

#endif /* _RACEENGINE_H_ */ 



