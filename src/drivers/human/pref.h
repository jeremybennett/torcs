/***************************************************************************

    file                 : pref.h
    created              : Sat Apr 29 16:52:41 CEST 2000
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
 


#ifndef _PREF_H_
#define _PREF_H_

extern void	*PrefHdle;

extern int	Transmission;

extern int	NbPitStopProg;

extern int	ParamAsr;	/* anti-slip accel */
extern int	ParamAbs;	/* anti-lock brake */

extern int	CmdButton[];

extern int	RelButNeutral;

extern int	CmdSteer;
extern float	SteerSens;
extern float	SteerPow;
extern int	CmdThrottle;
extern float	ThrMin;
extern float	ThrMinVal;
extern float	ThrMax;
extern float	ThrSens;
extern float	ThrPow;
extern int	CmdBrake;
extern float	BrkMin;
extern float	BrkMinVal;
extern float	BrkMax;
extern float	BrkSens;
extern float	BrkPow;
extern char *Yn[];

#define	CMD_BUT_UP_SHFT	0
#define	CMD_BUT_DN_SHFT	1
#define	CMD_BUT_ASR	2
#define	CMD_BUT_ABS	3
#define	CMD_BUT_GEAR_R	4
#define	CMD_BUT_GEAR_N	5
#define	CMD_BUT_GEAR_1	6
#define	CMD_BUT_GEAR_2	7
#define	CMD_BUT_GEAR_3	8
#define	CMD_BUT_GEAR_4	9
#define	CMD_BUT_GEAR_5	10
#define	CMD_BUT_GEAR_6	11



extern void HmReadPrefs(int index);


#endif /* _PREF_H_ */ 



