/***************************************************************************

    file                 : car.h
    created              : Sun Jan 30 12:00:15 CET 2000
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
 

#ifndef __CARV1_H__
#define __CARV1_H__

#include <ttypes.h>
#include <track.h>

#include <plib/sg.h>

#define CAR_IDENT	((0x01)<<CAR_IDENT_SHIFT)

typedef struct
{
    tdble	rimRadius;
    tdble	tireHeight;
    tdble	tireWidth;
    tdble	brakeDiskRadius;
    tdble	wheelRadius;
} tWheelSpec;
#define _rimRadius(i) info->wheel[i].rimRadius
#define _tireHeight(i) info->wheel[i].tireHeight
#define _tireWidth(i) info->wheel[i].tireWidth
#define _brakeDiskRadius(i) info->wheel[i].brakeDiskRadius
#define _wheelRadius(i) info->wheel[i].wheelRadius


/* Static Public info */
typedef struct {
    char	*name;	    	/* driver's name */
    char	*carName;	/* car object name */
    char	*category;	/* car's category */
    int		raceNumber;	/* car's race number */
    tdble	iconColor[3];	/* car color in leaders board */
    t3Dd	dimension;	/* car's mesures */
    t3Dd	drvPos;		/* driver's position */
    tdble	tank;		/* fuel tank capa */
    tdble	steerLock;
    t3Dd	statGC;		/* static pos of GC (should be the origin of car axis) */
    tWheelSpec	wheel[4];	/* wheels specif */
} tInitCar;
/* structure access */
#define _name		info->name
#define _carName	info->carName
#define _category	info->cartegory
#define _raceNumber	info->raceNumber
#define _dimension	info->dimension
#define _dimension_x	info->dimension.x
#define _dimension_y	info->dimension.y
#define _dimension_z	info->dimension.z
#define _drvPos_x	info->drvPos.x
#define _drvPos_y	info->drvPos.y
#define _drvPos_z	info->drvPos.z
#define _statGC		info->statGC
#define _statGC_x	info->statGC.x
#define _statGC_y	info->statGC.y
#define _statGC_z	info->statGC.z
#define _iconColor	info->iconColor
#define _tank		info->tank
#define _steerLock	info->steerLock

/* Race Administrative info */
typedef struct {
    double	bestLapTime;
    double	deltaBestLapTime;
    double	curLapTime;
    double	lastLapTime;
    double	curTime;
    tdble	topSpeed;
    int		laps;
    int		remainingLaps;
    int		pos;
    double	timeBehindLeader;
    int		lapsBehindLeader;
    double	timeBehindPrev;
    double	timeBeforeNext;
    tdble	distRaced;
    tdble	distFromStartLine;
    double	scheduledEventTime;
    tTrackOwnPit *pit;
} tCarRaceInfo;
/* structure access */
#define _bestLapTime		race->bestLapTime
#define _deltaBestLapTime	race->deltaBestLapTime
#define _curLapTime		race->curLapTime
#define _curTime		race->curTime
#define _lastLapTime		race->lastLapTime
#define _topSpeed		race->topSpeed
#define _laps			race->laps
#define _remainingLaps		race->remainingLaps
#define _pos			race->pos
#define _timeBehindLeader	race->timeBehindLeader
#define _lapsBehindLeader	race->lapsBehindLeader
#define _timeBehindPrev		race->timeBehindPrev
#define _timeBeforeNext		race->timeBeforeNext
#define _distRaced		race->distRaced
#define _distFromStartLine	race->distFromStartLine
#define _pit			race->pit
#define _scheduledEventTime	race->scheduledEventTime

