/***************************************************************************

    file                 : util.cpp
    created              : Wed May 29 22:20:24 CEST 2002
    copyright            : (C) 2001 by Eric Espie
    email                : eric.espie@torcs.org
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
    		
    @author	<a href=mailto:eric.espie@torcs.org>Eric Espie</a>
    @version	$Id$
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifndef WIN32
#include <unistd.h>
#endif

#include <plib/ul.h>
#include <tgf.h>

#include "util.h"

int
GetFilename(char *filename, char *filepath, char *buf)
{
    char	*c1, *c2;
    int		found = 0;
    int		lg;
    
    if (filepath) {
	c1 = filepath;
	c2 = c1;
	while ((!found) && (c2 != NULL)) {
	    c2 = strchr(c1, ';');
	    if (c2 == NULL) {
		sprintf(buf, "%s/%s", c1, filename);
	    } else {
		lg = c2 - c1;
		strncpy(buf, c1, lg);
		buf[lg] = '/';
		strcpy(buf + lg + 1, filename);
	    }
	    if (ulFileExists(buf)) {
		found = 1;
	    }
	    c1 = c2 + 1;
	}
    } else {
	strcpy(buf, filename);
	if (ulFileExists(buf)) {
	    found = 1;
	}
    }
    if (!found) {
	printf("File %s not found\n", filename);
	printf("File Path was %s\n", filepath);
	return 0;
    }

    return 1;
}
