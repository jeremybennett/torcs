/***************************************************************************

    file                 : grsmoke.cpp
    created              : Fri Mar 22 23:17:54 CET 2002
    copyright            : (C) 2001 by Christophe Guionneau
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
#include "grsmoke.h"
#include "grcar.h"
#include "grcam.h"
#include "grscene.h"
#include "grboard.h"
#include "grssgext.h"
#include "grutil.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

int grSmokeMaxNumber;
double grSmokeDeltaT;
double grFireDeltaT;
double grSmokeLife;


static tgrSmokeManager *smokeManager = 0;
/** initialize the smoke structure */
ssgSimpleState	*mst = NULL;
ssgSimpleState	*mstf0 = NULL;
ssgSimpleState	*mstf1 = NULL;
ssgVtxTable * tsmoke = 0 ;
ssgVtxTable * tfire0 = 0 ;
ssgVtxTable * tfire1 = 0 ;
double * timeSmoke = 0;
double * timeFire = 0;

void grInitSmoke(int index)
{
    char		buf[256];

    grSmokeMaxNumber = (int)GfParmGetNum(grHandle, GR_SCT_GRAPHIC, GR_ATT_SMOKENB,
					 (char*)NULL, MAX_SMOKE_NUMBER);
    grSmokeDeltaT = (double)GfParmGetNum(grHandle, GR_SCT_GRAPHIC, GR_ATT_SMOKEDELTAT,
					 (char*)NULL, DELTAT);
    grSmokeLife = (double)GfParmGetNum(grHandle, GR_SCT_GRAPHIC, GR_ATT_SMOKEDLIFE,
				       (char*)NULL, MAX_SMOKE_LIFE);
    grFireDeltaT=grSmokeDeltaT*8;

    if (!timeSmoke) {
	timeSmoke = (double *) malloc(sizeof(double)*index*4);
	memset(timeSmoke,0,sizeof(double)*index*4);
    }
    if (!timeFire) {
	timeFire = (double *) malloc(sizeof(double)*index);
	memset(timeFire,0,sizeof(double)*index);
    }
    if (!smokeManager) {
	smokeManager = (tgrSmokeManager*) malloc(sizeof(tgrSmokeManager));
	smokeManager->smokeList = NULL;
	smokeManager->number = 0;
    }

    /* add temp object to get a reference on the states */
    if (!mst) {
	tsmoke = new ssgVtxTable(GL_TRIANGLE_STRIP, NULL, NULL, NULL, NULL);
	sprintf(buf, "data/textures;data/img;.");
	mst = (ssgSimpleState*)grSsgLoadTexStateEx("smoke.rgb", buf, FALSE, FALSE);
	if (mst!=NULL) {
	    mst->disable(GL_LIGHTING);
	    mst->disable(GL_COLOR_MATERIAL);
	    mst->enable(GL_BLEND);
	    mst->disable(GL_CULL_FACE);
	    mst->setTranslucent();
	    mst->setColourMaterial(GL_AMBIENT_AND_DIFFUSE);
	    tsmoke->setState(mst);    
	}
	TheScene->addKid(tsmoke);
    }
    if (!mstf0) {
      tfire0 = new ssgVtxTable(GL_TRIANGLE_STRIP, NULL, NULL, NULL, NULL);
      sprintf(buf, "data/textures;data/img;.");
      mstf0 = (ssgSimpleState*)grSsgLoadTexStateEx("fire0.rgb", buf, FALSE, FALSE);
      if (mst!=NULL) {
	mstf0->disable(GL_LIGHTING);
	mstf0->disable(GL_COLOR_MATERIAL);
	mstf0->enable(GL_BLEND);
	mstf0->disable(GL_CULL_FACE);
	mstf0->setTranslucent();
	mstf0->setColourMaterial(GL_AMBIENT_AND_DIFFUSE);
	tfire0->setState(mstf0);    
      }
      TheScene->addKid(tfire0);
    }
    if (!mstf1) {
      tfire1 = new ssgVtxTable(GL_TRIANGLE_STRIP, NULL, NULL, NULL, NULL);
      sprintf(buf, "data/textures;data/img;.");
      mstf1 = (ssgSimpleState*)grSsgLoadTexStateEx("fire1.rgb", buf, FALSE, FALSE);
      if (mst!=NULL) {
	mstf1->disable(GL_LIGHTING);
	mstf1->disable(GL_COLOR_MATERIAL);
	mstf1->enable(GL_BLEND);
	mstf1->disable(GL_CULL_FACE);
	mstf1->setTranslucent();
	mstf1->setColourMaterial(GL_AMBIENT_AND_DIFFUSE);
	tfire1->setState(mstf1);    
      }
      TheScene->addKid(tfire1);
    }
}

