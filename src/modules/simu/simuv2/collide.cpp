/***************************************************************************

    file                 : collide.cpp
    created              : Sun Mar 19 00:06:19 CET 2000
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

#include "sim.h"

#define CAR_DAMMAGE	0.1


void
SimCarCollideZ(tCar *car)
{
    int 	i;
    t3Dd	normal;
    tdble	dotProd;
    tWheel	*wheel;
	const float CRASH_THRESHOLD = -5.0f;

    if (car->carElt->_state & RM_CAR_STATE_NO_SIMU) {
	return;
    }

    for (i = 0; i < 4; i++) {
	wheel = &(car->wheel[i]);
	if (wheel->state & SIM_SUSP_COMP) {
	    //car->DynGCg.pos.z += wheel->susp.x - wheel->rideHeight;
	    car->DynGCg.pos.z += wheel->susp.spring.packers - wheel->rideHeight;

/* 	    if ((car->DynGCg.vel.ax * wheel->staticPos.y) < 0) { */
/* 		car->DynGCg.vel.ax = 0; */
/* 	    } */
/* 	    if ((car->DynGCg.vel.ay * wheel->staticPos.x) < 0) {  */
/* 		car->DynGCg.vel.ay = 0; */
/* 	    } */
	    RtTrackSurfaceNormalL(&(wheel->trkPos), &normal);
	    dotProd = (car->DynGCg.vel.x * normal.x + car->DynGCg.vel.y * normal.y + car->DynGCg.vel.z * normal.z) * wheel->trkPos.seg->surface->kRebound;
	    if (dotProd < 0) {
	    if (dotProd < CRASH_THRESHOLD) {car->collision |= 16;}		
		car->collision |=9;
		car->DynGCg.vel.x -= normal.x * dotProd;
		car->DynGCg.vel.y -= normal.y * dotProd;
		car->DynGCg.vel.z -= normal.z * dotProd;
		if ((car->carElt->_state & RM_CAR_STATE_FINISH) == 0) {
		    car->dammage += (int)(wheel->trkPos.seg->surface->kDammage * fabs(dotProd) * simDammageFactor[car->carElt->_skillLevel]);
		}
	    }
	}
    }
}

const tdble BorderFriction = 0.00;

