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

#include <tgfclient.h>
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

    if (!grSmokeMaxNumber) {
		return;
    }
    
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
		sprintf(buf, "data/textures;data/img;.");
		mst = (ssgSimpleState*)grSsgLoadTexStateEx("smoke.rgb", buf, FALSE, FALSE);
		if (mst!=NULL) {
			mst->disable(GL_LIGHTING);
			mst->enable(GL_BLEND);
			mst->disable(GL_CULL_FACE);
			mst->setTranslucent();
			mst->setColourMaterial(GL_AMBIENT_AND_DIFFUSE);
		}
    }
    if (!mstf0) {
		sprintf(buf, "data/textures;data/img;.");
		mstf0 = (ssgSimpleState*)grSsgLoadTexStateEx("fire0.rgb", buf, FALSE, FALSE);
		if (mst!=NULL) {
			mstf0->disable(GL_LIGHTING);
			mstf0->enable(GL_BLEND);
			mstf0->disable(GL_CULL_FACE);
			mstf0->setTranslucent();
			mstf0->setColourMaterial(GL_AMBIENT_AND_DIFFUSE);
		}
    }
    if (!mstf1) {
		sprintf(buf, "data/textures;data/img;.");
		mstf1 = (ssgSimpleState*)grSsgLoadTexStateEx("fire1.rgb", buf, FALSE, FALSE);
		if (mst!=NULL) {
			mstf1->disable(GL_LIGHTING);
			mstf1->enable(GL_BLEND);
			mstf1->disable(GL_CULL_FACE);
			mstf1->setTranslucent();
			mstf1->setColourMaterial(GL_AMBIENT_AND_DIFFUSE);
		}
    }
}

