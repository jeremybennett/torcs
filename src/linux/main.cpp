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

#include "linuxspec.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

static void
torcs_end(void)
{
    printf("Thanks to play with TORCS.\n");
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
    
    /* atexit(torcs_end); */
    
    LinuxSpecInit();		/* init specific linux functions */
    
    GfScrInit(argc, argv);	/* init screen */

    TorcsEntry();		/* launch TORCS */
    
    glutMainLoop();		/* event loop of glut */
    
    return 0;			/* just for the compiler, never reached */
}

