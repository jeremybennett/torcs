/***************************************************************************

    file                 : grcar.cpp
    created              : Mon Aug 21 18:24:02 CEST 2000
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

#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>

#include <GL/glut.h>
#include <plib/ssg.h>

#include <tgf.h>
#include <track.h>
#include <car.h>
#include <graphic.h>
#include <robottools.h>

#include "grmain.h"
#include "grcar.h"
#include "grcam.h"
#include "grscene.h"
#include "grssgext.h"
#include "grutil.h"

static int
preCbEnv(ssgEntity *e)
{
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_EQUAL);
    glBlendFunc(GL_ZERO, GL_SRC_COLOR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    return TRUE;
}

static int
postCbEnv(ssgEntity *e)
{
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    return TRUE;
}

class myLoaderOptions : public ssgLoaderOptions
{
public:
  virtual void makeModelPath ( char* path, const char *fname ) const
  {
    ulFindFile ( path, model_dir, fname, NULL ) ;
  }

  virtual void makeTexturePath ( char* path, const char *fname ) const
  {
    ulFindFile ( path, texture_dir, fname, NULL ) ;
  }
} ;


static int grCarIndex;

static ssgSimpleState *brakeState = NULL;

static ssgTransform *
initWheel(tCarElt *car, int wheel_index)
{
    int		i, j, k;
    float	alpha;
    sgVec3	vtx;
    sgVec4	clr;
    sgVec3	nrm;
    sgVec2	tex;
    float	b_offset = 0;
    tdble	curAngle = 0.0;
    
    /* brake */
    if (brakeState == NULL) {
	brakeState = new ssgSimpleState;
	brakeState->disable(GL_LIGHTING);
	brakeState->disable(GL_TEXTURE_2D);
	brakeState->disable(GL_COLOR_MATERIAL);
    }

