/***************************************************************************

    file                 : track.h
    created              : Sun Jan 30 23:00:06 CET 2000
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
    		This is the track structure.
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
    @ingroup	track
*/
 
#ifndef _TRACKV1_H_
#define _TRACKV1_H_

#include <ttypes.h>

#define TRK_IDENT	((0x01)<<TRK_IDENT_SHIFT)	/* from 0x01 to 0xFF */

#define TRK_SECT_HDR	"Header"

#define TRK_ATT_WIDTH	"width"
#define TRK_ATT_SURF	"surface"
#define TRK_ATT_NAME	"name"
#define TRK_ATT_VERSION	"version"
#define TRK_ATT_AUTHOR	"author"
#define TRK_ATT_DESCR	"description"
#define TRK_ATT_CAT     "category"

#define TRK_SECT_GRAPH	"Graphic"

#define TRK_ATT_3DDESC	"3d description"
#define TRK_ATT_BKGRND	"background image"
#define TRK_ATT_BKGRND2	"background image2"
#define TRK_ATT_BGTYPE	"background type"
#define TRK_ATT_BGCLR_R	"background color R"
#define TRK_ATT_BGCLR_G	"background color G"
#define TRK_ATT_BGCLR_B	"background color B"
#define TRK_LST_ENV	"Environment Mapping"
#define TRK_ATT_ENVNAME	"env map image"
#define TRK_ATT_SPEC_R	"specular color R"
#define TRK_ATT_SPEC_G	"specular color G"
#define TRK_ATT_SPEC_B	"specular color B"
#define TRK_ATT_AMBIENT_R	"ambient color R"
#define TRK_ATT_AMBIENT_G	"ambient color G"
#define TRK_ATT_AMBIENT_B	"ambient color B"
#define TRK_ATT_SHIN	"shininess"
#define TRK_ATT_LIPOS_X	"light position x"
#define TRK_ATT_LIPOS_Y	"light position y"
#define TRK_ATT_LIPOS_Z	"light position z"

#define TRK_SECT_TURNMARKS "Graphic/Turn Marks"
#define TRK_ATT_HSPACE	"horizontal space"
#define TRK_ATT_VSPACE	"vertical space"

#define TRK_SECT_TERRAIN  "Graphic/Terrain Generation"

#define TRK_ATT_TSTEP	"track step"
#define TRK_ATT_BMARGIN	"border margin"
#define TRK_ATT_BSTEP	"border step"
#define TRK_ATT_BHEIGHT	"border height"
#define TRK_ATT_ORIENT	"orientation"
#define TRK_VAL_CLOCK	"clockwise"
#define TRK_VAL_CCLOCK	"counter-clockwise"
#define TRK_ATT_RELIEF	"relief file"

#define TRK_SECT_SURFACES "Surfaces"

#define TRK_ATT_FRICTION "friction"
#define TRK_ATT_ROLLRES  "rolling resistance"
#define TRK_ATT_ROUGHT   "roughness"
#define TRK_ATT_ROUGHTWL "roughness wavelength"
#define TRK_ATT_DAMMAGE  "dammage"
#define TRK_ATT_REBOUND  "rebound"
#define TRK_ATT_TEXTURE  "texture name"
#define TRK_ATT_TEXTYPE  "texture type"
#define TRK_ATT_TEXLINK  "texture link with previous"
#define TRK_ATT_TEXSIZE  "texture size"
#define TRK_ATT_TEXSTARTBOUNDARY "texture start on boundary"
#define TRK_ATT_TEXMIPMAP "texture mipmap"
#define TRK_ATT_R1	 "color R1"
#define TRK_ATT_G1	 "color G1"
#define TRK_ATT_B1	 "color B1"
#define TRK_ATT_R2	 "color R2"
#define TRK_ATT_G2	 "color G2"
#define TRK_ATT_B2	 "color B2"

#define TRK_ATT_STEPLEN	"steps length"

