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
double grSmokeLife;


static tgrSmokeManager *smokeManager;
ssgCutout * rootSmoke = NULL;
/** initialize the smoke structure */
ssgSimpleState	*mst = NULL;
ssgVtxTable * tsmoke ;
double * timeSmoke;

void grInitSmoke(int index)
{
    char		buf[256];


    grSmokeMaxNumber = (int)GfParmGetNum(grHandle, GR_SCT_GRAPHIC, GR_ATT_SMOKENB,
					 (char*)NULL, MAX_SMOKE_NUMBER);
    grSmokeDeltaT = (double)GfParmGetNum(grHandle, GR_SCT_GRAPHIC, GR_ATT_SMOKEDELTAT,
					 (char*)NULL, DELTAT);
    grSmokeLife = (double)GfParmGetNum(grHandle, GR_SCT_GRAPHIC, GR_ATT_SMOKEDLIFE,
				       (char*)NULL, MAX_SMOKE_LIFE);
    
    if (!timeSmoke) {
	timeSmoke = (double *) malloc(sizeof(double)*index*4);
	memset(timeSmoke,0,sizeof(double)*index*4);
    }
    if (!smokeManager) {
	smokeManager = (tgrSmokeManager*) malloc(sizeof(tgrSmokeManager));
	smokeManager->smokeList = NULL;
	smokeManager->number = 0;
    }
    if (!mst) {
	tsmoke = new ssgVtxTable(GL_TRIANGLE_STRIP, NULL, NULL, NULL, NULL);
	sprintf(buf, "data/textures;data/img;.");
	mst = (ssgSimpleState*)grSsgLoadTexStateEx("smoke.rgb", buf, FALSE, FALSE);
	if (mst!=NULL) {
	    mst->disable(GL_LIGHTING);
	    mst->disable(GL_COLOR_MATERIAL);
	    mst->enable(GL_BLEND);
	    mst->setTranslucent();
	    tsmoke->setState(mst);    
	}
	TheScene->addKid(tsmoke);
    }
}

/** update if necessary the smoke for a car */
void grUpdateSmoke(double dt, double t)
{
    tgrSmoke * tmp, *tmp2;
    tgrSmoke * prev;

    if (dt==0)
	return;

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
	tmp->smoke->sizey +=  tmp->smoke->dt*tmp->smoke->vexp;
	tmp->smoke->sizez += tmp->smoke->dt*tmp->smoke->vexp;
	tmp->smoke->sizex += tmp->smoke->dt*tmp->smoke->vexp;
	/* expand the Z value */
	/*vtx[2][2]+=tmp->vexp*dt2;
	  vtx[3][2]+=tmp->vexp*dt2;
	*/
	tmp->smoke->lastTime = t;
	tmp->smoke->cur_life+=dt;
	prev = tmp;
	tmp = tmp->next;
    }
}

void grAddSmoke(tCarElt *car)
{
    int i = 0;
    tgrSmoke * tmp;
    double t;
    sgVec3	vtx;
    char		buf[256];
    ssgSimpleState	*st = NULL;
    ssgVertexArray	*shd_vtx ;

    t = GfTimeClock();
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
		    vtx[2] = car->priv->wheel[i].relPos.z-car->_wheelRadius(i)*1.1;
		    shd_vtx->add(vtx);
		    tmp->smoke = new ssgVtxTableSmoke(shd_vtx,SMOKE_INIT_SIZE,SMOKE_TYPE_TIRE);
		    sprintf(buf, "data/textures;data/img;.");
		    st = (ssgSimpleState*)grSsgLoadTexStateEx("smoke.rgb", buf, FALSE, FALSE);
		    if (st!=NULL) {
			st->disable(GL_LIGHTING);
			st->disable(GL_COLOR_MATERIAL);
			st->enable(GL_BLEND);
			st->disable(GL_CULL_FACE);
			st->setTranslucent();
			tmp->smoke->setState(st);    
		    }
		    else
			{
			    printf("error loading smoke.rgb\n");
			}
	    
		    tmp->smoke->setState(st);    
		    tmp->smoke->setCullFace(0);
		    tmp->smoke->max_life = grSmokeLife * car->_skid[i];
		    tmp->smoke->cur_life = 0;
		    tmp->smoke->vvx = VX_INIT*(((float)rand()/(float)RAND_MAX));
		    tmp->smoke->vvy = VY_INIT*(((float)rand()/(float)RAND_MAX));
		    tmp->smoke->vvz = VZ_INIT+(car->_speed_x * car->_speed_x + car->_speed_y * car->_speed_y)/10000;
		    tmp->smoke->vexp = V_EXPANSION;
		    tmp->smoke->smokeType = SMOKE_TYPE_TIRE;
		    tmp->next = NULL;
		    tmp->smoke->lastTime = GfTimeClock();
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
}

/** remove the smoke information for a car */
void grShutdownSmoke ()
{
    tgrSmoke *tmp, *tmp2;

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
    free(smokeManager);
    TheScene->removeKid(tsmoke);
    smokeManager = NULL;
    tsmoke = NULL;
    timeSmoke = NULL;

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

    alpha =  1.0-((float)(cur_life/max_life));
    glDepthMask(GL_FALSE);
    glDisable(GL_LIGHTING);

    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    /*glPolygonOffset(-5.0f, +10.0f);*/
    /*glEnable(GL_POLYGON_OFFSET_FILL);*/

    /* the principle is to have a right and up verctor 
       to determine how the points of the quadri should be placed
       orthoganly to the view, paralel to the screen.
       This alogo is inspired from the Cutout in Plib 
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
    /* down and up */
    A[0] = -right[0]-up[0];
    A[1] = -right[1]-up[1];
    A[2] = -right[2]-up[2];
    /* right and down */
    B[0] = right[0]-up[0];
    B[1] = right[1]-up[1];
    B[2] = right[2]-up[2];

    glBegin ( gltype ) ;
    glColor4f(0.9,0.9,0.9,alpha);
    if ( num_colours == 1 ) glColor4fv  ( cl [ 0 ] ) ;
    if ( num_normals == 1 ) glNormal3fv ( nm [ 0 ] ) ;
    /* the computed coordinates are translated from the smoke position
       with the x,y,z speed*/
    glTexCoord2f(0,0);
    glVertex3f(vx[0][0]+sizex*A[0]+vvx*dt,vx[0][1]+sizey*A[1]+vvy*dt, vx[0][2]+sizez*A[2]+vvz*dt);
    glTexCoord2f(0,1);
    glVertex3f(vx[0][0]+sizex*B[0]+vvx*dt,vx[0][1]+sizey*B[1]+vvy*dt, vx[0][2]+sizez*B[2]+vvz*dt);
    glTexCoord2f(1,0);
    glVertex3f(vx[0][0]+sizex*D[0]+vvx*dt,vx[0][1]+sizey*D[1]+vvy*dt, vx[0][2]+sizez*D[2]+vvz*dt);
    glTexCoord2f(1,1);
    glVertex3f(vx[0][0]+sizex*C[0]+vvx*dt,vx[0][1]+sizey*C[1]+vvy*dt, vx[0][2]+sizez*C[2]+vvz*dt);
    glEnd () ;
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
}
