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

/** @file
    		This is the car structure.
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
    @ingroup	carstruct
    @note	Short cuts are to be used with the carElt structure.
*/


#ifndef __CARV1_H__
#define __CARV1_H__

#include <track.h>
#include <plib/sg.h>

#define CAR_IDENT	0

#define MAX_NAME_LEN	32

/* designation */
#define FRNT_RGT	0	/**< front right */
#define FRNT_LFT	1	/**< front left */
#define REAR_RGT	2	/**< rear right */
#define REAR_LFT	3	/**< rear left */
#define FRNT		0	/**< front */
#define REAR		1	/**< rear */
#define RIGHT		0	/**< right */
#define LEFT		1	/**< left */


/** Wheels Specifications */
typedef struct
{
    tdble	rimRadius;	/**< Rim radius */
    tdble	tireHeight;	/**< Tire height  */
    tdble	tireWidth;	/**< Tire width */
    tdble	brakeDiskRadius; /**< Brake disk radius */
    tdble	wheelRadius;	/**< Overall wheel radius */
} tWheelSpec;
/* structure access short cuts */
#define _rimRadius(i)		info.wheel[i].rimRadius 			/**< short cut to tWheelSpec#rimRadius */
#define _tireHeight(i)		info.wheel[i].tireHeight		/**< short cut to tWheelSpec#tireHeight */
#define _tireWidth(i)		info.wheel[i].tireWidth			/**< short cut to tWheelSpec#tireWidth */
#define _brakeDiskRadius(i)	info.wheel[i].brakeDiskRadius	/**< short cut to tWheelSpec#brakeDiskRadius */
#define _wheelRadius(i)		info.wheel[i].wheelRadius		/**< short cut to tWheelSpec#wheelRadius */

/** Static visual attributes */
typedef struct {
    int		exhaustNb;	/**< Number of exhaust pipes (max 2) */
    t3Dd	exhaustPos[2];	/**< Position of exhaust pipes */
    tdble	exhaustPower;	/**< Power of the flames (from 1 to 3) */
} tVisualAttributes;

/** Static Public info */
typedef struct {
    char	name[MAX_NAME_LEN];	/**< Driver's name */
    char	carName[MAX_NAME_LEN];	/**< Car object name */
    char	category[MAX_NAME_LEN];	/**< Car's category */
    int		raceNumber;		/**< Car's race number */
    int		startRank;		/**< Car's starting position */
    int		driverType;		/**< Driver type */
    int		skillLevel;		/**< Driver's skill level (0=rookie -> 3=pro) */
    tdble	iconColor[3];		/**< Car color in leaders board */
    t3Dd	dimension;		/**< Car's mesures */
    t3Dd	drvPos;			/**< Driver's position */
    tdble	tank;			/**< Fuel tank capa */
    tdble	steerLock;		/**< Steer lock angle */
    t3Dd	statGC;			/**< Static pos of GC (should be the origin of car axis) */
    tWheelSpec	wheel[4];		/**< Wheels specifications */
    tVisualAttributes visualAttr; 	/**< Visual attributes */
} tInitCar;
/* structure access short cuts */
#define _name		info.name			/**< short cut to tInitCar#name */
#define _carName	info.carName			/**< short cut to tInitCar#carName */
#define _category	info.cartegory			/**< short cut to tInitCar#cartegory */
#define _driverType	info.driverType			/**< short cut to tInitCar#driverType */
#define _skillLevel	info.skillLevel			/**< short cut to tInitCar#skillLevel */
#define _raceNumber	info.raceNumber			/**< short cut to tInitCar#raceNumber */
#define _startRank	info.startRank			/**< short cut to tInitCar#startRank */
#define _dimension	info.dimension			/**< short cut to tInitCar#dimension */
#define _dimension_x	info.dimension.x		/**< short cut to tInitCar#dimension.x */
#define _dimension_y	info.dimension.y		/**< short cut to tInitCar#dimension.y */
#define _dimension_z	info.dimension.z		/**< short cut to tInitCar#dimension.z */
#define _drvPos_x	info.drvPos.x			/**< short cut to tInitCar#drvPos.x */
#define _drvPos_y	info.drvPos.y			/**< short cut to tInitCar#drvPos.y */
#define _drvPos_z	info.drvPos.z			/**< short cut to tInitCar#drvPos.z */
#define _statGC		info.statGC			/**< short cut to tInitCar#statGC */
#define _statGC_x	info.statGC.x			/**< short cut to tInitCar#statGC.x */
#define _statGC_y	info.statGC.y			/**< short cut to tInitCar#statGC.y */
#define _statGC_z	info.statGC.z			/**< short cut to tInitCar#statGC.z */
#define _iconColor	info.iconColor			/**< short cut to tInitCar#iconColor */
#define _tank		info.tank			/**< short cut to tInitCar#tank */
#define _steerLock	info.steerLock			/**< short cut to tInitCar#steerLock */
#define _exhaustNb	info.visualAttr.exhaustNb	/**< short cut to tVisualAttributes#exhaustNb */
#define _exhaustPos	info.visualAttr.exhaustPos	/**< short cut to tVisualAttributes#exhaustPos */
#define _exhaustPower	info.visualAttr.exhaustPower	/**< short cut to tVisualAttributes#exhaustPower */

