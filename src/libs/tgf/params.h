/***************************************************************************

    file                 : params.h
    created              : Mon Jan 31 22:19:04 CET 2000
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
 

#ifndef _PARAMS_H_
#define _PARAMS_H_

#define BUFMAX	1024

/* Internal structures for parameters management */

#define PARM_NODE_ROOT	0x01
#define PARM_NODE_PARM	0x02
#define PARM_NODE_SECT	0x04
#define PARM_NODE_KEY	0x10

#define PARM_NODE_BRANCH	0x0F

typedef struct ParmWithin {
    char		*val;
    struct ParmWithin	*next;
} tParmWithin;

typedef struct ParmNode {
    struct ParmNode	*next;
    struct ParmNode	*prev;
    struct ParmNode	*kids;
    struct ParmNode	*parent;
    int			type;
    char		*name;
} tParmNode;

typedef struct ParmKey {
    tParmNode		n;

    int			type;
#define P_NUM 0
#define P_STR 1
    char		*valstr;
    tdble		valnum;
    tdble		min;
    tdble		max;
    struct ParmWithin	*withins;
} tParmKey;

typedef struct ParmSect {
    tParmNode		n;
    tParmNode		*current;
} tParmSect;

typedef struct Parm {
    tParmNode		n;
    char		*file;
    int			type;
    int			mode;
    int			refcount;
} tParm;


#endif /* _PARAMS_H_ */ 



