/***************************************************************************

    file                 : main.cpp
    created              : Sat Mar 18 23:54:30 CET 2000
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

#include <tgf.h>
#include <torcs.h>
#include <stdlib.h>
#include <string.h>

#include "linuxspec.h"

static void
init_args(int argc, char **argv)
{
    int		i;
    char	*buf;

    i = 1;
    while (i < argc) {
	if (strncmp(argv[i], "-l", 2) == 0) {
	    i++;
	    if (i < argc) {
		buf = (char *)malloc(strlen(argv[i]) + 2);
		sprintf(buf, "%s/", argv[i]);
		SetLocalDir(buf);
		i++;
	    }
	} else if (strncmp(argv[i], "-m", 2) == 0) {
	    i++;
	    GfuiMouseSetHWPresent(); /* allow the hardware cursor */
	}
    }
}

/*
 * Function
 *	main
 *
 * Description
 *	LINUX entry point of TORCS
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
    
    LinuxSpecInit();		/* init specific linux functions */
    
    GfScrInit(argc, argv);	/* init screen */

    TorcsEntry();		/* launch TORCS */
    
    glutMainLoop();		/* event loop of glut */
    
    return 0;			/* just for the compiler, never reached */
}