#define BRK_BRANCH	16
#define BRK_ANGLE	(2.0 * M_PI / (tdble)BRK_BRANCH)
#define BRK_OFFSET	0.1
    switch(wheel_index) {
    case FRNT_RGT:
	curAngle = -(M_PI / 2.0 + BRK_ANGLE);
	b_offset = BRK_OFFSET - car->_tireWidth(wheel_index) / 2.0;
	break;
    case FRNT_LFT:
	curAngle = -(M_PI / 2.0 + BRK_ANGLE);
	b_offset = car->_tireWidth(wheel_index) / 2.0 - BRK_OFFSET;
	break;
    case REAR_RGT:
	curAngle = (M_PI / 2.0 - BRK_ANGLE);
	b_offset = BRK_OFFSET - car->_tireWidth(wheel_index) / 2.0;
	break;
    case REAR_LFT:
	curAngle = (M_PI / 2.0 - BRK_ANGLE);
	b_offset = car->_tireWidth(wheel_index) / 2.0 - BRK_OFFSET;
	break;
    }

    /* hub */
    ssgVertexArray	*brk_vtx = new ssgVertexArray(BRK_BRANCH + 1);
    ssgColourArray	*brk_clr = new ssgColourArray(1);
    ssgNormalArray	*brk_nrm = new ssgNormalArray(1);
    tdble		hubRadius;
    
    /* center */
    vtx[0] = vtx[2] = 0.0;
    vtx[1] = b_offset;
    brk_vtx->add(vtx);
    
    hubRadius = car->_brakeDiskRadius(wheel_index) * 0.6;
    for (i = 0; i < BRK_BRANCH; i++) {
	alpha = (float)i * 2.0 * M_PI / (float)(BRK_BRANCH - 1);
	vtx[0] = hubRadius * cos(alpha);
	vtx[1] = b_offset;
	vtx[2] = hubRadius * sin(alpha);
	brk_vtx->add(vtx);
    }
    

    clr[0] = clr[1] = clr[2] = 0.0;
    clr[3] = 1.0;
    brk_clr->add(clr);
    nrm[0] = nrm[2] = 0.0;
    nrm[1] = 1.0;
    brk_nrm->add(nrm);
    
    ssgVtxTable *brk = new ssgVtxTable(GL_TRIANGLE_FAN, brk_vtx, brk_nrm, NULL, brk_clr);
    brk->setCullFace(0);
    brk->setState(brakeState);
  
    ssgTransform *wheel = new ssgTransform;
    wheel->addKid(brk);

    /* Brake disk */
    brk_vtx = new ssgVertexArray(BRK_BRANCH + 4);
    brk_clr = new ssgColourArray(1);
    brk_nrm = new ssgNormalArray(1);

    for (i = 0; i < (BRK_BRANCH / 2 + 2); i++) {
	alpha = curAngle + (float)i * 2.0 * M_PI / (float)(BRK_BRANCH - 1);
	vtx[0] = car->_brakeDiskRadius(wheel_index) * cos(alpha);
	vtx[1] = b_offset;
	vtx[2] = car->_brakeDiskRadius(wheel_index) * sin(alpha);
	brk_vtx->add(vtx);
	vtx[0] = car->_brakeDiskRadius(wheel_index) * cos(alpha) * 0.6;
	vtx[1] = b_offset;
	vtx[2] = car->_brakeDiskRadius(wheel_index) * sin(alpha) * 0.6;
	brk_vtx->add(vtx);
    }
    

    clr[0] = clr[1] = clr[2] = 0.1;
    clr[3] = 1.0;
    brk_clr->add(clr);
    nrm[0] = nrm[2] = 0.0;
    nrm[1] = 1.0;
    brk_nrm->add(nrm);
    
    brk = new ssgVtxTable(GL_TRIANGLE_STRIP, brk_vtx, brk_nrm, NULL, brk_clr);
    brk->setCullFace(0);
    brk->setState(brakeState);
    grCarInfo[grCarIndex].brkColor[wheel_index] = brk_clr;

    wheel->addKid(brk);

    /* Brake caliper */
    brk_vtx = new ssgVertexArray(BRK_BRANCH - 4);
    brk_clr = new ssgColourArray(1);
    brk_nrm = new ssgNormalArray(1);

    for (i = 0; i < (BRK_BRANCH / 2 - 2); i++) {
	alpha = - curAngle + (float)i * 2.0 * M_PI / (float)(BRK_BRANCH - 1);
	vtx[0] = (car->_brakeDiskRadius(wheel_index) + 0.02) * cos(alpha);
	vtx[1] = b_offset;
	vtx[2] = (car->_brakeDiskRadius(wheel_index) + 0.02) * sin(alpha);
	brk_vtx->add(vtx);
	vtx[0] = car->_brakeDiskRadius(wheel_index) * cos(alpha) * 0.6;
	vtx[1] = b_offset;
	vtx[2] = car->_brakeDiskRadius(wheel_index) * sin(alpha) * 0.6;
	brk_vtx->add(vtx);
    }
    

    clr[0] = 0.2;
    clr[1] = 0.2;
    clr[2] = 0.2;
    clr[3] = 1.0;
    brk_clr->add(clr);
    nrm[0] = nrm[2] = 0.0;
    nrm[1] = 1.0;
    brk_nrm->add(nrm);
    
    brk = new ssgVtxTable(GL_TRIANGLE_STRIP, brk_vtx, brk_nrm, NULL, brk_clr);
    brk->setCullFace(0);
    brk->setState(brakeState);

    wheel->addKid(brk);

    DBG_SET_NAME(wheel, "Wheel", grCarIndex, wheel_index);

    grCarInfo[grCarIndex].wheelPos[wheel_index] = wheel;

    /* wheels */
    ssgTransform *whrotation = new ssgTransform;
    grCarInfo[grCarIndex].wheelRot[wheel_index] = whrotation;
    wheel->addKid(whrotation);
    ssgSelector *whselector = new ssgSelector;
    whrotation->addKid(whselector);
    grCarInfo[grCarIndex].wheelselector[wheel_index] = whselector;
    
    float	wheelRadius = car->_rimRadius(wheel_index) + car->_tireHeight(wheel_index);

    for (j = 0; j < 4; j++) {
	static sgVec2	toffset[4] = { {0.0, 0.5}, {0.5, 0.5}, {0.0, 0.0}, {0.5, 0.0} };
	ssgBranch	*whl_branch = new ssgBranch;

#define WHL_BRANCH	16

	/* Tread */
	{
	    ssgVertexArray	*whl_vtx = new ssgVertexArray(2 * WHL_BRANCH);
	    ssgColourArray	*whl_clr = new ssgColourArray(2 * WHL_BRANCH);
	    ssgNormalArray	*whl_nrm = new ssgNormalArray(1);

	    whl_nrm->add(nrm);
	    clr[3] = 1.0;
	    for (i = 0; i < WHL_BRANCH; i++) {
		alpha = (float)i * 2.0 * M_PI / (float)(WHL_BRANCH - 1);
		vtx[0] = wheelRadius * cos(alpha);
		vtx[2] = wheelRadius * sin(alpha);
		vtx[1] = - car->_tireWidth(wheel_index) / 2.0;
		whl_vtx->add(vtx);
		vtx[1] = car->_tireWidth(wheel_index) / 2.0;
		whl_vtx->add(vtx);
		if (i % 2) {
		    clr[0] = clr[1] = clr[2] = 0.15;
		} else {
		    clr[0] = clr[1] = clr[2] = 0.0;
		}
		whl_clr->add(clr);
		whl_clr->add(clr);		
	    }
	    ssgVtxTable *whl = new ssgVtxTable(GL_TRIANGLE_STRIP, whl_vtx, whl_nrm, NULL, whl_clr);
	    whl->setState(brakeState);
	    whl->setCullFace(0);
	    whl_branch->addKid(whl);
	}
	    
    
    /* Rim */
	switch(wheel_index) {
	case FRNT_RGT:
	case REAR_RGT:
	    b_offset = -0.05;
	    break;
	case FRNT_LFT:
	case REAR_LFT:
	    b_offset = 0.05;
	    break;
	}
	for (k = 0; k < 2; k++) {
	    ssgVertexArray	*whl_vtx = new ssgVertexArray(WHL_BRANCH + 1);
	    ssgTexCoordArray	*whl_tex = new ssgTexCoordArray(WHL_BRANCH + 1);
	    ssgColourArray	*whl_clr = new ssgColourArray(1);
	    ssgNormalArray	*whl_nrm = new ssgNormalArray(1);
	
	    whl_clr->add(clr);
	    whl_nrm->add(nrm);
	    vtx[0] = vtx[2] = 0.0;
	    vtx[1] = (float)(2 * k - 1) * car->_tireWidth(wheel_index) / 2.0 - b_offset;
	    whl_vtx->add(vtx);
	    tex[0] = 0.25 + toffset[j][0];
	    tex[1] = 0.25 + toffset[j][1];
	    whl_tex->add(tex);
	    vtx[1] = (float)(2 * k - 1) * car->_tireWidth(wheel_index) / 2.0;
	    for (i = 0; i < WHL_BRANCH; i++) {
		alpha = (float)i * 2.0 * M_PI / (float)(WHL_BRANCH - 1);
		vtx[0] = wheelRadius * cos(alpha);
		vtx[2] = wheelRadius * sin(alpha);
		whl_vtx->add(vtx);
		tex[0] = 0.25 + 0.25 * cos(alpha) + toffset[j][0];
		tex[1] = 0.25 + 0.25 * sin(alpha) + toffset[j][1];
		whl_tex->add(tex);
	    }
	    ssgVtxTable *whl = new ssgVtxTable(GL_TRIANGLE_FAN, whl_vtx, whl_nrm, whl_tex, whl_clr);
	    whl->setState(grCarInfo[grCarIndex].wheelTexture);
	    whl->setCullFace(0);
	    whl_branch->addKid(whl);
	}

	whselector->addKid(whl_branch);
    }