/* public info on the cars */
typedef struct {
    tDynPt	DynGC;		/* GC data (car axis) */    
    tDynPt	DynGCg;		/* GC data (world axis) */    
    sgMat4	posMat;		/* position matrix */
    tTrkLocPos	trkPos;		/* current track position */
    int		state;	    	/* state of the car */
    tPosd	corner[4];
#define RM_CAR_STATE_FINISH	 0x00000100				/* Car having passed the finish line */
#define RM_CAR_STATE_PIT	 0x00000001				/* Car currently stopped in pits */
#define RM_CAR_STATE_DNF	 0x00000002				/* Car did not finish */
#define RM_CAR_STATE_PULLUP	 0x00000004				/* Car pulled out in the air */
#define RM_CAR_STATE_PULLSIDE	 0x00000008				/* Car pulled out in the air */
#define RM_CAR_STATE_PULLDN	 0x00000010				/* Car pulled out in the air */
#define RM_CAR_STATE_OUT	(RM_CAR_STATE_DNF | RM_CAR_STATE_FINISH)/* Car out of race */
#define RM_CAR_STATE_NO_SIMU	 0x000000FF				/* Do not simulate the car */
#define RM_CAR_STATE_BROKEN	 0x00000200				/* Engine no more working */

} tPublicCar;
/* structure access */
#define _DynGC		pub->DynGC
#define _pos_X		pub->DynGC.pos.x
#define _pos_Y		pub->DynGC.pos.y
#define _pos_Z		pub->DynGC.pos.z
#define _roll		pub->DynGC.pos.ax
#define _pitch		pub->DynGC.pos.ay
#define _yaw		pub->DynGC.pos.az
#define _yaw_rate	pub->DynGC.vel.az
#define _speed_x	pub->DynGC.vel.x
#define _speed_y	pub->DynGC.vel.y
#define _speed_z	pub->DynGC.vel.z
#define _accel_x	pub->DynGC.acc.x
#define _accel_y	pub->DynGC.acc.y
#define _accel_z	pub->DynGC.acc.z
#define _state		pub->state
#define _trkPos		pub->trkPos
#define _speed_X	pub->DynGCg.vel.x
#define _speed_Y	pub->DynGCg.vel.y
#define _corner_x(i)	pub->corner[i].ax
#define _corner_y(i)	pub->corner[i].ay
#define _posMat		pub->posMat

typedef struct {
    tPosd	relPos;		/* position relative to GC */
    tdble	spinVel;	/* spin velocity rad/s */
    tdble	brakeTemp;	/* brake temperature from 0 (cool) to 1.0 (hot) */
    int		state;		/* wheel state */
} tWheelState;
#define _ride(i)	priv->wheel[i].relPos.z
#define _brakeTemp(i)	priv->wheel[i].brakeTemp
#define _wheelSpinVel(i) priv->wheel[i].spinVel

typedef struct 
{
    int		type;
#define CAR_VECT_INVALID	0
#define CAR_VECT_ABSOLUTE	1
#define CAR_VECT_RELATIVE	2
    t3Dd	start;
    t3Dd	end;
    float	color[3];
} tDebugVect;

#define CAR_NVECT	24	/* the first 12 are for user, the others are for simu */
#define MAX_GEARS	10	/* including reverse and neutral */

/* data known only by the driver */
typedef struct {
    void	*paramsHandle;	/* accessible parameters for modules */
    void	*carHandle;	/* parameters for car caracteristics */
    int		driverIndex;	/* index when multiple drivers are in the same dll */
    char	*modName;	/* dll name */
    tWheelState	wheel[4];
    tPosd	corner[4];	/* car's corners position */
    int		gear;	    	/* current gear */
    tdble	fuel;	    	/* remaining fuel (liters) */
    tdble	enginerpm;
    tdble	enginerpmRedLine;
    tdble	enginerpmMax;
    tdble	gearRatio[MAX_GEARS];	/* including final drive */
    int		gearNb;			/* incl reverse and neutral */
    int		gearOffset;		/* gearRatio[gear + gearOffset] is the ratio for gear */

    tdble	skid[4];		/* skid intensity */
    int		collision;
    t3Dd	normal;
    t3Dd	collpos;
    int		dammage;
    int		debug;
    tDebugVect	vect[CAR_NVECT];
} tPrivCar;
/* structure access */
#define _driverIndex	priv->driverIndex
#define _paramsHandle	priv->paramsHandle
#define _carHandle	priv->carHandle
#define _modName	priv->modName
#define _enginerpm	priv->enginerpm
#define _enginerpmRedLine	priv->enginerpmRedLine
#define _enginerpmMax	priv->enginerpmMax
#define _gearRatio	priv->gearRatio
#define _gearNb		priv->gearNb
#define _gearOffset	priv->gearOffset
#define _fuel		priv->fuel
#define _gear		priv->gear
#define _debug		priv->debug
#define _vect(i)	priv->vect[i]
#define _skid		priv->skid
#define _dammage	priv->dammage

