/***************************************************************************

    file                 : qracegl.h
    created              : Sun Jan 30 22:41:11 CET 2000
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
 
#ifndef _QRACEGL_H_
#define _QRACEGL_H_


extern void *qrHandle;

extern void qraceglRun(void);
extern void qraceglShutdown(void);
extern void qrResults(void *prevHdle);

#endif /* _QRACEGL_H_ */ 