/** update if necessary the smoke for a car */
void grUpdateSmoke(double t)
{
    tgrSmoke * tmp, *tmp2;
    tgrSmoke * prev;

    if (!grSmokeMaxNumber) {
		return;
    }

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
	  
			SmokeAnchor->removeKid(tmp->smoke);
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2);
			continue;
		}
      
		/* update the smoke */
		tmp->smoke->dt = t-tmp->smoke->lastTime;
		/* expand the Y value */
		tmp->smoke->sizey += tmp->smoke->dt*tmp->smoke->vexp*2.0;
		tmp->smoke->sizez += tmp->smoke->dt*tmp->smoke->vexp*.25;
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
		sgVec3 *vx = (sgVec3 *) tmp->smoke->getVertices()->get(0) ;

		tdble dt = tmp->smoke->dt;

		tdble damp = 0.2;
		tdble rWalk = 0.1;
		tmp->smoke->vvx -= damp*tmp->smoke->vvx*fabs(tmp->smoke->vvx) * dt;
		tmp->smoke->vvy -= damp*tmp->smoke->vvy*fabs(tmp->smoke->vvy) * dt;
		tmp->smoke->vvz -= damp*tmp->smoke->vvz*fabs(tmp->smoke->vvz) * dt;
		//tdble dz = grGetHOT(vx[0][0], vx[0][1]) + 1.0 - vx[0][2];
		tmp->smoke->vvz += 0.0001;//*dz;

		vx[0][0] += tmp->smoke->vvx * dt;
		vx[0][1] += tmp->smoke->vvy * dt;
		vx[0][2] += tmp->smoke->vvz * dt;




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
	//ssgColourArray *shd_clr;
    tgrCarInstrument	*curInst;
    tdble		val;
    tdble		spd2;
    int			index;

    if (!grSmokeMaxNumber) {
		return;
    }
    spd2 = car->_speed_x * car->_speed_x + car->_speed_y * car->_speed_y;


	for (i = 0; i < 4; i++) {
		tdble wspd2 = car->_wheelSlipSide(i) * car->_wheelSlipSide(i)
			+ car->_wheelSlipAccel(i) *  car->_wheelSlipAccel(i);
		//printf ("%f %f %f#SLIP\n", car->_wheelSlipSide(i), car->_wheelSlipAccel(i), sqrt(spd2));
		if (wspd2 > 0.001) {	
			if (smokeManager->number < grSmokeMaxNumber) {
				if ((t - timeSmoke[car->index*4+i]) < grSmokeDeltaT) {
					continue;
				} else {
					timeSmoke[car->index*4+i] = t;
				}

				sgVec3 cur_clr;
				tdble init_speed;
				tdble threshold = .1;
				tdble smoke_life_coefficient = 30.0;
				tdble smoke_speed_coefficient = 0.0;
				cur_clr[0] = 0.8;
				cur_clr[1] = 0.8;
				cur_clr[2] = 0.8;
				init_speed = 0.01;
				if (car->priv.wheel[i].seg) { // sanity check
					char* surface = car->priv.wheel[i].seg->surface->material;
					if (strstr(surface, "sand")) {
						cur_clr[0] = 0.8;
						cur_clr[1] = 0.7+urandom()*0.1;
						cur_clr[2] = 0.4+urandom()*0.2;
						init_speed = .5;
						threshold=.05;
						smoke_life_coefficient = 12.5;
						smoke_speed_coefficient = 0.25;
					} else if (strstr(surface, "dirt")) {
						cur_clr[0] = 0.7+urandom()*0.1;
						cur_clr[1] = 0.6+urandom()*0.1;
						cur_clr[2] = 0.5+urandom()*0.1;
						init_speed = 0.45;
						threshold=0.0;
						smoke_life_coefficient = 10.0;
						smoke_speed_coefficient = 0.5;
					} else if (strstr(surface,"mud")) {
						cur_clr[0] = 0.65;
						cur_clr[1] = 0.4+urandom()*.2;
						cur_clr[2] = 0.3+urandom()*.2;
						init_speed = 0.4;
						threshold=.2;
						smoke_speed_coefficient = 0.05;
					} else if (strstr(surface,"gravel")) {
						cur_clr[0] = 0.6;
						cur_clr[1] = 0.6;
						cur_clr[2] = 0.6;
						init_speed = 0.35;
						smoke_life_coefficient = 20.0;
						smoke_speed_coefficient = 0.1;
					} else if (strstr(surface,"grass")) {
						cur_clr[0] = 0.4+urandom()*.2;
					cur_clr[1] = 0.5+urandom()*.1;
					cur_clr[2] = 0.3+urandom()*.1;
					init_speed = 0.3;
					smoke_life_coefficient = 25.0;
					} else {
						cur_clr[0] = 0.8;
						cur_clr[1] = 0.8;
						cur_clr[2] = 0.8;
						init_speed = 0.01;
					}
				}
				smoke_life_coefficient = smoke_life_coefficient * (1.0 - urandom()*urandom());
				tdble spd_fx=tanh(0.001*car->_reaction[i])*smoke_speed_coefficient*sqrt(spd2);
				if (car->_skid[i]+0.025*urandom()*spd_fx>urandom()+threshold) {// instead of 0.3, to randomize


					shd_vtx = new ssgVertexArray(1);
					//shd_clr = new ssgColourArray(1);

					tmp = (tgrSmoke *) malloc(sizeof(tgrSmoke));
					vtx[0] = car->priv.wheel[i].relPos.x-car->_tireHeight(i);
					vtx[1] = car->priv.wheel[i].relPos.y;
					vtx[2] = car->priv.wheel[i].relPos.z-car->_wheelRadius(i)*1.1+SMOKE_INIT_SIZE;
					
					shd_vtx->add(vtx);
					tmp->smoke = new ssgVtxTableSmoke(shd_vtx,SMOKE_INIT_SIZE,SMOKE_TYPE_TIRE);
					init_speed = urandom()*init_speed;
					tdble sinCarYaw = sin(car->_yaw);
					tdble cosCarYaw = cos(car->_yaw);
					tmp->smoke->vvx = -sinCarYaw * car->_wheelSlipSide(i);
					tmp->smoke->vvy = cosCarYaw * car->_wheelSlipSide(i);
					tmp->smoke->vvx += cosCarYaw * car->_wheelSlipAccel(i);
					tmp->smoke->vvy += sinCarYaw * car->_wheelSlipAccel(i);
					tmp->smoke->vvz = 0.1;
					tdble stretchX=fabs(0.5*(car->_speed_X));// + tmp->smoke->vvx));
					tdble stretchY=fabs(0.5*(car->_speed_Y));//+ tmp->smoke->vvy));
					tmp->smoke->vvx *= init_speed;
					tmp->smoke->vvy *= init_speed;
					tmp->smoke->setState(mst);    
					tmp->smoke->setCullFace(0);

					//printf("%f\n", car->_reaction[i]);
					tmp->smoke->max_life = grSmokeLife *
						(car->_skid[i]*sqrt(wspd2)+urandom()*spd_fx)/ smoke_life_coefficient;
					for (int c=0; c<3; c++) {
						tmp->smoke->cur_col[c] = cur_clr[c];
					}

					tmp->smoke->cur_life = 0;
					tmp->smoke->sizex = VX_INIT + .1*(spd_fx + stretchX);
					tmp->smoke->sizey = VY_INIT + .1*(spd_fx + stretchY);
					tmp->smoke->sizez = VZ_INIT + .1*spd_fx;

					tmp->smoke->init_alpha = 1.0/(1.0+0.1*spd_fx);
					tmp->smoke->vexp = V_EXPANSION+(car->_skid[i]+.1*spd_fx)*(((float)rand()/(float)RAND_MAX));
					tmp->smoke->smokeType = SMOKE_TYPE_TIRE;
					tmp->smoke->smokeTypeStep = 0;
					tmp->next = NULL;
					tmp->smoke->lastTime = t;
					tmp->smoke->transform(grCarInfo[car->index].carPos);
					SmokeAnchor->addKid(tmp->smoke);
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

    if (car->_exhaustNb && (spd2 > 10.0)) {
		if (smokeManager->number < grSmokeMaxNumber) {
			index = car->index;	/* current car's index */
			if ((t - timeFire[index]) > grFireDeltaT) {
				timeFire[index] = t;
				curInst = &(grCarInfo[index].instrument[0]);
				val = ((curInst->rawPrev - curInst->minValue) / curInst->maxValue) - ((*(curInst->monitored) - curInst->minValue) / curInst->maxValue);
				curInst->rawPrev = *(curInst->monitored);
				if (val > 0.1) {
					grCarInfo[index].fireCount = (int)(10.0 * val * car->_exhaustPower);
				}
				//				if (grCarInfo[index].fireCount) {
				//					grCarInfo[index].fireCount--;
				if (car->priv.smoke>urandom()) {
			
					//car->priv.smoke = val * car->_exhaustPower;
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
						tmp->smoke->init_alpha = 0.9;
						tmp->smoke->sizex = VX_INIT*4;
						tmp->smoke->sizey = VY_INIT*4;
						tmp->smoke->sizez = VZ_INIT*4;
						tmp->smoke->vexp = V_EXPANSION+5.0*(((float)rand()/(float)RAND_MAX)) * car->_exhaustPower / 2.0;
						tmp->smoke->smokeType = SMOKE_TYPE_ENGINE;
						tmp->smoke->smokeTypeStep = 0;
						tmp->next = NULL;
						tmp->smoke->lastTime = t;
						tmp->smoke->transform(grCarInfo[index].carPos);
						SmokeAnchor->addKid(tmp->smoke);
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

    GfOut("-- grShutdownSmoke\n");

    if (!grSmokeMaxNumber) {
		return;
    }

    SmokeAnchor->removeAllKids();
    if (smokeManager) {
		tmp = smokeManager->smokeList;
		while( tmp!=NULL)
			{
				tmp2 = tmp->next;
				/* SmokeAnchor->removeKid(tmp->smoke); */
				free(tmp);
				tmp = tmp2;
			}
		smokeManager->smokeList = NULL;
		free(timeSmoke);
		free(timeFire);
		free(smokeManager);
		smokeManager = 0;
		smokeManager = NULL;
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
	cur_col[0] = cur_col[1] = cur_col[2] = 0.8;
	vvx = vvy = vvz = 0.0;
	init_alpha = 0.9;
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
	float a_c =  ((float)(cur_life/max_life));
    alpha =  init_alpha*(1.0-a_c);
    glDepthMask(GL_FALSE);
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
    glColor4f(cur_col[0],cur_col[1],cur_col[2],alpha);
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
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
}