#define TRK_VAL_YES	"yes"
#define TRK_VAL_NO	"no"

#define TRK_SECT_MAIN	"Main Track"
#define TRK_LST_SEGMENTS	"Track Segments"
#define TRK_ATT_TYPE		"type"

#define TRK_VAL_STR		"str"
#define TRK_VAL_LFT		"lft"
#define TRK_VAL_RGT		"rgt"

#define TRK_ATT_LG		"lg"
#define TRK_ATT_RADIUS		"radius"
#define TRK_ATT_RADIUSEND	"end radius"
#define TRK_ATT_ARC		"arc"
#define TRK_ATT_ZS		"z start"
#define TRK_ATT_ZE		"z end"
#define TRK_ATT_ZSL		"z start left"
#define TRK_ATT_ZSR		"z start right"
#define TRK_ATT_ZEL		"z end left"
#define TRK_ATT_ZER		"z end right"
#define TRK_ATT_GRADE		"grade"
#define TRK_ATT_BKS		"banking start"
#define TRK_ATT_BKE		"banking end"
#define TRK_ATT_ID		"id"
#define TRK_ATT_PROFIL		"profil"
#define TRK_ATT_PROFSTEPS	"profil steps"
#define TRK_ATT_PROFSTEPSLEN	"profil steps length"
#define TRK_ATT_PROFTGTS	"profil start tangent"
#define TRK_ATT_PROFTGTE	"profil end tangent"
#define TRK_ATT_PROFTGTSL	"profil start tangent left"
#define TRK_ATT_PROFTGTEL	"profil end tangent left"
#define TRK_ATT_PROFTGTSR	"profil start tangent right"
#define TRK_ATT_PROFTGTER	"profil end tangent right"
#define TRK_ATT_MARKS		"marks"
#define TRK_ATT_ENVMAP		"env map"

#define TRK_SECT_PITS		"Pits"

#define TRK_ATT_ENTRY		"entry"
#define TRK_ATT_EXIT		"exit"
#define TRK_ATT_START		"start"
#define TRK_ATT_END		"end"
#define TRK_ATT_SIDE		"side"
#define TRK_ATT_LEN		"length"

#define TRK_SECT_LSIDE		"Left Side"
#define TRK_SECT_RSIDE		"Right Side"
#define TRK_SECT_LBORDER	"Left Border"
#define TRK_SECT_RBORDER	"Right Border"
#define TRK_SECT_LBARRIER	"Left Barrier"
#define TRK_SECT_RBARRIER	"Right Barrier"

#define TRK_ATT_SWIDTH		"start width"
#define TRK_ATT_EWIDTH		"end width"
#define TRK_ATT_STYLE		"style"
#define TRK_ATT_HEIGHT		"height"
#define TRK_ATT_BANKTYPE	"banking type"

#define TRK_VAL_PLAN		"plan"
#define TRK_VAL_WALL		"wall"
#define TRK_VAL_CURB		"curb"
#define TRK_VAL_FENCE		"fence"


#define TRK_SECT_CAM		"Cameras"

#define TRK_ATT_SEGMENT		"segment"
#define TRK_ATT_TORIGHT 	"to right"
#define TRK_ATT_TOSTART 	"to start"
#define TRK_ATT_HEIGHT  	"height"
#define TRK_ATT_CAM_FOV 	"fov start"
#define TRK_ATT_CAM_FOVE 	"fov end"

#define TRK_VAL_ASPHALT		"asphalt"
#define TRK_VAL_CONCRETE	"concrete"
#define TRK_VAL_GRASS		"grass"
#define TRK_VAL_SAND		"sand"
#define TRK_VAL_DIRT		"dirt"
#define TRK_VAL_BARRIER		"barrier"

#define TRK_VAL_LINEAR		"linear"
#define TRK_VAL_SPLINE		"spline"

#define TRK_VAL_TANGENT		"tangent"
#define TRK_VAL_LEVEL		"level"

