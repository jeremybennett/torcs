/***************************************************************************

    file                 : main.cpp
    created              : Sat Sep  2 10:40:47 CEST 2000
    copyright            : (C) 2000 by Patrice & Eric Espie
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
#endif
#include <GL/glut.h>
#include <tgfclient.h>
#include <client.h>

#include "windowsspec.h"

static void
init_args(int argc, char **argv)
{
    int		i;
    char	*buf;

    i = 1;
    while (i < argc) {
	if ((strncmp(argv[i], "-s", 2) == 0) || (strncmp(argv[i], "/s", 2) == 0)) {
	    i++;
	    SetSingleTextureMode ();
	} else {
	    i++;		/* ignore bad args */
	}
    }
}
/*
 * Function
 *	main
 *
 * Description
 *	Win32 entry point of TORCS
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
main(int argc, char *argv[])
{
    init_args(argc, argv);

    WindowsSpecInit();		/* init specific windows functions */
    
    GfScrInit(argc, argv);	/* init screen */

    TorcsEntry();		/* launch TORCS */
    
    glutMainLoop();		/* event loop of glut */
    
    return 0;			/* just for the compiler, never reached */
}