void
SimCarCollideXYScene(tCar *car)
{
    tTrackSeg	*seg = car->trkPos.seg;
    tTrkLocPos	trkpos;
    int		i;
    tDynPt	*corner;
    t3Dd	normal;
    tdble	initDotProd;
    tdble	dotProd, nx, ny, cx, cy, dotprod2;
    tTrackBarrier *curBarrier;
    tdble	dmg;

    if (car->carElt->_state & RM_CAR_STATE_NO_SIMU) {
		return;
    }

	//int segtype = seg->type;

	corner = &(car->corner[0]);
	for (i = 0; i < 4; i++, corner++) {
		cx = corner->pos.ax - car->DynGCg.pos.x;
		cy = corner->pos.ay - car->DynGCg.pos.y;
		seg = car->trkPos.seg;
		RtTrackGlobal2Local(seg, corner->pos.ax, corner->pos.ay, &trkpos, TR_LPOS_TRACK);
		seg = trkpos.seg;
		if (trkpos.toRight < 0.0) {
			/* collision with right border */
			curBarrier = seg->barrier[0];
			if (seg->rside != NULL) {
				seg = seg->rside;
				if (seg->rside != NULL) {
					seg = seg->rside;
				}
			}
			// TODO: Does not work, always parallel to track (fix in trackX.cpp?)!
			//RtTrackSideNormalG(seg, corner->pos.ax, corner->pos.ay, TR_RGT, &normal);
			// Temporary fix:
			tdble nx = seg->vertex[TR_ER].x - seg->vertex[TR_SR].x;
			tdble ny = seg->vertex[TR_ER].y - seg->vertex[TR_SR].y;
			normal.x = -ny;
			normal.y = nx;
			tdble len = sqrt(normal.x*normal.x + normal.y*normal.y);
			normal.x /= len;
			normal.y /= len;

			car->DynGCg.pos.x -= normal.x * trkpos.toRight;
			car->DynGCg.pos.y -= normal.y * trkpos.toRight;
		} else if (trkpos.toLeft < 0.0) {
			/* collision with left border */
			curBarrier = seg->barrier[1];
			if (seg->lside != NULL) {
				seg = seg->lside;
				if (seg->lside != NULL) {
					seg = seg->lside;
				}
			}
			// TODO: Does not work, always parallel to track(fix in trackX.cpp?)!
			//RtTrackSideNormalG(seg, corner->pos.ax, corner->pos.ay, TR_LFT, &normal);
			// Temporary fix:
			tdble nx = seg->vertex[TR_EL].x - seg->vertex[TR_SL].x;
			tdble ny = seg->vertex[TR_EL].y - seg->vertex[TR_SL].y;
			normal.x = ny;
			normal.y = -nx;
			tdble len = sqrt(normal.x*normal.x + normal.y*normal.y);
			normal.x /= len;
			normal.y /= len;

			car->DynGCg.pos.x -= normal.x * trkpos.toLeft;
			car->DynGCg.pos.y -= normal.y * trkpos.toLeft;
		} else {
			continue;
		}

		car->blocked = 1;
		/* friction */
		car->collision |= 1;
		nx = normal.x;
		ny = normal.y;

		// Impact speed perpendicular to barrier (of corner).
		initDotProd = nx * corner->vel.x + ny * corner->vel.y;
		
		// TODO: This bit doesn't work so swell.
		// look below for choice between dmg and dmg2.
		// Test whether new corner speed calculation fixes bug
		// of high damage when dotProd is used instead of dmgDotProd.
		// Simuv3 does not seem to have this problem.
		tdble absvel = MAX(1.0, sqrt(car->DynGCg.vel.x*car->DynGCg.vel.x + car->DynGCg.vel.y*car->DynGCg.vel.y));
		tdble GCgnormvel = car->DynGCg.vel.x*normal.x + car->DynGCg.vel.y*normal.y;
		tdble cosa = GCgnormvel/absvel;
		tdble dmgDotProd = GCgnormvel*cosa;

		dotProd = initDotProd * curBarrier->surface->kFriction;
		car->DynGCg.vel.x -= nx * dotProd;
		car->DynGCg.vel.y -= ny * dotProd;
		dotprod2 = (nx * cx + ny * cy);
		car->DynGCg.vel.az -= dotprod2 * dotProd / 10.0;
		if (fabs(car->DynGCg.vel.az) > 6.0) {
			car->DynGCg.vel.az = SIGN(car->DynGCg.vel.az) * 6.0;
		}

		/* rebound */
		dotProd = initDotProd;
		dmg = 0;
		if (dotProd < 0 &&
			(car->carElt->_state & RM_CAR_STATE_FINISH) == 0) {
			dmg = curBarrier->surface->kDammage * fabs(dotProd) * simDammageFactor[car->carElt->_skillLevel];
			tdble dmg2 = curBarrier->surface->kDammage * fabs(0.5*dmgDotProd*dmgDotProd) * simDammageFactor[car->carElt->_skillLevel];
			//tdble dmg2 = curBarrier->surface->kDammage * fabs(0.5*dotProd*dotProd) * simDammageFactor[car->carElt->_skillLevel];
			//car->dammage += (int)dmg;
			car->dammage += (int)dmg2;
		}
		dotProd *= curBarrier->surface->kRebound;
		/* dotprod2 = (nx * cx + ny * cy); */

		// If the car moves toward the barrier, rebound.
		if (dotProd < 0) {
			car->collision |= 2;
			car->normal.x = normal.x * dmg;
			car->normal.y = normal.y * dmg;
			car->collpos.x = corner->pos.ax;
			car->collpos.y = corner->pos.ay;

			//printf("nx: %f, ny: %f\n", nx, ny);

			/* collision detected */
			car->DynGCg.vel.x -= nx * dotProd;
			car->DynGCg.vel.y -= ny * dotProd;
			/* car->DynGCg.vel.az -= dotprod2 * dotProd * 0.2; */

		}
    }
}

