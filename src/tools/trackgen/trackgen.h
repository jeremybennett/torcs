/***************************************************************************

    file                 : trackgen.h
    created              : Sun Dec 24 16:00:03 CET 2000
    copyright            : (C) 2000 by Eric Espié
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

#ifndef _TRACKGEN_H_
#define _TRACKGEN_H_

extern void GenerateTrack(char *trackname);

extern int	Orientation;
extern float	GridStep;
extern float	TrackStep;
extern float	Margin;
extern float	ExtHeight;
extern char	*OutputFileName;
extern char	*ReliefFileName;
extern int 	SceneDraw;

extern void	LoadRelief(char *reliefFile);
extern void	GenRelief(int interior);
extern void	CountRelief(int interior, int *nb_vert, int *nb_seg);


#define CLOCKWISE	0
#define ANTICLOCKWISE	1

#endif /* _TRACKGEN_H_ */ 



