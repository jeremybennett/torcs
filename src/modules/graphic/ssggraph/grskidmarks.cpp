/***************************************************************************

    file                 : grskidmarks.cpp
    created              : Fri Mar 22 23:17:24 CET 2002
    copyright            : (C) 2001 by Christopha Guionneau
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

#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include <plib/ssg.h>

#include <tgf.h>
#include <track.h>
#include <car.h>
#include <graphic.h>
#include <robottools.h>

#include "grmain.h"
#include "grshadow.h"
#include "grskidmarks.h"
#include "grcar.h"
#include "grcam.h"
#include "grscene.h"
#include "grboard.h"
#include "grssgext.h"
#include "grutil.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

static ssgSimpleState *skidState = NULL;

int grSkidMaxStripByWheel;
int grSkidMaxPointByStrip;
double grSkidDeltaT;

/** initialize the skidmak structure for a car*/
void grInitSkidmarks(tCarElt *car)
{
    int i; 
    int k;
    sgVec4		clr;
    ssgColourArray	*shd_clr;
    ssgNormalArray	*shd_nrm;
    sgVec3		nrm;

    grSkidMaxStripByWheel = (int)GfParmGetNum(grHandle, GR_SCT_GRAPHIC, GR_ATT_MAXSTRIPBYWHEEL,
					      (char*)NULL, MAXSTRIP_BYWHEEL);
    grSkidMaxPointByStrip = (int)GfParmGetNum(grHandle, GR_SCT_GRAPHIC, GR_ATT_MAXPOINTBYSTRIP,
					      (char*)NULL, MAXPOINT_BY_STRIP);
    grSkidDeltaT = (double)GfParmGetNum(grHandle, GR_SCT_GRAPHIC, GR_ATT_SKIDDELTAT,
					(char*)NULL, DELTATSTRIP);

    if (!grSkidMaxStripByWheel) {
	return;
    }

    shd_clr = new ssgColourArray(1);
    clr[0] = clr[1] = clr[2] = 0.1;
    clr[3] = 0.6;
    shd_clr->add(clr);

    shd_nrm = new ssgNormalArray(1);
    nrm[0] = nrm[1] = 0.0;
    nrm[2] = 1.0;
    shd_nrm->add(nrm);

    if (skidState == NULL) {
	skidState = new ssgSimpleState;
	skidState->enable(GL_LIGHTING);
	skidState->disable(GL_TEXTURE_2D);
	skidState->disable(GL_COLOR_MATERIAL);
    }
      
    grCarInfo[car->index].skidmarks = (tgrSkidmarks *)malloc(sizeof(tgrSkidmarks));
    for (i = 0; i<4; i++) {
	grCarInfo[car->index].skidmarks->strips[i].vtx   = (ssgVertexArray **)malloc(grSkidMaxStripByWheel * sizeof(ssgVertexArray *));
	grCarInfo[car->index].skidmarks->strips[i].vta   = (ssgVtxTableShadow **)malloc(grSkidMaxStripByWheel 
											* sizeof(ssgVtxTableShadow *));
	grCarInfo[car->index].skidmarks->strips[i].clr   = ( ssgColourArray **)malloc(grSkidMaxStripByWheel 
											* sizeof( ssgColourArray *));

	grCarInfo[car->index].skidmarks->strips[i].state = (int *)malloc(grSkidMaxStripByWheel * sizeof(int));
	grCarInfo[car->index].skidmarks->strips[i].size  = (int *)malloc(grSkidMaxStripByWheel * sizeof(int));
	
	for (k = 0; k < grSkidMaxStripByWheel; k++) {
	    grCarInfo[car->index].skidmarks->strips[i].state[k] = SKID_UNUSED;
	    grCarInfo[car->index].skidmarks->strips[i].vtx[k] = new ssgVertexArray(grSkidMaxPointByStrip + 1);
	    grCarInfo[car->index].skidmarks->strips[i].clr[k] = new ssgColourArray(grSkidMaxPointByStrip + 1);

	    grCarInfo[car->index].skidmarks->strips[i].vta[k] = new ssgVtxTableShadow(GL_TRIANGLE_STRIP,
										      grCarInfo[car->index].skidmarks->strips[i].vtx[k]
										      ,shd_nrm, NULL,
										      grCarInfo[car->index].skidmarks->strips[i].clr[k]
										      );
	    grCarInfo[car->index].skidmarks->strips[i].vta[k]->setCullFace(0);
	    grCarInfo[car->index].skidmarks->strips[i].vta[k]->setState(skidState);
	    grCarInfo[car->index].skidmarks->strips[i].timeStrip = 0;
	    TheScene->addKid(grCarInfo[car->index].skidmarks->strips[i].vta[k]);
	}
	/** no skid is in used */
	grCarInfo[car->index].skidmarks->strips[i].running_skid = 0;
	/** the next skid to used is the first one */
	grCarInfo[car->index].skidmarks->strips[i].next_skid = 0;
	/** there was no skid for this wheel during the next shot */
	grCarInfo[car->index].skidmarks->strips[i].last_state_of_skid = 0;
    }
}