static void
SimCarCollideResponse(void * /*dummy*/, DtObjectRef obj1, DtObjectRef obj2, const DtCollData *collData)
{
    tCar	*car1 = (tCar*)obj1;
    tCar	*car2 = (tCar*)obj2;
    tCarElt	*carElt;
    tdble	damFactor, atmp;

    sgVec2	n, p1, p2;
    sgVec2	v1ap, v1bp, v1ab;
    sgVec2	rap, rbp;
    sgVec2	v2a, v2b;
    sgVec2	tmpv;
    sgVec3	pa, pb, pab ;

    float	j;		/* impulse */
    float	rapn, rbpn;
    float	distpab;

    float	e = 1.0;	/* energy restitution */
    
    if ((car1->carElt->_state & RM_CAR_STATE_NO_SIMU) ||
	(car2->carElt->_state & RM_CAR_STATE_NO_SIMU)) {
	return;
    }

    if (car1->carElt->index < car2->carElt->index) {
	/* vector conversion from double to float */
	p1[0] = (float)collData->point1[0];
	p1[1] = (float)collData->point1[1];
	p2[0] = (float)collData->point2[0];
	p2[1] = (float)collData->point2[1];
	n[0]  = (float)collData->normal[0];
	n[1]  = (float)collData->normal[1];
    } else {
	/* swap the cars (not the same for the simu) */
	car1 = (tCar*)obj2;
	car2 = (tCar*)obj1;
	p1[0] = (float)collData->point2[0];
	p1[1] = (float)collData->point2[1];
	p2[0] = (float)collData->point1[0];
	p2[1] = (float)collData->point1[1];
	n[0]  = -(float)collData->normal[0];
	n[1]  = -(float)collData->normal[1];
    }

    if ((isnan(p1[0]) ||
	 isnan(p1[1]) ||
	 isnan(p2[0]) ||
	 isnan(p2[1]) ||
	 isnan(n[0])  ||
	 isnan(n[1]))) {
	/* I really don't know where the problem is... */
	GfOut ("Collide failed 1 (%s - %s)\n", car1->carElt->_name, car2->carElt->_name);
	return;
    }

    if (sgLengthVec2 (n) == 0.0) {
	/* I really don't know where the problem is... */
	GfOut ("Collide failed 2 (%s - %s)\n", car1->carElt->_name, car2->carElt->_name);
	return;
    }

    sgNormaliseVec2 (n);

/*     printf("Coll %d <> %d : (%f, %f) - (%f, %f) - (%f, %f)\n", */
/* 	   car1->carElt->index, car2->carElt->index, */
/* 	   p1[0], p1[1], */
/* 	   p2[0], p2[1], */
/* 	   n[0], n[1]); */

    /* vector GP */
    sgSubVec2(rap, p1, (const float*)&(car1->statGC));
    sgSubVec2(rbp, p2, (const float*)&(car2->statGC));
    
    /* speed of collision points */
    v1ap[0] = car1->DynGCg.vel.x - car1->DynGCg.vel.az * rap[1];
    v1ap[1] = car1->DynGCg.vel.y + car1->DynGCg.vel.az * rap[0];
    v1bp[0] = car2->DynGCg.vel.x - car2->DynGCg.vel.az * rbp[1];
    v1bp[1] = car2->DynGCg.vel.y + car2->DynGCg.vel.az * rbp[0];
    
    /* relative speed */
    sgSubVec2(v1ab, v1ap, v1bp);
/*     printf("Coll %d <> %d : vab = %f\n", car1->carElt->index, car2->carElt->index, sgLengthVec2(v1ab)); */

    /* try to separate the cars */
    sgCopyVec2(pa, rap);
    sgCopyVec2(pb, rbp);
    pa[2] = pb[2] = 0;
    sgFullXformPnt3(pa, car1->carElt->_posMat);
    sgFullXformPnt3(pb, car2->carElt->_posMat);
    sgSubVec2(pab, pb, pa);
    distpab = sgLengthVec2(pab);
/*     printf("Coll %d <> %d : (%f, %f) - (%f, %f) dist = %f\n", */
/* 	   car1->carElt->index, car2->carElt->index, */
/* 	   pa[0], pa[1], pb[0], pb[1], */
/* 	   distpab); */
/*     printf("Coll %d <> %d : dist = %f\n", car1->carElt->index, car2->carElt->index, distpab); */
/*     if (distpab > 1.0) { */
/* 	return; */
/*     } */
    
    if ((car1->blocked == 0) && (car2->blocked == 0)) {
	/* move the 2 cars */
	sgScaleVec2(tmpv, n, MIN(distpab, 0.05));
	sgAddVec2((float*)&(car1->DynGCg.pos), tmpv);
	sgSubVec2((float*)&(car2->DynGCg.pos), tmpv);
	car1->blocked = 1;
	car2->blocked = 1;
    } else if (car1->blocked == 0) {
	sgScaleVec2(tmpv, n, MIN(distpab, 0.05));	
	sgAddVec2((float*)&(car1->DynGCg.pos), tmpv);
	car1->blocked = 1;
    } else if (car2->blocked == 0) {
	sgScaleVec2(tmpv, n, MIN(distpab, 0.05));	
	sgSubVec2((float*)&(car2->DynGCg.pos), tmpv);
	car2->blocked = 1;
    }

    if (sgScalarProductVec2(v1ab, n) > 0) {
	return;
    }
    
    /* impulse */
    rapn = sgScalarProductVec2(rap, n);
    rbpn = sgScalarProductVec2(rbp, n);
    
    
    j = -(1 + e) * sgScalarProductVec2(v1ab, n) /
	((car1->Minv + car2->Minv) +
	 rapn * rapn * car1->Iinv.z + rbpn * rbpn * car2->Iinv.z);
    
    assert (!isnan(j));
    
    atmp = atan2(rap[1], rap[0]);
    if (fabs(atmp) < (PI / 3.0)) {
	damFactor = 1.5;
    } else {
	damFactor = 1.0;
    }
    /* printf("Coll %d -> %f - %f %f %f \n", car1->carElt->index, damFactor, atan2(rap[1], rap[0]), car1->carElt->_yaw, atmp); */
    if ((car1->carElt->_state & RM_CAR_STATE_FINISH) == 0) {
	car1->dammage += (int)(CAR_DAMMAGE * (0.0002*j*j) * damFactor * simDammageFactor[car1->carElt->_skillLevel]);
    }

    atmp = atan2(rbp[1], rbp[0]);
    if (fabs(atmp) < (PI / 3.0)) {
	damFactor = 1.5;
    } else {
	damFactor = 1.0;
    }
    /* printf("Coll %d -> %f - %f %f %f \n---\n", car2->carElt->index, damFactor, atan2(rbp[1], rbp[0]), car2->carElt->_yaw, atmp); */
    if ((car2->carElt->_state & RM_CAR_STATE_FINISH) == 0) {
	car2->dammage += (int)(CAR_DAMMAGE * (0.0002*j*j) * damFactor * simDammageFactor[car2->carElt->_skillLevel]);
    }
    
/*     if (j < 0) { */
/* 	return; */
/*     } */
    
    
/*     printf("Coll %d <> %d : j = %f\n", car1->carElt->index, car2->carElt->index, j); */

#define ROT_K	0.5

/*     printf("Vel %d : %f (%f, %f, %f) -> ", car1->carElt->index, j, */
/* 	   car1->DynGCg.vel.x, car1->DynGCg.vel.y, car1->DynGCg.vel.az); */

    sgScaleVec2(tmpv, n, j * car1->Minv);
    if (car1->collision & 4) {
	sgAddVec2(v2a, (const float*)&(car1->VelColl.x), tmpv);
	car1->VelColl.az = car1->VelColl.az + j * rapn * car1->Iinv.z * ROT_K;
    } else {
	sgAddVec2(v2a, (const float*)&(car1->DynGCg.vel), tmpv);
	car1->VelColl.az = car1->DynGCg.vel.az + j * rapn * car1->Iinv.z * ROT_K;
    }
    if (fabs(car1->VelColl.az) > 3.0) {
	car1->VelColl.az = SIGN(car1->VelColl.az) * 3.0;
    }
    
    sgCopyVec2((float*)&(car1->VelColl.x), v2a);

    /* Move the car for the collision lib */
    carElt = car1->carElt;
    sgMakeCoordMat4(carElt->pub.posMat, car1->DynGCg.pos.x, car1->DynGCg.pos.y, car1->DynGCg.pos.z - carElt->_statGC_z,
		    RAD2DEG(carElt->_yaw), RAD2DEG(carElt->_roll), RAD2DEG(carElt->_pitch));

    dtSelectObject(car1);
    dtLoadIdentity();
    dtTranslate(-carElt->_statGC_x, -carElt->_statGC_y, 0);
    dtMultMatrixf((const float *)(carElt->_posMat));

/*     printf("(%f, %f, %f)\n", car1->DynGCg.vel.x, car1->DynGCg.vel.y, car1->DynGCg.vel.az); */

/*     printf("Vel %d : %f (%f, %f, %f) -> ", car2->carElt->index, j, */
/* 	   car2->DynGCg.vel.x, car2->DynGCg.vel.y, car2->DynGCg.vel.az); */
    
    sgScaleVec2(tmpv, n, -j * car2->Minv);
    if (car2->collision & 4) {
	sgAddVec2(v2b, (const float*)&(car2->VelColl), tmpv);
	car2->VelColl.az = car2->VelColl.az - j * rbpn * car1->Iinv.z * ROT_K;
    } else {
	sgAddVec2(v2b, (const float*)&(car2->DynGCg.vel), tmpv);
	car2->VelColl.az = car2->DynGCg.vel.az - j * rbpn * car1->Iinv.z * ROT_K;
    }
    if (fabs(car2->VelColl.az) > 3.0) {
	car2->VelColl.az = SIGN(car2->VelColl.az) * 3.0;
    }
    sgCopyVec2((float*)&(car2->VelColl), v2b);

    /* Move the car for the collision lib */
    carElt = car2->carElt;
    sgMakeCoordMat4(carElt->pub.posMat, car2->DynGCg.pos.x, car2->DynGCg.pos.y, car2->DynGCg.pos.z - carElt->_statGC_z,
		    RAD2DEG(carElt->_yaw), RAD2DEG(carElt->_roll), RAD2DEG(carElt->_pitch));
    dtSelectObject(car2);
    dtLoadIdentity();
    dtTranslate(-carElt->_statGC_x, -carElt->_statGC_y, 0);
    dtMultMatrixf((const float *)(carElt->_posMat));

/*     printf("(%f, %f, %f)\n", car2->DynGCg.vel.x, car2->DynGCg.vel.y, car2->DynGCg.vel.az); */
    
    car1->collision |= 4;
    car2->collision |= 4;

}