/** road camera */
typedef struct RoadCam
{
    char		*name;
    t3Dd		pos;
    struct RoadCam	*next;
} tRoadCam;

/** Extended track segment */
typedef struct SegExt
{
    /** turn marks */
    int		nbMarks;
    /** marks array */
    int		*marks;  
} tSegExt;


/** Surface */
typedef struct trackSurface {
    struct trackSurface *next;
    
    char *material;	/* type of material used */

    tdble kFriction;	/* coefficient of friction */
    tdble kRebound;	/* coefficient of energy restitution */
    tdble kRollRes;	/* rolling resistance */
    tdble kRoughness;
    tdble kRoughWaveLen;
    tdble kDammage;
} tTrackSurface;



/** Barrier */
typedef struct trackBarrier {
    /** barrier style */
    int			style;
    tdble		width;
    tdble		height;
    tTrackSurface	*surface;
} tTrackBarrier;


/** Track segment */
typedef struct trackSeg {
    char *name;
    /** segment number */
    int	id;

    /** Geometry */
    /** geometrical type */
    int type;	   
    /** right curve */     
#define TR_RGT	    1
    /** left curve */
#define TR_LFT	    2
    /** straight */
#define TR_STR	    3

    /** position type */
    int type2;
#define TR_MAIN	    1
#define TR_LSIDE    2
#define TR_RSIDE    3
#define TR_LBORDER  4
#define TR_RBORDER  5

    /** segment style */
    int style;
#define TR_PLAN		0	/* border only */
#define TR_CURB		1	/* border only */
#define TR_WALL		2
#define TR_FENCE	3	/* barrier only */
#define TR_PITBUILDING	4	/* barrier only */

    /** length in meters of the middle of the track */
    tdble length;
    tdble width;
    tdble startWidth;
    tdble endWidth;
    tdble lgfromstart;  /* length of begining of segment from starting line (logical not real) */
    tdble radius;	/* radius in meters of the middle of the track (>0) */
    tdble radiusr;	/* radius in meters of the right side of the track (>0) */
    tdble radiusl;	/* radius in meters of the left side of the track (>0) */
    tdble arc;	        /* arc in rad of the curve (>0) */
    t3Dd center;	/* center of the curve */
    t3Dd vertex[4];	/* coord of the 4 corners of the segment */
#define TR_SL	0	/* Start-Left corner */
#define TR_SR	1	/* Start-Right corner */
#define TR_EL	2	/* End-Left corner */
#define TR_ER	3	/* End_Right corner */

    tdble angle[7];	/* rotation angles of the track in rad anti-clockwise */
#define TR_ZS	0	/* Z Start angle */
#define TR_ZE	1	/* Z End angle */
#define TR_YL	2	/* Y Left angle */
#define TR_YR	3	/* Y Right angle */
#define TR_XS	4	/* X Start angle */
#define TR_XE	5	/* X End angle */
#define TR_CS   6       /* Center start angle */
    /* constants used to find the height of a point */
    tdble Kzl;          /* long constant */
    tdble Kzw;          /* width constant */
    /* constant used to find the width of a segment */
    tdble Kyl;		/* find y along x */
    
    t3Dd rgtSideNormal;   /* normal to the right side in case of straight segment */

    tdble height;	/* for walls, curbs and barriers */

    int		envIndex;	/* Environment mapping image index */

    /* Type of segment regarding the race */
    unsigned int    raceInfo;
#define TR_NORMAL	0x00000000	/* normal segment */
#define TR_LAST		0x00000001	/* segment before start line */
#define TR_START	0x00000002	/* segment after start line */
#define TR_PITLANE	0x00000004	/* pit lane segment */
#define TR_SPEEDLIMIT	0x00000008	/* segment where the speed is limited */
#define TR_PITENTRY	0x00000010	/* segment where the pit lane cross the main track */
#define TR_PITEXIT	0x00000020	/* segment where the pit lane cross the main track */
#define TR_PIT		0x00000040	/* car pit */

    /* optionnal extensions */
    tSegExt		*ext;

    /* pointers */
    tTrackSurface	*surface; /* segment surface */
    tTrackBarrier	*barrier[2];
    tRoadCam        *cam;   /* current camera */
    struct trackSeg *next;  /* next segment */
    struct trackSeg *prev;  /* previous segment */
    struct trackSeg *lside; /* left side */
    struct trackSeg *rside; /* right side */
} tTrackSeg;

