/***************************************************************************

    file                 : robot.h
    created              : Sun Jan 30 22:59:40 CET 2000
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
 
 
#ifndef _ROBOTV1_H_
#define _ROBOTV1_H_

#define ROB_IDENT	(TRK_IDENT|RCM_IDENT|CAR_IDENT)


typedef void (*tfRbNewTrack)(int index, tTrack*, void **carParmHandle, tSituation*);
typedef void (*tfRbNewRace) (int index, tCarElt*, tSituation*);
typedef void (*tfRbDrive)   (int index, tCarElt*, tSituation*);
typedef void (*tfRbShutdown)(int index);

#define ROB_PIT_IM	0	/* Immediate return from pit command */
#define ROB_PIT_MENU	1	/* Call the interactive menu for pit command */
typedef int  (*tfRbPitCmd)(int index, tCarElt*, tSituation*);


/* interface for robots */
typedef struct RobotItf {
    tfRbNewTrack	rbNewTrack;	/* give the robot the track view. Called for every track change or new race */
    tfRbNewRace		rbNewRace;	/* Start a new race */
    tfRbDrive		rbDrive;	/* drive during race */
    tfRbShutdown	rbShutdown;	/* called before the dll is unloaded */
    tfRbPitCmd		rbPitCmd;	/* Get the driver's pit commands */
    int			index;		/* index used if multiple interfaces */
} tRobotItf;



/*
 * Parameters definitions for driver
 */
#define ROB_SECT_ROBOTS		"Robots"

#define ROB_LIST_INDEX		"index"

#define ROB_ATTR_NAME		"name"
#define ROB_ATTR_DESC		"desc"
#define ROB_ATTR_AUTHOR		"author"
#define ROB_ATTR_CAR		"car name"
#define ROB_ATTR_CATEGORY	"category"
#define ROB_ATTR_RACENUM	"race number"
#define ROB_ATTR_RED		"red"
#define ROB_ATTR_GREEN		"green"
#define ROB_ATTR_BLUE		"blue"

#endif /* _ROBOTV1_H_ */ 



