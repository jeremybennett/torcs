/***************************************************************************

    file                 : grsound.h
    created              : Thu Aug 17 23:57:35 CEST 2000
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

#ifndef _GRSOUND_H_
#define _GRSOUND_H_

#include <raceman.h>

extern void grInitSound(void);
extern void grShutdownSound(void);
extern void grRefreshSound(tSituation *s);

#endif /* _GRSOUND_H_ */ 



