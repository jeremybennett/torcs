/***************************************************************************

    file                 : memory.cpp
    created              : Mon Aug 23 19:23:53 CEST 1999
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

/** @package	Memory
    @packinfo	Memory allocation and free management per module.
		This API allows to allocate memory and free all the
		previously allocated memory at once for a module.
		This is just to ease the memory management for lazy programmers...
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/


#ifdef DMALLOC
#include "dmalloc.h"
#endif
