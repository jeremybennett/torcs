/***************************************************************************
                          tgf.cpp -- The Gaming Framework                            
                             -------------------                                         
    created              : Fri Aug 13 22:31:43 CEST 1999
    copyright            : (C) 1999 by Eric Espie                         
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


#include <tgf.h>
#include "gui.h"

extern void gfDirInit(void);
extern void gfModInit(void);
extern void gfOsInit(void);
extern void gfParamInit(void);
extern void gfScreenInit(void);
/* extern void gfTraceInit(void); */
extern void gfMenuInit(void);
extern void gfRlstInit(void);

void
GfInit(void)
{
    gfDirInit();
    gfuiInit();
    gfMenuInit();
    gfModInit();
    gfOsInit();
    gfParamInit();
    gfScreenInit();
    gfRlstInit();
/*     gfTraceInit(); */
}

tdble
gfMean(tdble v, tMeanVal *pvt, int n, int w)
{
    int		i;
    tdble	sum;
    
    if (n > pvt->curNum) {
	if (pvt->curNum < GF_MEAN_MAX_VAL) {
	    pvt->curNum++;
	}
	n = pvt->curNum;
    } else {
	pvt->curNum = n;
    }
    sum = 0;
    for (i = 0; i < n; i++) {
	pvt->val[i] = pvt->val[i + 1];
	sum += pvt->val[i];
    }
    pvt->val[n] = v;
    sum += (tdble)w * v;
    sum /= (tdble)(n + w);

    return sum;
}