/* Info returned by driver during the race */
typedef struct {
    tdble	steer;	    /* Steer command [-1.0, 1.0]  */
    tdble	accelCmd;   /* Accelerator command [0.0, 1.0] */
    tdble	brakeCmd;   /* Brake command [0.0, 1.0] */
    int		gear;  	    /* [-1,6] for gear selection */
    int		raceCmd;    /* command issued by the driver */
#define RM_CMD_NONE		0
#define RM_CMD_PIT_ASKED	1
    char	*msg[4];     /* 4 lines of 12 characters from car */
    float	msgColor[4]; /* RGBA of text */
} tCarCtrl;

struct RobotItf;

typedef struct 
{
    tdble		fuel;
    int			repair;
} tCarPitCmd;

/* Element of list of car info */
typedef struct CarElt
{
    int			index;	/* car index */
    tInitCar		*info;	/* public */
    tPublicCar		*pub;	/* public */
    tCarRaceInfo	*race;	/* public */
    tPrivCar		*priv;	/* private */
    tCarCtrl		*ctrl;	/* private */
    tCarPitCmd		*pitcmd;/* private */
    struct RobotItf	*robot; /* private */
    struct CarElt	*next;
} tCarElt;



/* sections in xml description files */

#define SECT_CAR		"Car"
#define SECT_FRNT		"Front"
#define SECT_FRNTWING		"Front Wing"
#define SECT_FRNTAXLE		"Front Axle"
#define SECT_FRNTARB		"Front Anti-Roll Bar"
#define SECT_FRNTRGTWHEEL	"Front Right Wheel"
#define SECT_FRNTLFTWHEEL	"Front Left Wheel"
#define SECT_FRNTRGTSUSP	"Front Right Suspension"
#define SECT_FRNTLFTSUSP	"Front Left Suspension"
#define SECT_FRNTRGTBRAKE	"Front Right Brake"
#define SECT_FRNTLFTBRAKE	"Front Left Brake"
#define SECT_FRNTDIFFERENTIAL	"Front Differential"
#define SECT_REAR		"Rear"
#define SECT_REARWING		"Rear Wing"
#define SECT_REARAXLE		"Rear Axle"
#define SECT_REARARB		"Rear Anti-Roll Bar"
#define SECT_REARRGTWHEEL	"Rear Right Wheel"
#define SECT_REARLFTWHEEL	"Rear Left Wheel"
#define SECT_REARRGTSUSP	"Rear Right Suspension"
#define SECT_REARLFTSUSP	"Rear Left Suspension"
#define SECT_REARRGTBRAKE	"Rear Right Brake"
#define SECT_REARLFTBRAKE	"Rear Left Brake"
#define SECT_REARDIFFERENTIAL	"Rear Differential"
#define SECT_CENTRALDIFFERENTIAL	"Central Differential"
#define SECT_STEER		"Steer"
#define SECT_BRKSYST		"Brake System"
#define SECT_AERODYNAMICS	"Aerodynamics"
#define SECT_ENGINE		"Engine"
#define SECT_CLUTCH		"Clutch"
#define SECT_DRIVETRAIN		"Drivetrain"
#define SECT_GEARBOX		"Gearbox"
#define SECT_DRIVER		"Driver"
#define SECT_GROBJECTS		"Graphic Objects"

