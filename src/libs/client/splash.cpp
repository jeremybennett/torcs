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
#ifdef WIN32
#include <windows.h>
#define HAVE_CONFIG_H
#endif
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <tgfclient.h>

#include "splash.h"
#include "mainmenu.h"

static int ImgWidth, ImgHeight;
static GLenum ImgFormat;
static GLubyte *Image = (GLubyte *)NULL;

static int SplashDisplaying;

static char buf[1024];

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
splashKey( unsigned char /* key */, int /* x */, int /* y */)
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
splashTimer(int /* value */)
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

    glRasterPos2i(0,0);
    GfScrGetSize(&sw, &sh, &w, &h);
    glPixelZoom((float)w / (float)ImgWidth, (float)h / (float)ImgHeight);

    glDrawPixels(ImgWidth, ImgHeight, ImgFormat, GL_UNSIGNED_BYTE, Image);

#ifdef HAVE_CONFIG_H
	//glPixelZoom(1.0, 1.0);
	glDisable(GL_LIGHTING);
	static float grWhite[4] = {1.0, 1.0, 1.0, 1.0};
	GfuiPrintString(VERSION, grWhite, GFUI_FONT_SMALL_C, 640-8, 8, GFUI_ALIGN_HR_VB);
#endif

	glutSwapBuffers();
}

static void
splashMouse(int /* b */, int s, int /* x */, int /* y */)
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
	sprintf(buf, "%s%s", GetLocalDir(), GFSCR_CONF_FILE);
	handle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
	screen_gamma = (float)GfParmGetNum(handle, GFSCR_SECT_PROP, GFSCR_ATT_GAMMA, (char*)NULL, 2.0);
	Image = GfImgReadPng(img , &ImgWidth, &ImgHeight, screen_gamma);
	ImgFormat = GL_RGBA;
    }
    if (!Image) {
	GfTrace("Couldn't read %s\n", img);
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