/** update if necessary the smoke for a car */
void grUpdateSmoke(double t)
{
    tgrSmoke * tmp, *tmp2;
    tgrSmoke * prev;

    prev = NULL;
    tmp = smokeManager->smokeList;
    while( tmp!=NULL) {
	if (tmp->smoke->cur_life>=tmp->smoke->max_life) {
	    if (prev) {
		prev->next = tmp->next;
	    } else {
		smokeManager->smokeList = tmp->next;
	    }
	  
	    smokeManager->number--;
	  
	    TheScene->removeKid(tmp->smoke);
	    tmp2 = tmp;
	    tmp = tmp->next;
	    free(tmp2);
	    continue;
	}
      
	/* update the smoke */
	tmp->smoke->dt = t-tmp->smoke->lastTime;
	/* expand the Y value */
	tmp->smoke->sizey += tmp->smoke->dt*tmp->smoke->vexp*2.0;
	tmp->smoke->sizez += tmp->smoke->dt*tmp->smoke->vexp;
	tmp->smoke->sizex += tmp->smoke->dt*tmp->smoke->vexp*2.0;
	if (tmp->smoke->smokeType==SMOKE_TYPE_ENGINE)
	  {
	    if (tmp->smoke->smokeTypeStep==0)
	      if (tmp->smoke->cur_life>=tmp->smoke->step0_max_life)
		{
		  /* changing from fire to smoke */
		  tmp->smoke->smokeTypeStep=1;
		  tmp->smoke->setState(mstf1);    
		}
	    else
	      if (tmp->smoke->smokeTypeStep==1)
		if (tmp->smoke->cur_life>=tmp->smoke->step1_max_life)
		  {
		    /* changing from fire to smoke */
		    tmp->smoke->smokeTypeStep=2;
		    tmp->smoke->setState(mst);    
		}
	  }
	/* expand the Z value */
	/*vtx[2][2]+=tmp->vexp*dt2;
	  vtx[3][2]+=tmp->vexp*dt2;
	*/
	tmp->smoke->lastTime = t;
	tmp->smoke->cur_life+=tmp->smoke->dt;
	prev = tmp;
	tmp = tmp->next;
    }
}