/* parameters names */
#define PRM_CATEGORY		"category"
#define PRM_LEN			"body length"
#define PRM_WIDTH		"body width"
#define PRM_OVERALLLEN		"overall length"
#define PRM_OVERALLWIDTH	"overall width"
#define PRM_HEIGHT		"body height"
#define PRM_MASS		"mass"
#define PRM_FRWEIGHTREP		"front-rear weight repartition"
#define PRM_FRLWEIGHTREP	"front right-left weight repartition"
#define PRM_RRLWEIGHTREP	"rear right-left weight repartition"
#define PRM_GCHEIGHT		"GC height"
#define PRM_TANK		"fuel tank"
#define PRM_FUEL		"initial fuel"
#define PRM_CENTR		"mass repartition coefficient"
#define PRM_INERTIA		"inertia"
#define PRM_EFFICIENCY		"efficiency"
#define PRM_TYPE		"type"

/* Tires */
#define PRM_MU			"mu"
#define PRM_RIMDIAM		"rim diameter"
#define PRM_TIREWIDTH		"tire width"
#define PRM_TIRERATIO		"tire height-width ratio"
#define PRM_RIDEHEIGHT		"ride height"
#define PRM_ROLLINGRESIST	"rolling resistance"
#define PRM_TOE			"toe"
#define PRM_CAMBER		"camber"
#define PRM_CA			"stiffness"
#define PRM_RFACTOR		"dynamic friction"
#define PRM_EFACTOR		"elasticity factor"
#define PRM_PRESSURE		"pressure"
#define PRM_LOADFMAX		"load factor max"
#define PRM_LOADFMIN		"load factor min"
#define PRM_OPLOAD		"operating load"


#define PRM_SPR			"spring"
#define PRM_SUSPCOURSE		"suspension course"
#define PRM_BELLCRANK		"bellcrank"
#define PRM_PACKERS		"packers"
#define PRM_SLOWBUMP		"slow bump"
#define PRM_SLOWREBOUND		"slow rebound"
#define PRM_FASTBUMP		"fast bump"
#define PRM_FASTREBOUND		"fast rebound"

#define PRM_XPOS		"xpos"
#define PRM_YPOS		"ypos"
#define PRM_ZPOS		"zpos"

#define PRM_STEERLOCK		"steer lock"
#define PRM_STEERSPD		"max steer speed"

#define PRM_BRKDIAM		"disk diameter"
#define PRM_BRKAREA		"piston area"
#define PRM_BRKREP		"front-rear brake repartition"
#define PRM_BRKPRESS		"max pressure"

#define PRM_CX			"Cx"
#define PRM_CL			"Clift"
#define PRM_FRNTAREA		"front area"
#define PRM_WINGAREA		"area"
#define PRM_WINGANGLE		"angle"

#define PRM_REVSLIM		"revs limiter"
#define PRM_REVSMAX		"revs maxi"
#define PRM_TICKOVER		"tickover"
#define PRM_RPM			"rpm"
#define PRM_TQ			"Tq"
#define ARR_DATAPTS		"data points"
#define PRM_FUELCONS		"fuel cons factor"

#define PRM_RATIO		"ratio"
#define PRM_BIAS		"bias"

#define ARR_GEARS		"gears"
#define PRM_SHIFTTIME		"shift time"

#define	PRM_ROLLCENTER		"roll center height"

#define LST_RANGES		"Ranges"
#define PRM_DISTANCE		"distance"
#define PRM_CAR			"car"
#define PRM_ENV			"env"
#define PRM_BONNET		"bonnet"
#define PRM_WHEEL_TEXTURE	"wheel texture"

#define PRM_MIN_TQ_BIAS		"min torque bias"
#define PRM_MAX_TQ_BIAS		"max torque bias"
#define PRM_MAX_SLIP_BIAS	"max slip bias"
#define PRM_LOCKING_TQ		"locking input torque"
#define PRM_VISCOSITY_FACTOR	"viscosity factor"


#define VAL_DIFF_NONE		"NONE"
#define VAL_DIFF_SPOOL		"SPOOL"
#define VAL_DIFF_FREE		"FREE"
#define VAL_DIFF_LIMITED_SLIP	"LIMITED SLIP"
#define VAL_DIFF_VISCOUS_COUPLER "VISCOUS COUPLER"

#define VAL_TRANS_RWD		"RWD"
#define VAL_TRANS_FWD		"FWD"
#define VAL_TRANS_4WD		"4WD"

#endif /* __CARV1_H__ */ 



