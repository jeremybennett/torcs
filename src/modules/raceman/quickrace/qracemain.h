/***************************************************************************

    file                 : qracemain.h
    created              : Sun Jan 30 22:41:39 CET 2000
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
 
#ifndef _QRACEMAIN_H_
#define _QRACEMAIN_H_

#include <ttypes.h>
#include <track.h>
#include <car.h>
#include <simu.h>
#include <graphic.h>
#include <telemetry.h>
#include <robot.h>
#include <racemantools.h>

#define QRACE_CFG	"config/quickrace/qrace.xml"

extern tRmInfo	*RmInfo;
extern void	*qrMainMenuHandle;


extern void qrConfigInit(void);
extern void qrConfigRunState(void * /* dummy */);
extern void qrMenuRun(void);

#endif /* _QRACEMAIN_H_ */ 



