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
#include <plib/ssg.h>
#include <GL/glut.h>

#include <tgf.h>
#include <track.h>

#include "ac3d.h"
#include "easymesh.h"
#include "objects.h"
#include "elevation.h"
#include "trackgen.h"

float	GridStep = 40.0;
float	TrackStep = 5.0;
float	Margin = 100.0;
float	ExtHeight = 5.0;


char		*OutputFileName;
char		*TrackName;
char		*TrackCategory;

void		*TrackHandle;
void		*CfgHandle;

tTrack		*Track;
tTrackItf	TrackItf;

int		TrackOnly;
int		MergeAll;
int		MergeTerrain;

static char	buf[1024];
static char	buf2[1024];
static char	trackdef[1024];

char		*OutTrackName;
char		*OutMeshName;

tModList	*modlist = NULL;

int		saveElevation;
char		*ElevationFile;

static void Generate(void);

void usage(void)
{
    fprintf(stderr, "Terrain generator for tracks $Revision$ \n");
    fprintf(stderr, "Usage: trackgen -c category -n name [-a] [-m] [-s] [-S] [-e]\n");
    fprintf(stderr, "       -c category    : track category (road, oval, dirt...)\n");
    fprintf(stderr, "       -n name        : track name\n");
    fprintf(stderr, "       -a             : draw all (default is track only)\n");
    fprintf(stderr, "       -s             : split the track and the terrain\n");
    fprintf(stderr, "       -S             : split all\n");
    fprintf(stderr, "       -e             : save elevation file\n");
    fprintf(stderr, "       -E             : save 2 elevation files\n");
}

void init_args(int argc, char **argv)
{
    int		c;
    
    TrackOnly = 1;
    MergeAll = 1;
    MergeTerrain = 1;
    TrackName = NULL;
    TrackCategory = NULL;
    saveElevation = 0;

#ifndef WIN32
    while (1) {
	int option_index = 0;
	static struct option long_options[] = {
	    {"help", 0, 0, 0},
	    {"version", 1, 0, 0}
	};

	c = getopt_long(argc, argv, "hvn:c:asSeE",
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
	case 'a':
	    TrackOnly = 0;
	    break;
	case 's':
	    MergeAll = 0;
	    MergeTerrain = 1;
	    break;
	case 'S':
	    MergeAll = 0;
	    MergeTerrain = 0;
	    break;
	case 'n':
	    TrackName = strdup(optarg);
	    break;
	case 'c':
	    TrackCategory = strdup(optarg);
	    break;
	case 'e':
	    saveElevation = 1;
	    break;
	case 'E':
	    saveElevation = 2;
	    break;
	default:
	    usage();
	    exit(1);
	    break;
	}
    }
#else
    i = 1;
    while (i < argc) {
	if (strncmp(argv[i], "-h", 2) == 0) {
	    usage();
	    exit(0);
	}
	if (strncmp(argv[i], "-v", 2) == 0) {
	    printf("Terrain generator for tracks $Revision$ \n");
	    exit(0);
	}
	if (strncmp(argv[i], "-a", 2) == 0) {
	    TrackOnly = 0;
	} else if (strncmp(argv[i], "-s", 2) == 0) {
	    MergeAll = 0;
	    MergeTerrain = 1;
	} else if (strncmp(argv[i], "-S", 2) == 0) {
	    MergeAll = 0;
	    MergeTerrain = 0;
	} else if (strncmp(argv[i], "-n", 2) == 0) {
	    if (i + 1 < argc) {
		TrackName = strdup(argv[i++]);
	    } else {
		usage();
		exit(0);
	    }
	} else if (strncmp(argv[i], "-e", 2) == 0) {
	    saveElevation = 1;
	} else if (strncmp(argv[i], "-E", 2) == 0) {
	    saveElevation = 2;
	} else if (strncmp(argv[i], "-c", 2) == 0) {
	    if (i + 1 < argc) {
		TrackCategory = strdup(argv[i++]);
	    } else {
		usage();
		exit(0);
	    }
	} else {
	    usage();
	    exit(0);
	}
	i++;
    }
#endif

    if (!TrackName || !TrackCategory) {
	usage();
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


    glutInit(&argc, argv);
    glutCreateWindow(argv[1]);

    ssgInit();
    
#ifndef WIN32
    LinuxSpecInit();
#else
    WindowsSpecInit();
#endif

    Generate();
    return 0;
}

#ifdef WIN32
#define INSTBASE "./"
#endif

static void
Generate(void)
{
    char	*trackdllname;
    char	*extName;
    FILE	*outfd = NULL;

    /* Get the trackgen paramaters */
    sprintf(buf, "%s/%s", INSTBASE, CFG_FILE);
    CfgHandle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    trackdllname = GfParmGetStr(CfgHandle, "Modules", "track", "track");
    sprintf(buf, "%s/modules/track/%s.%s", INSTBASE, trackdllname, DLLEXT);
    if (GfModLoad(TRK_IDENT, buf, &modlist) < 0) {
	GfFatal("Failed to find the track module %s", buf);
    }
    if (modlist->modInfo->fctInit(modlist->modInfo->index, &TrackItf)) {
	GfFatal("Failed to init the track module %s", buf);
    }

    /* This is the track definition */
    sprintf(trackdef, "tracks/%s/%s/%s.xml", TrackCategory, TrackName, TrackName);
    TrackHandle = GfParmReadFile(trackdef, GFPARM_RMODE_STD);
    if (!TrackHandle) {
	fprintf(stderr, "Cannot find %s\n", trackdef);
	exit(1);
    }

    /* build the track structure with graphic extensions */
    Track = TrackItf.trkBuildEx(trackdef);

    /* Get the output file radix */
    sprintf(buf2, "tracks/%s/%s/%s", Track->category, Track->internalname, Track->internalname);
    OutputFileName = strdup(buf2);

    /* Number of goups for the complete track */
    if (TrackOnly) {
	sprintf(buf2, "%s.ac", OutputFileName);
	/* track */
	outfd = Ac3dOpen(buf2, 1);
    } else if (MergeAll) {
	sprintf(buf2, "%s.ac", OutputFileName);
	/* track + terrain + objects */
	outfd = Ac3dOpen(buf2, 2 + GetObjectsNb(TrackHandle));
    }

    /* Main Track */
    extName = "trk";
    sprintf(buf2, "%s-%s.ac", OutputFileName, extName);
    OutTrackName = strdup(buf2);

    GenerateTrack(Track, TrackHandle, OutTrackName, outfd);

    if (TrackOnly) {
	return;
    }
    
    /* Terrain */
    if (MergeTerrain && !MergeAll) {
	sprintf(buf2, "%s.ac", OutputFileName);
	/* terrain + objects  */
	outfd = Ac3dOpen(buf2, 1 + GetObjectsNb(TrackHandle));
    }

    extName = "msh";
    sprintf(buf2, "%s-%s.ac", OutputFileName, extName);
    OutMeshName = strdup(buf2);
    
    GenerateTerrain(Track, TrackHandle, OutMeshName, outfd, saveElevation);

    if (saveElevation) {
	Ac3dClose(outfd);
	sprintf(buf2, "%s.ac", OutputFileName);
	sprintf(buf, "%s-elv.png", OutputFileName);
	SaveElevation(Track, TrackHandle, buf, buf2);
	if (saveElevation == 2) {
	    sprintf(buf, "%s-elv2.png", OutputFileName);
	    SaveElevation(Track, TrackHandle, buf, OutMeshName);
	}
	return;
    }
    
    GenerateObjects(Track, TrackHandle, CfgHandle, outfd);
}
