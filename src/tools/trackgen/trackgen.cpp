/***************************************************************************

    file                 : trackgen.cpp
    created              : Sat Dec 23 09:27:43 CET 2000
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

/** @file   
    		
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifndef WIN32
#include <unistd.h>
#endif
#define _GNU_SOURCE
#ifndef WIN32
#include <getopt.h>
#endif
#include <math.h>
#include <ttypes.h>
#include <plib/ul.h>

#include "trackgen.h"

int Orientation;
int SceneDraw;

char	*InputFileName = NULL;
char	*OutputFileName = NULL;
char	*ReliefFileName = NULL;
float	GridStep = 40.0;
float	TrackStep = 5.0;
float	Margin = 100.0;
float	ExtHeight = 5.0;


void usage(void)
{
    fprintf(stderr, "Terrain generator for tracks $Revision$ \n");
    fprintf(stderr, "Usage: trackgen [-n] <input xmlfile>\n");
    fprintf(stderr, "<input xmlfile>  : input track in XML format\n");
    fprintf(stderr, "n                : don't draw scenery\n");
}

void init_args(int argc, char **argv)
{
    int		c;
    
    Orientation = CLOCKWISE;
    SceneDraw = 1;

#ifndef WIN32
    while (1) {
	int option_index = 0;
	static struct option long_options[] = {
	    {"help", 0, 0, 0},
	    {"version", 1, 0, 0}
	};

	c = getopt_long(argc, argv, "hvn",
			long_options, &option_index);
	if (c == -1)
	    break;
	     
	switch (c) {
	case 0:
	    switch (option_index) {
	    case 0:
		usage();
		exit(0);
		break;
	    case 1:
		printf("Terrain generator for tracks $Revision$ \n");
		exit(0);
		break;
	    default:
		usage();
		exit(1);
	    }
	    break;
	case 'h':
	    usage();
	    exit(0);
	    break;
	case 'v':
	    printf("Terrain generator for tracks $Revision$ \n");
	    exit(0);
	    break;
	case 'n':
	    SceneDraw = 0;
	    break;
	default:
	    usage();
	    exit(1);
	    break;
	}
    }
#else
    if (argc==1)
      {
	usage();
	exit(1);
      }
    if (argc==2)
      {
	if (strncmp(argv[1],"-h",2)==0)
	  {
	    usage();
	    exit(0);
	  }
	else if (strncmp(argv[1],"-v",2)==0)
	  {
	    printf("Terrain generator for tracks $Revision$ \n");
	    exit(0);
	  }
	else if (strncmp(argv[1],"-n",2)==0)
	  {
	    SceneDraw=0;
	  }
	else
	  {
	    InputFileName = strdup(argv[1]);
	  }
      }
    else
      {
	usage();
	exit(1);
      }
#endif

#ifndef WIN32
    if (optind < argc) {
	if (optind == argc - 1) {
	    InputFileName = strdup(argv[optind]);
	} else {
	    usage();
	    exit(1);
	}
    }
#endif

    if (!ulFileExists(InputFileName)) {
	fprintf(stderr, "The Input XML track file is not correct\n");
	exit(1);
    }
}
#ifndef WIN32
extern void LinuxSpecInit(void);
#else
extern void WindowsSpecInit(void);
#endif

int
main(int argc, char **argv)
{

    init_args(argc, argv);
#ifndef WIN32
    LinuxSpecInit();
#else
    WindowsSpecInit();
#endif

    GenerateTrack(InputFileName);
    return 0;
}