/*     if (wheel_index == 1) { */
/* 	wheel->print(); */
/*     } */

    return wheel;
}


#define GR_SHADOW_POINTS	6

static void
initShadow(tCarElt *car)
{
    int			i;
    float		x;
    sgVec3		vtx;
    sgVec4		clr;
    sgVec3		nrm;
    ssgVertexArray	*shd_vtx = new ssgVertexArray(GR_SHADOW_POINTS+1);
    ssgColourArray	*shd_clr = new ssgColourArray(1);
    ssgNormalArray	*shd_nrm = new ssgNormalArray(1);

    clr[0] = clr[1] = clr[2] = 0.2;
    clr[3] = 0.7;
    shd_clr->add(clr);
    nrm[0] = nrm[1] = 0.0;
    nrm[2] = 1.0;
    shd_nrm->add(nrm);
    
    /* vertices */
    vtx[2] = 0.0;
    for (i = 0, x = car->_dimension_x / 2.0; i < GR_SHADOW_POINTS / 2; i++, x -= car->_dimension_x / (float)(GR_SHADOW_POINTS - 2) * 2.0) {
	vtx[0] = x;
	vtx[1] = car->_dimension_y / 2.0;
	shd_vtx->add(vtx);
	vtx[1] = -car->_dimension_y / 2.0;
	shd_vtx->add(vtx);
    };

    grCarInfo[car->index].shadowBase = new ssgVtxTable(GL_TRIANGLE_STRIP, shd_vtx, shd_nrm, NULL, shd_clr);
    grCarInfo[car->index].shadowBase->setState(brakeState);
    grCarInfo[car->index].shadowCurr = (ssgVtxTable *)grCarInfo[car->index].shadowBase->clone(SSG_CLONE_GEOMETRY);
    TheScene->addKid(grCarInfo[car->index].shadowCurr);
}


