/***************************************************************************

    file                 : splash.cpp
    created              : Sat Mar 18 23:49:03 CET 2000
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

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#include <tgf.h>

#include "splash.h"
#include "mainmenu.h"

static int ImgWidth, ImgHeight;
static GLenum ImgFormat;
static GLubyte *Image = (GLubyte *)NULL;

static int SplashDisplaying;

/*
 * Function
 *	splashKey
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	
 *
 * Remarks
 *	
 */
static void 
splashKey( unsigned char key, int x, int y )
{
    SplashDisplaying = 0;
    free(Image);
    Image = (GLubyte *)NULL;
    TorcsMainMenuRun();
}

/*
 * Function
 *	
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	
 *
 * Remarks
 *	
 */
static void
splashTimer(int value)
{
    if (SplashDisplaying) {
	SplashDisplaying = 0;
	free(Image);
	Image = (GLubyte *)NULL;
	TorcsMainMenuRun();
    }
}
	

/*
 * Function
 *	splashDisplay
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	
 *
 * Remarks
 *	
 */
static void 
splashDisplay( void )
{
    int w,h,sw,sh;
    
    SplashDisplaying = 1;
    
    glClear( GL_COLOR_BUFFER_BIT );

    //glRasterPos2i((GfScrWidth - ImgWidth)/2, (GfScrHeight - ImgHeight)/2);
    
    glRasterPos2i(0,0);
    GfScrGetSize(&sw, &sh, &w, &h);
    glPixelZoom((float)w / (float)ImgWidth, (float)h / (float)ImgHeight);

    glDrawPixels(ImgWidth, ImgHeight, ImgFormat, GL_UNSIGNED_BYTE, Image);

    glutSwapBuffers();
}

static void
splashMouse(int b, int s, int x, int y)
{
    if (s == GLUT_UP) {
	SplashDisplaying = 0;
	free(Image);
	Image = (GLubyte *)NULL;
	TorcsMainMenuRun();
    }
}


/*
 * Function
 *	
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	
 *
 * Remarks
 *	
 */
int 
SplashScreen(void)
{
    void	*handle;
    float	screen_gamma;
    char	*img = "data/img/splash.png";
    
    if (!Image) {
	handle = GfParmReadFile(GFSCR_CONF_FILE, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
	screen_gamma = (float)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_GAMMA, (char*)NULL, 2.0);
	Image = GfImgReadPng(img , &ImgWidth, &ImgHeight, screen_gamma);
	ImgFormat = GL_RGBA;
    }
    if (!Image) {
	GfTrace1("Couldn't read %s\n", img);
	return -1;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

    glutDisplayFunc(splashDisplay);
    glutKeyboardFunc(splashKey);
    glutSpecialFunc((void (*)(int key, int x, int y))NULL);
    glutTimerFunc(7000, splashTimer, 0);
    glutMouseFunc(splashMouse);
    glutPostRedisplay();
    
    return 0;
}