#define RM_DRV_HUMAN	1
#define RM_DRV_ROBOT	2


/** Race Administrative info */
typedef struct {
    double	bestLapTime;
    double	deltaBestLapTime;
    double	curLapTime;
    double	lastLapTime;
    double	curTime;
    tdble	topSpeed;
    int		laps;
    int		nbPitStops;
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
    int		event;
} tCarRaceInfo;
/* structure access */
#define _bestLapTime		race.bestLapTime
#define _deltaBestLapTime	race.deltaBestLapTime
#define _curLapTime		race.curLapTime
#define _curTime		race.curTime
#define _lastLapTime		race.lastLapTime
#define _topSpeed		race.topSpeed
#define _laps			race.laps
#define _nbPitStops		race.nbPitStops
#define _remainingLaps		race.remainingLaps
#define _pos			race.pos
#define _timeBehindLeader	race.timeBehindLeader
#define _lapsBehindLeader	race.lapsBehindLeader
#define _timeBehindPrev		race.timeBehindPrev
#define _timeBeforeNext		race.timeBeforeNext
#define _distRaced		race.distRaced
#define _distFromStartLine	race.distFromStartLine
#define _pit			race.pit
#define _scheduledEventTime	race.scheduledEventTime
#define _event			race.event

/** Public info on the cars */
typedef struct {
    tDynPt	DynGC;		/**< GC data (car axis) */    
    tDynPt	DynGCg;		/**< GC data (world axis) */    
    sgMat4	posMat;		/**< position matrix */
    tTrkLocPos	trkPos;		/**< current track position */
    int		state;	    	/**< state of the car.
				   <br>The states are:
				   - RM_CAR_STATE_FINISH
				   - RM_CAR_STATE_PIT
				   - RM_CAR_STATE_DNF
				   - RM_CAR_STATE_PULLUP
				   - RM_CAR_STATE_PULLSIDE
				   - RM_CAR_STATE_PULLDN
				   - RM_CAR_STATE_OUT
				   - RM_CAR_STATE_NO_SIMU
				   - RM_CAR_STATE_BROKEN
				   - RM_CAR_STATE_OUTOFGAS
				*/
#define RM_CAR_STATE_FINISH	 0x00000100				/**< Car having passed the finish line */
#define RM_CAR_STATE_PIT	 0x00000001				/**< Car currently stopped in pits */
#define RM_CAR_STATE_DNF	 0x00000002				/**< Car did not finish */
#define RM_CAR_STATE_PULLUP	 0x00000004				/**< Car pulled out in the air */
#define RM_CAR_STATE_PULLSIDE	 0x00000008				/**< Car pulled out in the air */
#define RM_CAR_STATE_PULLDN	 0x00000010				/**< Car pulled out in the air */
#define RM_CAR_STATE_OUT	(RM_CAR_STATE_DNF | RM_CAR_STATE_FINISH)/**< Car out of race */
#define RM_CAR_STATE_NO_SIMU	 0x000000FF				/**< Do not simulate the car */
#define RM_CAR_STATE_BROKEN	 0x00000200				/**< Engine no more working */
#define RM_CAR_STATE_OUTOFGAS	 0x00000400				/**< Out of Gas */
    tPosd	corner[4];

} tPublicCar;
/* structure access */
#define _DynGC		pub.DynGC
#define _pos_X		pub.DynGC.pos.x
#define _pos_Y		pub.DynGC.pos.y
#define _pos_Z		pub.DynGC.pos.z
#define _roll		pub.DynGC.pos.ax
#define _pitch		pub.DynGC.pos.ay
#define _yaw		pub.DynGC.pos.az
#define _yaw_rate	pub.DynGC.vel.az
#define _speed_x	pub.DynGC.vel.x
#define _speed_y	pub.DynGC.vel.y
#define _speed_z	pub.DynGC.vel.z
#define _accel_x	pub.DynGC.acc.x
#define _accel_y	pub.DynGC.acc.y
#define _accel_z	pub.DynGC.acc.z
#define _state		pub.state
#define _trkPos		pub.trkPos
#define _speed_X	pub.DynGCg.vel.x
#define _speed_Y	pub.DynGCg.vel.y
#define _corner_x(i)	pub.corner[i].ax
#define _corner_y(i)	pub.corner[i].ay
#define _posMat		pub.posMat

