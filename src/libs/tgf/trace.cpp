/***************************************************************************
                                   TRACE                   
                             -------------------                                         
    created              : Fri Aug 13 22:32:45 CEST 1999
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

/** @file
    Allow the trace in the file <tt>trace.txt</tt>
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
    @ingroup	trace
*/


#if _WIN32
#include <windows.h>
#include <windowsx.h>
#endif /* _WIN32 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <tgf.h>

static FILE *outTrace = (FILE*)NULL;

void
gfTraceInit(void)
{
}


/** Print a message in the trace file.
    The file is openned the first time
    @ingroup	trace
    @param	szTrc	message to trace
*/
void GfTrace(char *szTrc)
{
#if DEBUG_OUT
    fprintf(stderr, "**********************************\n%s**********************************\n", szTrc);
    fflush(stderr);
#endif
    if (outTrace == NULL) {
	if ((outTrace = fopen("trace.txt", "w+")) == NULL) {
	    perror("trace.txt");
	    return;
	}
    }
    fwrite(szTrc, strlen(szTrc), 1, outTrace);
    fflush(outTrace);
}