void 
grInitCar(tCarElt *car)
{
    char		buf[256];
    int			index;
    int			selIndex;
    ssgEntity		*carEntity;
    ssgSelector	*rangeSel;
    ssgBranchCb		*branchCb;
    int			nranges;
    int			i;
    void		*handle;
    char		*param;
    int			lg;
    char		path[256];
    myLoaderOptions	options ;

    TRACE_GL("loadcar: start");

    ssgSetCurrentOptions ( &options ) ;    

    selIndex = 0; 	/* current selector index */
    grCarIndex = index = car->index;	/* current car's index */
    handle = car->_carHandle;

    GfOut("[gr] Init(%d) car %s for driver %s index %d\n", index, car->_carName, car->_modName, car->_driverIndex);

    lg = 0;
    lg += sprintf(buf, "drivers/%s/%s;", car->_modName, car->_carName);
    lg += sprintf(buf, "drivers/%s/%d/%s;", car->_modName, car->_driverIndex, car->_carName);
    lg += sprintf(buf, "drivers/%s;", car->_modName);
    lg += sprintf(buf, "cars/%s;", car->_carName);
    grFilePath = (char*)malloc(lg);
    lg = 0;
    lg += sprintf(grFilePath + lg, "drivers/%s/%s;", car->_modName, car->_carName);
    lg += sprintf(grFilePath + lg, "drivers/%s/%d/%s;", car->_modName, car->_driverIndex, car->_carName);
    lg += sprintf(grFilePath + lg, "drivers/%s;", car->_modName);
    lg += sprintf(grFilePath + lg, "cars/%s", car->_carName);

    param = GfParmGetStr(handle, SECT_GROBJECTS, PRM_WHEEL_TEXTURE, "");
    if (strlen(param) != 0) {
	grGammaValue = 1.8;
	grMipMap = 0;
	grCarInfo[index].wheelTexture = grSsgLoadTexState(param);
    }
    free(param);
    
    /* BEWARE OF PLIB BUG in 1.2.0 this doesn't work!!! */
    grCarInfo[index].envSelector = (ssgStateSelector*)grEnvSelector->clone();
    grCarInfo[index].envSelector->ref();
    //grCarInfo[index].envSelector = grEnvSelector; // for PLIB 1.2.0

    /* the base transformation of the car (rotation + translation) */
    grCarInfo[index].carTransform = new ssgTransform;
    DBG_SET_NAME(grCarInfo[index].carTransform, car->_modName, index, -1);


    /* Level of details */
    grCarInfo[index].rangeSelector = rangeSel = new ssgSelector;
    grCarInfo[index].carTransform->addKid(rangeSel);
    sprintf(path, "%s/%s", SECT_GROBJECTS, LST_RANGES);
    nranges = GfParmGetEltNb(handle, path) + 1;
    if (nranges < 2) {
	GfOut("Error not enough levels of detail\n");
	free(grFilePath);
	grFilePath = NULL;
	return;
    }

    /* First LOD */
    ssgBranch *carBody = new ssgBranch;
    DBG_SET_NAME(carBody, "LOD", index,0);
    rangeSel->addKid(carBody);
    
    /* The car's model is under cars/<model> */
    sprintf(buf, "cars/%s", car->_carName);
    ssgModelPath(buf);
    sprintf(buf, "drivers/%s/%d;drivers/%s;cars/%s", car->_modName, car->_driverIndex, car->_modName, car->_carName);
    ssgTexturePath(buf);
    grTexturePath = strdup(buf);

    /* loading raw car level 0*/
    sprintf(buf, "%s.ac", car->_carName); /* default car name */
    sprintf(path, "%s/%s/1", SECT_GROBJECTS, LST_RANGES);
    param = GfParmGetStr(handle, path, PRM_CAR, buf);
    carEntity = ssgLoad(param);
    DBG_SET_NAME(carEntity, "Body", index, -1);
    free(param);
    carBody->addKid(carEntity);
    /* add wheels */
    for (i = 0; i < 4; i++){
	carBody->addKid(initWheel(car, i));
    }
    grCarInfo[index].selectMask[0] = 1 << selIndex; /* car mask */
    selIndex++;

    /* env map car */
    carEntity = (ssgEntity*)carEntity->clone(SSG_CLONE_RECURSIVE | SSG_CLONE_GEOMETRY);
    grForceState(carEntity, grCarInfo[grCarIndex].envSelector);
    branchCb = new ssgBranchCb;
    branchCb->addKid(carEntity);
    branchCb->setCallback(SSG_CALLBACK_PREDRAW, preCbEnv);
    branchCb->setCallback(SSG_CALLBACK_POSTDRAW, postCbEnv);
    DBG_SET_NAME(branchCb, "EnvMap", index, -1);
    carBody->addKid(branchCb);

    /* Other LODs */
    for (i = 2; i < nranges; i++) {
	carBody = new ssgBranch;
	sprintf(buf, "%s/%s/%d", SECT_GROBJECTS, LST_RANGES, i);
	param = GfParmGetStr(handle, buf, PRM_CAR, "");
	carEntity = ssgLoad(param);
	DBG_SET_NAME(carEntity, "LOD", index, i-1);
	free(param);
	carBody->addKid(carEntity);
	/* env map car */
	carEntity = (ssgEntity*)carEntity->clone(SSG_CLONE_RECURSIVE | SSG_CLONE_GEOMETRY);
	grForceState(carEntity, grCarInfo[grCarIndex].envSelector);
	branchCb = new ssgBranchCb;
	branchCb->addKid(carEntity);
	branchCb->setCallback(SSG_CALLBACK_PREDRAW, preCbEnv);
	branchCb->setCallback(SSG_CALLBACK_POSTDRAW, postCbEnv);
	DBG_SET_NAME(branchCb, "EnvMap", index, -1);
	carBody->addKid(branchCb);
	rangeSel->addKid(carBody);
	grCarInfo[index].selectMask[i-1] = 1 << selIndex; /* car mask */
	selIndex++;
    }
    /* default range selection */
    rangeSel->select(grCarInfo[index].selectMask[0]);

    TheScene->addKid(grCarInfo[index].carTransform);
    
    //grCarInfo[index].carTransform->print(stdout, "-", 1);

    free(grFilePath);
    free(grTexturePath);
    grFilePath = NULL;

    /* Shadow init */
    initShadow(car);
    
    TRACE_GL("loadcar: end");
}