/** update if necessary the skidmarks for a car */
void grUpdateSkidmarks(tCarElt *car, double t)
{
    int			i = 0;
    sgVec3		vtx;
    sgVec3		*tvtx;
    ssgVertexArray 	*basevtx = NULL;
    sgVec4		cur_clr;
    if (!grSkidMaxStripByWheel) {
	return;
    }
    cur_clr[0] = cur_clr[1] = cur_clr[2] = 0.1;

    for (i = 0; i < 4; i++) {
	if ((t - grCarInfo[car->index].skidmarks->strips[i].timeStrip) < grSkidDeltaT) {
	    continue;
	}
      
	if ((car->_speed_x * car->_speed_x + car->_speed_y * car->_speed_y) > 10.0) {
	    if (car->_skid[i] > 0.0) {

		basevtx = new ssgVertexArray(4 * 2 + 1);
	    
		cur_clr[3] = car->_skid[i];
		
		vtx[0] = car->priv->wheel[i].relPos.x-car->_tireHeight(i);
		vtx[1] = car->priv->wheel[i].relPos.y-car->_tireWidth(i) / 2.0;
		vtx[2] = car->priv->wheel[i].relPos.z-car->_wheelRadius(i)*1.1 ;
		basevtx->add(vtx);
		vtx[0] = car->priv->wheel[i].relPos.x-car->_tireHeight(i);
		vtx[1] = car->priv->wheel[i].relPos.y+car->_tireWidth(i) / 2.0;
		vtx[2] = car->priv->wheel[i].relPos.z-car->_wheelRadius(i)*1.1 ;
		basevtx->add(vtx);
		grCarInfo[car->index].skidmarks->base = new ssgVtxTable(GL_TRIANGLE_STRIP, basevtx, NULL, NULL, NULL);
		grCarInfo[car->index].skidmarks->base->transform(grCarInfo[car->index].carPos);
		grCarInfo[car->index].skidmarks->base->getVertexList((void**)&tvtx);
		/** this is the begining of a skid or the continue 
		    of the last one */
		if (grCarInfo[car->index].skidmarks->strips[i].last_state_of_skid == 0) {
		    /* begin case */
		    grCarInfo[car->index].skidmarks->strips[i].last_state_of_skid = 1;
		    /* start a new one */
		    grCarInfo[car->index].skidmarks->strips[i].running_skid = grCarInfo[car->index].skidmarks->strips[i].next_skid;
		    if (grCarInfo[car->index].skidmarks->strips[i].state[grCarInfo[car->index].skidmarks->strips[i].running_skid] != SKID_UNUSED) {
			grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].running_skid]->removeAll();
			grCarInfo[car->index].skidmarks->strips[i].clr[grCarInfo[car->index].skidmarks->strips[i].running_skid]->removeAll();
			//printf("clearing [%d] %d\n",i,grCarInfo[car->index].skidmarks->strips[i].running_skid);
		    }

		    grCarInfo[car->index].skidmarks->strips[i].state[grCarInfo[car->index].skidmarks->strips[i].running_skid] = SKID_BEGIN;
		    grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(tvtx[0]);
		    grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(tvtx[1]);

		    grCarInfo[car->index].skidmarks->strips[i].clr[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(cur_clr);
		    grCarInfo[car->index].skidmarks->strips[i].clr[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(cur_clr);

		    //printf("begin [%d] skid %d x = %.2f y = %.2f \n",i,grCarInfo[car->index].skidmarks->strips[i].running_skid,tvtx[0][0],tvtx[0][1]);
		    grCarInfo[car->index].skidmarks->strips[i].vta[grCarInfo[car->index].skidmarks->strips[i].running_skid]->recalcBSphere();
		    grCarInfo[car->index].skidmarks->strips[i].size[grCarInfo[car->index].skidmarks->strips[i].running_skid] = 2;
		    grCarInfo[car->index].skidmarks->strips[i].timeStrip=t;
		} else {
		    /* continue case */
		    grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(tvtx[0]);
		    grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(tvtx[1]);
		    grCarInfo[car->index].skidmarks->strips[i].clr[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(cur_clr);
		    grCarInfo[car->index].skidmarks->strips[i].clr[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(cur_clr);

		    //printf("continue [%d] x = %.2f y = %.2f \n",i,tvtx[0][0],tvtx[0][1]);
		    grCarInfo[car->index].skidmarks->strips[i].size[grCarInfo[car->index].skidmarks->strips[i].running_skid] += 2;
		    if ( grCarInfo[car->index].skidmarks->strips[i].state[grCarInfo[car->index].skidmarks->strips[i].running_skid] == SKID_BEGIN)
			{
			    grCarInfo[car->index].skidmarks->strips[i].state[grCarInfo[car->index].skidmarks->strips[i].running_skid] = SKID_RUNNING;
			    /*TheScene->addKid(grCarInfo[car->index].skidmarks->strips[i].vta[grCarInfo[car->index].skidmarks->strips[i].running_skid]);*/
			}
		    grCarInfo[car->index].skidmarks->strips[i].vta[grCarInfo[car->index].skidmarks->strips[i].running_skid]->recalcBSphere();
		    grCarInfo[car->index].skidmarks->strips[i].timeStrip=t;
		}
		basevtx->removeAll();
		delete grCarInfo[car->index].skidmarks->base;
	    } else {
		/** this is the end of a skid or there is nothing to do */
		if (grCarInfo[car->index].skidmarks->strips[i].last_state_of_skid != 0) {
		    /* end the running skid */
		    grCarInfo[car->index].skidmarks->strips[i].state[grCarInfo[car->index].skidmarks->strips[i].running_skid] = SKID_STOPPED;
		    grCarInfo[car->index].skidmarks->strips[i].vta[grCarInfo[car->index].skidmarks->strips[i].running_skid]->recalcBSphere();
		    grCarInfo[car->index].skidmarks->strips[i].last_state_of_skid = 0;
		    //printf("end skid [%d] %d\n",i,grCarInfo[car->index].skidmarks->strips[i].running_skid);

		    grCarInfo[car->index].skidmarks->strips[i].next_skid += 1;
		    if (grCarInfo[car->index].skidmarks->strips[i].next_skid >= grSkidMaxStripByWheel) {
			grCarInfo[car->index].skidmarks->strips[i].next_skid = 0;
			/* reset the next skid vertexArray */
			grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].next_skid]->removeAll();
			grCarInfo[car->index].skidmarks->strips[i].clr[grCarInfo[car->index].skidmarks->strips[i].next_skid]->removeAll();
			//printf("remove all in skid [%d] %d\n",i,grCarInfo[car->index].skidmarks->strips[i].next_skid);
		    }
		}
	    }
	}
    }
}

/** remove the skidmarks information for a car */
void grShutdownSkidmarks (void)
{
    int i ;
    int k ; 
    int z;

    if (!grSkidMaxStripByWheel) {
	return;
    }

    for (z = 0; z < grNbCars; z++) {
	for (i = 0; i<4; i++) {
	    for (k = 0; k < grSkidMaxStripByWheel; k++) {
		if (grCarInfo[z].skidmarks->strips[i].state[k] != SKID_UNUSED) {
		    TheScene->removeKid(grCarInfo[z].skidmarks->strips[i].vta[k]);
		}
	    }
	    free(grCarInfo[z].skidmarks->strips[i].vtx);
	    free(grCarInfo[z].skidmarks->strips[i].vta);
	    free(grCarInfo[z].skidmarks->strips[i].state);
	    free(grCarInfo[z].skidmarks->strips[i].size);
	}
	free(grCarInfo[z].skidmarks);
	grCarInfo[z].skidmarks = NULL;
    }
}


void grDrawSkidmarks (tCarElt *car)
{
    /* nothing to do */
  
  
}
