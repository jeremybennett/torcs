/***************************************************************************

    file                 : playerpref.h
    created              : Wed Mar 21 21:50:23 CET 2001
    copyright            : (C) 2001 by Eric Espié
    email                : Eric.Espie@torcs.org
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

#ifndef _PLAYERPREF_H_
#define _PLAYERPREF_H_

#define HM_PREF_FILE		"drivers/human/preferences.xml"

#define	HM_SECT_JSPREF		"joystick defaults"
#define	HM_SECT_MOUSEPREF	"mouse defaults"

#define HM_ATT_UP_SHFT		"up shift"
#define HM_ATT_DN_SHFT		"down shift"
#define HM_ATT_ASR_CMD		"ASR cmd"
#define HM_ATT_ABS_CMD		"ABS cmd"

#define HM_ATT_GEAR_R		"reverse gear"
#define HM_ATT_GEAR_N		"neutral gear"
#define HM_ATT_GEAR_1		"1st gear"
#define HM_ATT_GEAR_2		"2nd gear"
#define HM_ATT_GEAR_3		"3rd gear"
#define HM_ATT_GEAR_4		"4th gear"
#define HM_ATT_GEAR_5		"5th gear"
#define HM_ATT_GEAR_6		"6th gear"

/* used for RS Shifter controller */
#define HM_ATT_REL_BUT_NEUTRAL	"release gear button goes neutral"

/* Tell if the sequential shifter can go to neutral */
#define HM_ATT_SEQSHFT_ALLOW_NEUTRAL "sequential shifter allow neutral"

#define HM_ATT_LEFTSTEER	"left steer"
#define HM_ATT_LEFTSTEER_MIN	"left steer min"
#define HM_ATT_LEFTSTEER_MAX	"left steer max"
#define HM_ATT_LEFTSTEER_SENS	"left steer sensitivity"
#define HM_ATT_LEFTSTEER_POW	"left steer power"

#define HM_ATT_RIGHTSTEER	"right steer"
#define HM_ATT_RIGHTSTEER_MIN	"right steer min"
#define HM_ATT_RIGHTSTEER_MAX	"right steer max"
#define HM_ATT_RIGHTSTEER_SENS	"right steer sensitivity"
#define HM_ATT_RIGHTSTEER_POW	"right steer power"

#define HM_ATT_THROTTLE		"throttle"
#define HM_ATT_THROTTLE_MIN	"throttle min"
#define HM_ATT_THROTTLE_MAX	"throttle max"
#define HM_ATT_THROTTLE_SENS	"throttle sensitivity"
#define HM_ATT_THROTTLE_POW	"throttle power"

#define HM_ATT_BRAKE		"brake"
#define HM_ATT_BRAKE_MIN	"brake min"
#define HM_ATT_BRAKE_MAX	"brake max"
#define HM_ATT_BRAKE_SENS	"brake sensitivity"
#define HM_ATT_BRAKE_POW	"brake power"

#define	HM_SECT_PREF	"Preferences"

#define HM_LIST_DRV	"Drivers"

#define HM_ATT_TRANS	"transmission"
#define HM_ATT_ABS	"ABS on"
#define HM_ATT_ASR	"ASR on"
#define HM_ATT_NBPITS	"programmed pit stops"

#define HM_VAL_AUTO	"auto"
#define HM_VAL_MANUAL	"manual"

#define HM_VAL_YES	"yes"
#define HM_VAL_NO	"no"

#endif /* _PLAYERPREF_H_ */ 