void
grDrawShadow(tCarElt *car)
{
    int		i;
    ssgVtxTable	*shadow;
    sgVec3	*vtx;

    TheScene->removeKid(grCarInfo[car->index].shadowCurr);
    //delete grCarInfo[car->index].shadowCurr;
    shadow = (ssgVtxTable *)grCarInfo[car->index].shadowBase->clone(SSG_CLONE_GEOMETRY);
    shadow->setState(brakeState);
    shadow->setCullFace(0);
    shadow->getVertexList((void**)&vtx);
    
    shadow->transform(grCarInfo[car->index].carPos);
    
    for (i = 0; i < GR_SHADOW_POINTS; i++) {
	vtx[i][2] = RtTrackHeightG(car->_trkPos.seg, vtx[i][0], vtx[i][1]) + 0.02;
    }

    grCarInfo[car->index].shadowCurr = shadow;
    TheScene->addKid(shadow);
}


void
grDrawCar(tCarElt *car, tCarElt *curCar, int dispFlag)
{
    sgCoord	wheelpos;
    int		index, i, j;
    static float maxVel[3] = { 20.0, 40.0, 70.0 };
    
    TRACE_GL("cggrDrawCar: start");

    index = car->index;
  
    if ((car == curCar) && (dispFlag != 1)) {
	grCarInfo[index].rangeSelector->select(0);
    } else {
	grCarInfo[index].rangeSelector->select(1);	    
    }


    sgCopyMat4(grCarInfo[index].carPos, car->_posMat);
    grCarInfo[index].carTransform->setTransform(grCarInfo[index].carPos);

    grDrawShadow(car);
    
    /* Env mapping selection */
    grCarInfo[index].envSelector->selectStep(car->_trkPos.seg->envIndex);

    /* wheels */
    for (i = 0; i < 4; i++) {
	float	*clr;

	sgSetCoord(&wheelpos, car->priv->wheel[i].relPos.x, car->priv->wheel[i].relPos.y, car->priv->wheel[i].relPos.z,
		   RAD2DEG(car->priv->wheel[i].relPos.az), RAD2DEG(car->priv->wheel[i].relPos.ax), 0);
	grCarInfo[index].wheelPos[i]->setTransform(&wheelpos);
	sgSetCoord(&wheelpos, 0, 0, 0, 0, 0, RAD2DEG(car->priv->wheel[i].relPos.ay));
	grCarInfo[index].wheelRot[i]->setTransform(&wheelpos);
	for (j = 0; j < 3; j++) {
	    if (fabs(car->_wheelSpinVel(i)) < maxVel[j]) 
		break;
	}
	grCarInfo[index].wheelselector[i]->select(1<<j);
	clr = grCarInfo[index].brkColor[i]->get(0);
	clr[0] = 0.1 + car->_brakeTemp(i) * 1.5;
	clr[1] = 0.1 + car->_brakeTemp(i) * 0.3;
	clr[2] = 0.1 - car->_brakeTemp(i) * 0.3;
    }
    
    TRACE_GL("cggrDrawCar: end");
}

