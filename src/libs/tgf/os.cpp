/***************************************************************************
                         Os.cpp -- os specific function table                             
                             -------------------                                         
    created              : Fri Aug 13 22:26:42 CEST 1999
    copyright            : (C) 1999 by Eric Espie                         
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

/** @package	OS
    @packinfo	OS specific function table
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include "os.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif


/*
 * Globals definitions
 */
#ifdef WIN32
__declspec(dllexport)
#endif // WIN32
tGfOs GfOs = {0};

void
gfOsInit(void)
{
}


/** Get the time in seconds
    @return	Time in seconds since the start of the system
 */
double
GfTimeClock(void)
{
    if (GfOs.timeClock) {
	return GfOs.timeClock();
    } else {
	return 0;
    }
}