void
SimCarCollideShutdown(int nbcars)
{
    int  i;
    
    for (i = 0; i < nbcars; i++) {
	dtDeleteShape(SimCarTable[i].shape);
	dtDeleteObject(&(SimCarTable[i]));
    }
    dtClearDefaultResponse();
}


void 
SimCarCollideConfig(tCar *car)
{
    tCarElt *carElt;
    
    carElt = car->carElt;
    // The current car shape is a box...
    car->shape = dtBox(carElt->_dimension_x, carElt->_dimension_y, carElt->_dimension_z);
    dtCreateObject(car, car->shape);

    car->collisionAware = 1;
}

void
SimCarCollideInit(void)
{
    dtSetDefaultResponse(SimCarCollideResponse, DT_SMART_RESPONSE, NULL);
    dtDisableCaching();
    dtSetTolerance(0.001);
}


void
SimCarCollideCars(tSituation *s)
{
    tCar	*car;
    tCarElt	*carElt;
    int		i;
    
    for (i = 0; i < s->_ncars; i++) {
	carElt = s->cars[i];
	car = &(SimCarTable[carElt->index]);
	dtSelectObject(car);
	dtLoadIdentity();
	dtTranslate(-carElt->_statGC_x, -carElt->_statGC_y, 0);
	dtMultMatrixf((const float *)(carElt->_posMat));
	memset(&(car->VelColl), 0, sizeof(tPosd));
    }

    if (dtTest() == 0) {
	dtProceed();
    }

    for (i = 0; i < s->_ncars; i++) {
	carElt = s->cars[i];
	if (carElt->_state & RM_CAR_STATE_NO_SIMU) {
	    continue;
	}
	car = &(SimCarTable[carElt->index]);
	if (car->collision & 4) {
	    car->DynGCg.vel.x = car->VelColl.x;
	    car->DynGCg.vel.y = car->VelColl.y;
	    car->DynGCg.vel.az = car->VelColl.az;
	}
    }
}

