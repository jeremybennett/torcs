/***************************************************************************

    file                 : practicectrl.h
    created              : Sun Jan 30 22:59:06 CET 2000
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
 
 
#ifndef _PRACTICECTRLV1_H_
#define _PRACTICECTRLV1_H_

#include <raceman.h>

#define PRACTICE_CFG	"config/practice/practice.xml"

typedef struct tPractResults
{
    struct tPractResults	*next;		/* should be first for ring lists */
    struct tPractResults	*prev;
    int				lap;		/* current lap */
    tdble			lapTime;	/* in s */
    tdble			topSpeed;	/* in m/s */
    tdble			bottomSpeed;	/* in m/s */
    tdble			speedAvg;	/* in m/s */
    tdble			fuel;		/* in l */
} tPractResults;

typedef void (*tfPractice)(void);


typedef struct
{
    tfPractice	run;
    void	*backMenu;
} tPracticeFct;


typedef void (*tfStartCtrl)(tPracticeFct * /* functions of practice module */);
typedef void (*tfPractResults)(tRingListHead * /* results of the run (list of tPractResults) */);

typedef struct 
{
    tfStartCtrl		startCtrl;
    tfPractResults	results;
} tPractCtrlItf;

#endif /* _PRACTICECTRLV1_H_ */ 



