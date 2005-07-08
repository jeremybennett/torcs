/***************************************************************************

    file        : portability.h
    created     : Fri Jul 8 15:19:34 CET 2005
    copyright   : (C) 2005 Bernhard Wymann
    email       : berniw@bluewin.ch
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

#ifndef _TORCS_PORATBILITY_H_
#define _TORCS_PORATBILITY_H_

#include <stdlib.h>
#include <string.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// Missing strndup, define it here (for FreeBSD).
// TODO: Move it into library.
// strndup code provided by Thierry Thomas.
#ifndef HAVE_STRNDUP

static char *strndup(const char *str, int len)
{
	char *ret;

	if ((str == NULL || len < 0)) {
		return (NULL);
	}

	ret = (char *) malloc(len + 1);
	if (ret == NULL) {
		return (NULL);
	}

	memcpy(ret, str, len);
	ret[len] = '\0';
	return (ret);
}

#endif


#endif // _TORCS_PORATBILITY_H_