void grAddSmoke(tCarElt *car, double t)
{
    int i = 0;
    tgrSmoke * tmp;
    sgVec3	vtx;
    ssgVertexArray	*shd_vtx ;
    tgrCarInstrument	*curInst;
    tdble		val;
    int			index;

    if ((car->_speed_x * car->_speed_x + car->_speed_y * car->_speed_y) > 10.0) {
	if (smokeManager->number < grSmokeMaxNumber) {
	    for (i = 0; i < 4; i++) {
		if ((t - timeSmoke[car->index*4+i]) < grSmokeDeltaT) {
		    continue;
		} else {
		    timeSmoke[car->index*4+i] = t;
		}
	  
		if (car->_skid[i]>0.3) {
		    shd_vtx = new ssgVertexArray(1);

		    tmp = (tgrSmoke *) malloc(sizeof(tgrSmoke));
		    vtx[0] = car->priv->wheel[i].relPos.x-car->_tireHeight(i);
		    vtx[1] = car->priv->wheel[i].relPos.y;
		    vtx[2] = car->priv->wheel[i].relPos.z-car->_wheelRadius(i)*1.1+SMOKE_INIT_SIZE;
		    shd_vtx->add(vtx);
		    tmp->smoke = new ssgVtxTableSmoke(shd_vtx,SMOKE_INIT_SIZE,SMOKE_TYPE_TIRE);
		    /*
		      sprintf(buf, "data/textures;data/img;.");
		      st = (ssgSimpleState*)grSsgLoadTexStateEx("smoke.rgb", buf, FALSE, FALSE);
		      if (st!=NULL) {
		      st->disable(GL_LIGHTING);
		      st->disable(GL_COLOR_MATERIAL);
		      st->enable(GL_BLEND);
		      st->disable(GL_CULL_FACE);
		      st->setTranslucent();
		      st->setColourMaterial(GL_AMBIENT_AND_DIFFUSE);
		      tmp->smoke->setState(st);    
		      }
		      else
		      {
		      printf("error loading smoke.rgb\n");
		      }
		    */
		    tmp->smoke->setState(mst);    
		    tmp->smoke->setCullFace(0);
		    tmp->smoke->max_life = grSmokeLife * car->_skid[i];
		    tmp->smoke->cur_life = 0;
		    tmp->smoke->sizex = VX_INIT;
		    tmp->smoke->sizey = VY_INIT;
		    tmp->smoke->sizez = VZ_INIT;
		    tmp->smoke->vexp = V_EXPANSION+car->_skid[i]*2.0*(((float)rand()/(float)RAND_MAX));
		    tmp->smoke->smokeType = SMOKE_TYPE_TIRE;
		    tmp->smoke->smokeTypeStep = 0;
		    tmp->next = NULL;
		    tmp->smoke->lastTime = t;
		    tmp->smoke->transform(grCarInfo[car->index].carPos);
		    TheScene->addKid(tmp->smoke);
		    smokeManager->number++;
		    if (smokeManager->smokeList==NULL) {
			smokeManager->smokeList = tmp;
		    } else {
			tmp->next = smokeManager->smokeList;
			smokeManager->smokeList = tmp;
		    }
		}
	    }
	}
    }


    if (car->_exhaustNb && ((car->_speed_x * car->_speed_x + car->_speed_y * car->_speed_y) > 10.0)) {
	if (smokeManager->number < grSmokeMaxNumber) {
	    index = car->index;	/* current car's index */
	    if ((t - timeFire[index+i]) > grFireDeltaT) {
		timeFire[index+i] = t;
		curInst = &(grCarInfo[index].instrument[0]);
		val = ((curInst->rawPrev - curInst->minValue) / curInst->maxValue) - ((*(curInst->monitored) - curInst->minValue) / curInst->maxValue);
		curInst->rawPrev = *(curInst->monitored);
		if (val > 0.1) {
		    grCarInfo[index].fireCount = (int)(10.0 * val * car->_exhaustPower);
		}
		if (grCarInfo[index].fireCount) {
		    grCarInfo[index].fireCount--;
		    for (i = 0; i < car->_exhaustNb; i++) {
			shd_vtx = new ssgVertexArray(1);
			tmp = (tgrSmoke *) malloc(sizeof(tgrSmoke));
			vtx[0] = car->_exhaustPos[i].x;
			vtx[1] = car->_exhaustPos[i].y;
			vtx[2] = car->_exhaustPos[i].z;
		    
			shd_vtx->add(vtx);
			tmp->smoke = new ssgVtxTableSmoke(shd_vtx,SMOKE_INIT_SIZE*4,SMOKE_TYPE_ENGINE);
	      
			tmp->smoke->setState(mstf0);    
			tmp->smoke->setCullFace(0);
			tmp->smoke->max_life = grSmokeLife/8;
			tmp->smoke->step0_max_life =  (grSmokeLife)/50.0;
			tmp->smoke->step1_max_life =  (grSmokeLife)/50.0+ tmp->smoke->max_life/2.0;
			tmp->smoke->cur_life = 0;
			tmp->smoke->sizex = VX_INIT*4;
			tmp->smoke->sizey = VY_INIT*4;
			tmp->smoke->sizez = VZ_INIT*4;
			tmp->smoke->vexp = V_EXPANSION+5.0*(((float)rand()/(float)RAND_MAX)) * car->_exhaustPower / 2.0;
			tmp->smoke->smokeType = SMOKE_TYPE_ENGINE;
			tmp->smoke->smokeTypeStep = 0;
			tmp->next = NULL;
			tmp->smoke->lastTime = t;
			tmp->smoke->transform(grCarInfo[index].carPos);
			TheScene->addKid(tmp->smoke);
			smokeManager->number++;
			if (smokeManager->smokeList==NULL) {
			    smokeManager->smokeList = tmp;
			} else {
			    tmp->next = smokeManager->smokeList;
			    smokeManager->smokeList = tmp;
			}
		    }
		}
	    }
	}
    }
}

/** remove the smoke information for a car */
void grShutdownSmoke ()
{
    tgrSmoke *tmp, *tmp2;

    if (smokeManager) {
	tmp = smokeManager->smokeList;
	while( tmp!=NULL)
	    {
		tmp2 = tmp->next;
		TheScene->removeKid(tmp->smoke);
		free(tmp);
		tmp = tmp2;
	    }
	smokeManager->smokeList = NULL;
	free(timeSmoke);
	free(timeFire);
	free(smokeManager);
	smokeManager = 0;
	TheScene->removeKid(tsmoke);
	TheScene->removeKid(tfire0);
	TheScene->removeKid(tfire1);
	smokeManager = NULL;
	tsmoke = NULL;
	tfire0=NULL;
	timeSmoke = NULL;
	timeFire=NULL;
    }
}

