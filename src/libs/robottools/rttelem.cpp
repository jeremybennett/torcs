/***************************************************************************

    file                 : rttelem.cpp
    created              : Mon Feb 28 22:38:31 CET 2000
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

/** @file	
    		This is a collection of useful functions for using telemetry in a robot.
		You can see an example of telemetry usage in the human driver.
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
    @ingroup	robottools
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <telemetry.h>
#include <robottools.h>
#include <tgf.h>

#ifdef DMALLOC
#include "dmalloc.h"
#endif

static tTelemItf	tlm;
static tModList		*modlist = (tModList*)NULL;

/** Initialization of a telemetry session.
    @ingroup	robottools
    @param	ymin	Minimum value for Y.
    @param	ymax	Maximum value for Y.
    @return	None
 */
void RtTelemInit(tdble ymin, tdble ymax)
{
    char	buf[256];
    tModInfo	*curModInfo;

    memset(&tlm, 0, sizeof(tTelemItf));
    sprintf(buf, "modules/telemetry/%s.%s", "telemetry", DLLEXT);
    if (GfModLoad(TLM_IDENT, buf, &modlist)) return;
    GfOut("--- %s loaded ---\n", modlist->modInfo->name);
    curModInfo = modlist->modInfo;
    curModInfo->fctInit(curModInfo->index, &tlm);

    tlm.init(ymin, ymax);
}


/** Create a new telemetry channel.
    @ingroup	robottools
    @param	name	Name of the channel.
    @param	var	Address of the variable to monitor.
    @param	min	Minimum value of this variable.
    @param	max	Maximum value of this variable.
    @return	None
 */
void RtTelemNewChannel(const char * name, tdble * var, tdble min, tdble max)
{
    tlm.newChannel(name, var, min, max);
}

/** Start recording into a file.
    @ingroup	robottools
    @param	filename	name of the file to use.
    @return	none.
 */
void RtTelemStartMonitoring(const char * filename)
{
    tlm.startMonitoring(filename);
}

/** Stop recording and close the file.
    @ingroup	robottools
    @return	none
 */
void RtTelemStopMonitoring(void)
{
    tlm.stopMonitoring();
}

/** Record a new set of values.
    @ingroup	robottools
    @param	time	current time.
    @return	None.
 */
void RtTelemUpdate(double time)
{
    tlm.update(time);
}

/** Deinstall the telemetry module.
    @ingroup	robottools
    @return	none.
 */
void RtTelemShutdown(void)
{
    tlm.shutdown();
    GfModUnloadList(&modlist);
}