/* selection for local position structure */
#define TR_TORIGHT	0
#define TR_TOMIDDLE	1
#define TR_TOLEFT	2

/** Location on the track in local coordinates */
typedef struct
{
    /** Track segment */
    tTrackSeg	*seg;
    int		type;
    /** Relative to the main segment 
	@see	tTrkLocPos
     */
#define TR_LPOS_MAIN	0
    /** If the point is on a side, relative to this side 
	@see	tTrkLocPos
     */
#define TR_LPOS_SEGMENT	1
    /** Local pos includes all the track width 
	@see	tTrkLocPos
     */
#define TR_LPOS_TRACK	2

    /** Distance to start of segment (or arc if turn) */
    tdble	toStart;
    /** Distance to right side of segment (+ to inside of track - to outside) */
    tdble	toRight;
    /** Distance to middle of segment (+ to left - to right) */
    tdble	toMiddle;
    /** Distance to left side of segment (+ to inside of track - to outside) */
    tdble	toLeft;
} tTrkLocPos;

struct CarElt;

/** Driver's pit */
typedef struct TrackOwnPit
{
    /** Center of the pit position */
    tTrkLocPos		pos;
    int			state;
#define TR_PIT_STATE_FREE	0
#define TR_PIT_STATE_USED	1
#define TR_PIT_STATE_ASKED	2
    struct CarElt	*car;
} tTrackOwnPit;

/** Pits Info Structure */
typedef struct 
{
    int		type;
#define TR_PIT_NONE		0
#define TR_PIT_ON_TRACK_SIDE	1
#define TR_PIT_ON_SEPARATE_PATH	2
    /** number max of pits */
    int		nMaxPits;
    /** actual number of pits */
    int		nPitSeg;
    /** TR_RGT or TR_LFT */
    int		side;			
    tdble	len;
    tdble	width;
    /** Pit lane */
    tTrackSeg	*pitEntry;
    tTrackSeg	*pitExit;
    tTrackSeg	*pitStart;
    tTrackSeg	*pitEnd;
    tTrackOwnPit *driversPits;
    int		driversPitsNb;
} tTrackPitInfo;

typedef struct
{
    tdble	height;
    tdble	width;
    tdble	hSpace;
    tdble	vSpace;
} tTurnMarksInfo;

typedef struct 
{
    char		*background;
    char		*background2;
    int			bgtype;
    float		bgColor[3];
    int			envnb;
    char		**env;
    tTurnMarksInfo	turnMarksInfo;
} tTrackGraphicInfo;

/** Track structure */
typedef struct
{
    /** Name of the track */
    char		*name;
    /** Author's name */
    char		*author;
    /** Filename of the track description */
    char		*filename;
    /** Internal name of the track */
    char		*internalname;
    /** Category of the track */
    char		*category;
    /** Number of segments */
    int			nseg;
    /** Version of the track type */
    int			version;
    /** main track length */
    tdble		length;
    /** main track width */
    tdble		width;
    /** Pits information */
    tTrackPitInfo	pits;
    
    /** Main track */
    tTrackSeg		*seg;
    tTrackSurface	*surfaces; /* segment surface list */

    t3Dd		min;
    t3Dd		max;
    tTrackGraphicInfo	graphic;
} tTrack;