void ssgVtxTableSmoke::copy_from ( ssgVtxTableSmoke *src, int clone_flags )
{
    ssgVtxTable::copy_from ( src, clone_flags ) ;
}
ssgBase *ssgVtxTableSmoke::clone ( int clone_flags )
{
    ssgVtxTableSmoke *b = new ssgVtxTableSmoke ;
    b -> copy_from ( this, clone_flags ) ;
    return b ;
}
ssgVtxTableSmoke::ssgVtxTableSmoke ()
{
    ssgVtxTable();
}
ssgVtxTableSmoke:: ssgVtxTableSmoke (ssgVertexArray	*shd_vtx , float initsize, int typ)
{
    sizex = sizey = sizez = initsize;
  
    gltype = GL_TRIANGLE_STRIP;
    type = ssgTypeVtxTable () ;
    stype = typ;
    vertices  = (shd_vtx!=NULL) ? shd_vtx : new ssgVertexArray   () ;
    normals   =  new ssgNormalArray   () ;
    texcoords =  new ssgTexCoordArray () ;
    colours   =  new ssgColourArray   () ;

    vertices  -> ref () ;
    normals   -> ref () ;
    texcoords -> ref () ;
    colours   -> ref () ;

    recalcBSphere () ;
}

ssgVtxTableSmoke::~ssgVtxTableSmoke ()
{
} 

void ssgVtxTableSmoke::draw_geometry ()
{
    int num_colours   = getNumColours   () ;
    int num_normals   = getNumNormals   () ;
    /*   int num_vertices  = getNumVertices  () ; */
    /*   int num_texcoords = getNumTexCoords () ; */
    float alpha;
    GLfloat modelView[16];
    sgVec3 A,B,C,D;
    sgVec3 right,up;

    sgVec3 *vx = (sgVec3 *) vertices  -> get(0) ;
    sgVec3 *nm = (sgVec3 *) normals   -> get(0) ;
    /*   sgVec2 *tx = (sgVec2 *) texcoords -> get(0) ; */
    sgVec4 *cl = (sgVec4 *) colours   -> get(0) ;

    alpha =  0.9-((float)(cur_life/max_life));
    glDepthMask(GL_FALSE);
    glDisable(GL_LIGHTING);
    glAlphaFunc(GL_GREATER,0.0);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    /*glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);*/
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    /*glPolygonOffset(-5.0f, +10.0f);*/
    /*glEnable(GL_POLYGON_OFFSET_FILL);*/

    /* the principle is to have a right and up verctor 
       to determine how the points of the quadri should be placed
       orthoganly to the view, paralel to the screen.
       This algo is inspired from the Cutout in Plib 
       and from the cutout in racer code */

    /* get the matrix */
    glGetFloatv(GL_MODELVIEW_MATRIX,modelView);

    /* get the up and right vector from the matrice view */
    up[0] = modelView[1];
    up[1] = modelView[5];
    up[2] = modelView[9];

    right[0] = modelView[0];
    right[1] = modelView[4];
    right[2] = modelView[8];

    /* compute the coordinates of the 
       four points of the quadri. */

    /* up and right points */
    C[0] = right[0]+up[0];
    C[1] = right[1]+up[1];
    C[2] = right[2]+up[2];
    /* left and up */
    D[0] = -right[0]+up[0];
    D[1] = -right[1]+up[1];
    D[2] = -right[2]+up[2];
    /* down and left */
    A[0] = -right[0]-up[0];
    A[1] = -right[1]-up[1];
    A[2] = -right[2]-up[2];
    /* right and down */
    B[0] = right[0]-up[0];
    B[1] = right[1]-up[1];
    B[2] = right[2]-up[2];

    glBegin ( gltype ) ;
    glColor4f(0.8,0.8,0.8,alpha);
    if ( num_colours == 1 ) glColor4fv  ( cl [ 0 ] ) ;
    if ( num_normals == 1 ) glNormal3fv ( nm [ 0 ] ) ;
    /* the computed coordinates are translated from the smoke position
       with the x,y,z speed*/
    glTexCoord2f(0,0);
    glVertex3f(vx[0][0]+sizex*A[0],vx[0][1]+sizey*A[1], vx[0][2]+sizez*A[2]);
    glTexCoord2f(0,1);
    glVertex3f(vx[0][0]+sizex*B[0],vx[0][1]+sizey*B[1], vx[0][2]+sizez*B[2]);
    glTexCoord2f(1,0);
    glVertex3f(vx[0][0]+sizex*D[0],vx[0][1]+sizey*D[1], vx[0][2]+sizez*D[2]);
    glTexCoord2f(1,1);
    glVertex3f(vx[0][0]+sizex*C[0],vx[0][1]+sizey*C[1], vx[0][2]+sizez*C[2]);
    glEnd () ;
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
}