/** Dynamic wheel information */
typedef struct {
    tPosd	relPos;		/**< position relative to GC */
    tdble	spinVel;	/**< spin velocity rad/s */
    tdble	brakeTemp;	/**< brake temperature from 0 (cool) to 1.0 (hot) */
    int		state;		/**< wheel state */
    tTrackSeg	*seg;		/**< Track segment where the wheel is */
} tWheelState;
#define _ride(i)	priv.wheel[i].relPos.z
#define _brakeTemp(i)	priv.wheel[i].brakeTemp
#define _wheelSpinVel(i) priv.wheel[i].spinVel
#define _wheelSeg(i)	priv.wheel[i].seg

#define MAX_GEARS	10	/* including reverse and neutral */

/** Data known only by the driver */
typedef struct {
    void	*paramsHandle;	/**< accessible parameters for modules */
    void	*carHandle;	/**< parameters for car caracteristics */
    int		driverIndex;	/**< index when multiple drivers are in the same dll */
    char	modName[MAX_NAME_LEN];	/**< dll name */
    tWheelState	wheel[4];
    tPosd	corner[4];	/**< car's corners position */
    int		gear;	    	/**< current gear */
    tdble	fuel;	    	/**< remaining fuel (liters) */
    tdble	enginerpm;
    tdble	enginerpmRedLine;
    tdble	enginerpmMax;
    tdble	enginerpmMaxTq;
    tdble	gearRatio[MAX_GEARS];	/**< including final drive */
    int		gearNb;			/**< incl reverse and neutral */
    int		gearOffset;		/**< gearRatio[gear + gearOffset] is the ratio for gear */

    tdble	skid[4];		/**< skid intensity */
    int		collision;
    t3Dd	normal;
    t3Dd	collpos;
    int		dammage;
    int		debug;
} tPrivCar;
/* structure access */
#define _driverIndex	priv.driverIndex
#define _paramsHandle	priv.paramsHandle
#define _carHandle	priv.carHandle
#define _modName	priv.modName
#define _enginerpm	priv.enginerpm
#define _enginerpmRedLine	priv.enginerpmRedLine
#define _enginerpmMax	priv.enginerpmMax
#define _enginerpmMaxTq	priv.enginerpmMaxTq
#define _gearRatio	priv.gearRatio
#define _gearNb		priv.gearNb
#define _gearOffset	priv.gearOffset
#define _fuel		priv.fuel
#define _gear		priv.gear
#define _debug		priv.debug
#define _skid		priv.skid
#define _dammage	priv.dammage

/** Info returned by driver during the race */
typedef struct {
    tdble	steer;	    /**< Steer command [-1.0, 1.0]  */
    tdble	accelCmd;   /**< Accelerator command [0.0, 1.0] */
    tdble	brakeCmd;   /**< Brake command [0.0, 1.0] */
    int		gear;  	    /**< [-1,6] for gear selection */
    int		raceCmd;    /**< command issued by the driver */
#define RM_CMD_NONE		0	/**< No race command */
#define RM_CMD_PIT_ASKED	1	/**< Race command: Pit asked */
    char	*msg[4];     /**< 4 lines of 12 characters from car */
    float	msgColor[4]; /**< RGBA of text */
} tCarCtrl;
#define _steerCmd	ctrl.steer
#define _accelCmd	ctrl.accelCmd
#define _brakeCmd	ctrl.brakeCmd
#define _gearCmd	ctrl.gear
#define _raceCmd	ctrl.raceCmd
#define _msgCmd		ctrl.msg
#define _msgColorCmd	ctrl.msgColor