typedef tTrack*(*tfTrackBuild)(char*);
typedef tdble(*tfTrackHeightG)(tTrackSeg*, tdble, tdble);
typedef tdble(*tfTrackHeightL)(tTrkLocPos*);
typedef void(*tfTrackGlobal2Local)(tTrackSeg* /*seg*/, tdble /*X*/, tdble /*Y*/, tTrkLocPos* /*pos*/, int /*sides*/);
typedef void(*tfTrackLocal2Global)(tTrkLocPos*, tdble *, tdble *);
typedef void(*tfTrackSideNormal)(tTrackSeg*, tdble, tdble, int, t3Dd*);
typedef void(*tfTrackSurfaceNormal)(tTrkLocPos *, t3Dd*);
typedef void(*tfTrackShutdown)(void);

typedef struct {
    tfTrackBuild		trkBuild;		/* build track structure for simu */
    tfTrackBuild		trkBuildEx;		/* build with graphic extensions  */
    tfTrackHeightG		trkHeightG;
    tfTrackHeightL		trkHeightL;
    tfTrackGlobal2Local		trkGlobal2Local;
    tfTrackLocal2Global		trkLocal2Global;
    tfTrackSideNormal   	trkSideNormal;
    tfTrackSurfaceNormal	trkSurfaceNormal;
    tfTrackShutdown		trkShutdown;
} tTrackItf;


/* For Type 3 tracks (now obsolete) */

#define TRK_LST_SURF			"List"
#define TRK_LST_CAM			"list"
#define TRK_ATT_PIT_ENTRY		"pit entry"
#define TRK_ATT_PIT_EXIT		"pit exit"
#define TRK_ATT_PIT_START		"pit start"
#define TRK_ATT_PIT_END			"pit end"
#define TRK_ATT_PIT_TYPE		"pit type"
#define TRK_ATT_PIT_SIDE		"pit side"
#define TRK_ATT_PIT_LEN			"pit length"
#define TRK_ATT_PIT_WIDTH		"pit width"

#define TRK_LST_SEG	"segments"
#define TRK_ATT_ENVIND	"env map index"


#define TRK_ATT_LST	"lside type"
#define TRK_ATT_LSW	"lside width"
#define TRK_ATT_LSWS	"lside start width"
#define TRK_ATT_LSWE	"lside end width"
#define TRK_ATT_LSSURF	"lside surface"
#define TRK_ATT_RST	"rside type"
#define TRK_ATT_RSW	"rside width"
#define TRK_ATT_RSWS	"rside start width"
#define TRK_ATT_RSWE	"rside end width"
#define TRK_ATT_RSSURF	"rside surface"
#define TRK_ATT_LBS	"lborder style"
#define TRK_ATT_LBW	"lborder width"
#define TRK_ATT_LBH	"lborder height"
#define TRK_ATT_LBSURF	"lborder surface"
#define TRK_ATT_RBS	"rborder style"
#define TRK_ATT_RBW	"rborder width"
#define TRK_ATT_RBH	"rborder height"
#define TRK_ATT_RBSURF	"rborder surface"

#define TRK_ATT_LBAS	"lbarrier style"
#define TRK_ATT_LBAW	"lbarrier width"
#define TRK_ATT_LBAH	"lbarrier height"
#define TRK_ATT_LBAFRCT	"lbarrier friction"
#define TRK_ATT_LBASURF	"lbarrier surface"
#define TRK_ATT_RBAS	"rbarrier style"
#define TRK_ATT_RBAW	"rbarrier width"
#define TRK_ATT_RBAH	"rbarrier height"
#define TRK_ATT_LBAFRCT	"lbarrier friction"
#define TRK_ATT_RBASURF	"rbarrier surface"

#define TRK_VAL_PIT_TYPE_NONE		"no pit"
#define TRK_VAL_PIT_TYPE_SIDE		"track side"
#define TRK_VAL_PIT_TYPE_SEP_PATH	"seperate path"

#define TRK_ATT_FINISH	"finish segment"

#endif /* _TRACKV1_H_ */ 



