/***************************************************************************
                     screenshot.cpp -- make screen shots                                 
                             -------------------                                         
    created              : Wed Aug 18 12:50:34 CEST 1999
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

/** @package	Race Manager Tools
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/glut.h>
#include <tgf.h>

/** Save a screen shot in png format
 */
void
RmScreenShot(void * /* notused */)
{
    unsigned char	*img;
    char		buf[256];
    struct tm		*stm;
    time_t		t;
    
    img = (unsigned char*)malloc(GfScrWidth * GfScrHeight * 3);
    if (img == NULL) {
	return;
    }
    
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, GfScrWidth, GfScrHeight, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)img);

    t = time(NULL);
    stm = localtime(&t);
    sprintf(buf, "torcs-%4d%02d%02d%02d%02d%02d.png",
	    stm->tm_year+1900,
	    stm->tm_mon+1,
	    stm->tm_mday,
	    stm->tm_hour,
	    stm->tm_min,
	    stm->tm_sec);
    GfImgWritePng(img, buf, GfScrWidth, GfScrHeight);

    free(img);
}