struct RobotItf;

/** Command issued by the car during pit stop */
typedef struct 
{
    tdble		fuel;
    int			repair;
} tCarPitCmd;
#define _pitFuel	pitcmd.fuel
#define _pitRepair	pitcmd.repair

/** Car structure (tCarElt).
    This is the main car structure, used everywhere in the code.
*/
typedef struct CarElt
{
    int			index;	/**< car index */
    tInitCar		info;	/**< public */
    tPublicCar		pub;	/**< public */
    tCarRaceInfo	race;	/**< public */
    tPrivCar		priv;	/**< private */
    tCarCtrl		ctrl;	/**< private */
    tCarPitCmd		pitcmd;	/**< private */
    struct RobotItf	*robot;	/**< private */
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
#define SECT_EXHAUST		"Exhaust"

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
#define PRM_FCL			"front Clift"
#define PRM_RCL			"rear Clift"
#define PRM_FRNTAREA		"front area"
#define PRM_WINGAREA		"area"
#define PRM_WINGANGLE		"angle"

/* Engine */
#define PRM_REVSLIM		"revs limiter"
#define PRM_REVSMAX		"revs maxi"
#define PRM_TICKOVER		"tickover"
#define PRM_RPM			"rpm"
#define PRM_TQ			"Tq"
#define ARR_DATAPTS		"data points"
#define PRM_FUELCONS		"fuel cons factor"
#define PRM_ENGBRKCOEFF		"brake coefficient"
#define PRM_POWER		"power"


#define PRM_RATIO		"ratio"
#define PRM_BIAS		"bias"

#define ARR_GEARS		"gears"
#define PRM_SHIFTTIME		"shift time"

#define	PRM_ROLLCENTER		"roll center height"

#define LST_RANGES		"Ranges"
#define PRM_THRESHOLD		"threshold"
#define PRM_CAR			"car"
#define PRM_WHEELSON		"wheels"
#define PRM_ENV			"env"
#define PRM_BONNET		"bonnet"
#define PRM_WHEEL_TEXTURE	"wheel texture"
#define PRM_SHADOW_TEXTURE	"shadow texture"

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


/* graphic */
#define PRM_TACHO_TEX		"tachometer texture"
#define PRM_TACHO_XSZ		"tachometer width"
#define PRM_TACHO_YSZ		"tachometer height"
#define PRM_TACHO_XPOS		"tachometer x pos"
#define PRM_TACHO_YPOS		"tachometer y pos"
#define PRM_TACHO_NDLXSZ	"tachometer needle width"
#define PRM_TACHO_NDLYSZ	"tachometer needle height"
#define PRM_TACHO_XCENTER	"tachometer needle x center"
#define PRM_TACHO_YCENTER	"tachometer needle y center"
#define PRM_TACHO_XDIGITCENTER	"tachometer digit x center"
#define PRM_TACHO_YDIGITCENTER	"tachometer digit y center"
#define PRM_TACHO_MINVAL	"tachometer min value"
#define PRM_TACHO_MAXVAL	"tachometer max value"
#define PRM_TACHO_MINANG	"tachometer min angle"
#define PRM_TACHO_MAXANG	"tachometer max angle"

#define PRM_SPEEDO_TEX		"speedometer texture"
#define PRM_SPEEDO_XSZ		"speedometer width"
#define PRM_SPEEDO_YSZ		"speedometer height"
#define PRM_SPEEDO_XPOS		"speedometer x pos"
#define PRM_SPEEDO_YPOS		"speedometer y pos"
#define PRM_SPEEDO_NDLXSZ	"speedometer needle width"
#define PRM_SPEEDO_NDLYSZ	"speedometer needle height"
#define PRM_SPEEDO_XCENTER	"speedometer needle x center"
#define PRM_SPEEDO_YCENTER	"speedometer needle y center"
#define PRM_SPEEDO_XDIGITCENTER	"speedometer digit x center"
#define PRM_SPEEDO_YDIGITCENTER	"speedometer digit y center"
#define PRM_SPEEDO_MINVAL	"speedometer min value"
#define PRM_SPEEDO_MAXVAL	"speedometer max value"
#define PRM_SPEEDO_MINANG	"speedometer min angle"
#define PRM_SPEEDO_MAXANG	"speedometer max angle"

#endif /* __CARV1_H__ */ 



