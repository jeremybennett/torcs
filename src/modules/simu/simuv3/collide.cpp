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
extern tRmInfo ReInfo;

#define CAR_DAMMAGE	0.1

void SimCarCollideAddDeformation(tCar* car, sgVec3 pos, sgVec3 force)
{
	// just compute values, gr does deformation later.
	// must average position and add up force.
	tCollisionState* collision_state = &car->carElt->priv.collision_state;
	collision_state->collision_count++;
	//tdble k = (tdble) cnt;
	if (sgLengthVec3(collision_state->force) < sgLengthVec3(force)) {
		for (int i=0; i<3; i++) {
			collision_state->pos[i] = pos[i];// + k*collision_state->pos[i])/(k+1.0);
			collision_state->force[i] = 0.0001*force[i];// + k*collision_state->force[i])/(k+1.0);
			//printf ("F:%f\n", collision_state->force[i]);
		}
	}
}

void
SimCarCollideZ(tCar *car)
{
    int 	i;
    t3Dd	normal;
    t3Dd        rel_normal;
    tdble	dotProd;
    tWheel	*wheel;
    bool upside_down = false;

    if (car->carElt->_state & RM_CAR_STATE_NO_SIMU) {
		return;
    }

    
    t3Dd angles;

    RtTrackSurfaceNormalL(&(car->trkPos), &normal);
    
    angles.x = car->DynGCg.pos.ax;
    angles.y = car->DynGCg.pos.ay;
    angles.z = car->DynGCg.pos.az;
    NaiveRotate (normal, angles, &rel_normal);
    
    if (rel_normal.z > 0) {
		upside_down = false;
    } else {
		upside_down = true;
    }
    for (i = 0; i < 4; i++) {
		wheel = &(car->wheel[i]);
		if ((wheel->state & SIM_SUSP_COMP)
			||(rel_normal.z < 0)){
			t3Dd angles;
			t3Dd orig;
			t3Dd delta;

			t3Dd corner;

			bool flag = false;
			corner.z = -0.5;
			if (rel_normal.z <= 0) {
				orig.x = car->corner[i].pos.x;
				orig.y = car->corner[i].pos.y;
				orig.z = corner.z;
			} else {
				orig.x = 0.0;
				orig.y = 0.0;
				orig.z = wheel->susp.spring.packers - wheel->rideHeight;
				flag = true;
			}
			angles.x = car->DynGCg.pos.ax;
			angles.y = car->DynGCg.pos.ay;
			angles.z = car->DynGCg.pos.az;
			NaiveInverseRotate (orig, angles, &delta);
			if (((rel_normal.z <=0)
				 && (car->DynGCg.pos.z - delta.z < wheel->zRoad))
				|| (rel_normal.z > 0)) {
			
				//printf ("C[%d] %f (%f)\n", i, rel_normal.z, delta.z);
				if (rel_normal.z <= 0) {
					delta.z =  -(car->DynGCg.pos.z - delta.z - wheel->zRoad);
				}
				car->DynGCg.pos.z += delta.z;

				RtTrackSurfaceNormalL(&(wheel->trkPos), &normal);
				tdble cvx = (car->DynGCg.vel.x);
				tdble cvy = (car->DynGCg.vel.y);
				tdble cvz = (car->DynGCg.vel.z);

				//printf ("VS: %f %f\n", vx, car->DynGCg.vel.x);
				dotProd = (cvx * normal.x + cvy * normal.y + cvz * normal.z) * wheel->trkPos.seg->surface->kRebound;
				if (rel_normal.z < 0) {
					dotProd *=1.0;
				}
				if (dotProd < 0) {
					if (dotProd <-5.0) {
						car->collision |= 16;
						wheel->rotational_damage_x -= dotProd*0.01*urandom();
						wheel->rotational_damage_z -= dotProd*0.01*urandom();
						wheel->bent_damage_x += 0.1*urandom()-0.05;
						wheel->bent_damage_z += 0.1*urandom()-0.05;
						if (wheel->rotational_damage_x>0.25) {
							wheel->rotational_damage_x = 0.25;
						}
						if (wheel->rotational_damage_z>0.25) {
							wheel->rotational_damage_z = 0.25;
						}
						if (car->options->suspension_damage) {
							SimSuspDamage (&wheel->susp, dotProd+5);
						}
					}
					car->collision |= 9;

					{
						t3Dd N;
				
						N.x = - normal.x * dotProd;
						N.y = - normal.y * dotProd;
						N.z = - normal.z * dotProd;

						// reaction
						car->DynGCg.vel.x += N.x;
						car->DynGCg.vel.y += N.y;
						car->DynGCg.vel.z += N.z;

						// friction
						tdble c;
						if (rel_normal.z < 0) {
							c = 0.5;
						} else {
							c = 0.25;
						}
						car->DynGCg.vel.x = ConstantFriction (car->DynGCg.vel.x, c*dotProd*SIGN(car->DynGCg.vel.x));
						car->DynGCg.vel.y = ConstantFriction (car->DynGCg.vel.y, c*dotProd*SIGN(car->DynGCg.vel.y));
						car->DynGCg.vel.z = ConstantFriction (car->DynGCg.vel.z, c*dotProd*SIGN(car->DynGCg.vel.z));
				
					}
			
					if ((car->carElt->_state & RM_CAR_STATE_FINISH) == 0) {
						car->dammage += (int)(wheel->trkPos.seg->surface->kDammage * fabs(dotProd) * simDammageFactor[car->carElt->_skillLevel]);
					}

					NaiveRotate (normal, angles, &rel_normal);
					// dotProd = (car->DynGC.vel.x * rel_normal.x + car->DynGC.vel.y * rel_normal.y + car->DynGC.vel.z * rel_normal.z) * wheel->trkPos.seg->surface->kRebound;
					//	    printf ("%f\n", dotProd);
#if 1
					t3Dd direction;
					t3Dd updated;
					t3Dd original;
					angles.x = car->DynGCg.pos.ax;
					angles.y = car->DynGCg.pos.ay;
					angles.z = 0.0;
					original.x = 1.0;
					original.y = 0.0;
					original.z = 0.0;
					NaiveInverseRotate (original, angles, &updated);
					direction.x = SIGN(updated.x);
					direction.y = 1.0;
					angles.x = car->DynGCg.pos.ax;
					angles.y = car->DynGCg.pos.ay;
					angles.z = car->DynGCg.pos.az;
					original.x = 0.0;
					original.y = 0.0;
					original.z = 1.0;
					NaiveInverseRotate (original, angles, &updated);
					direction.z = SIGN(updated.z);
					if (1) {//rel_normal.z <= 0) {
						t3Dd forces;
						forces.x = -0.25*dotProd * rel_normal.x;
						forces.y = -0.25*dotProd * rel_normal.y;
						forces.z = -0.25*dotProd * rel_normal.z;
						t3Dd friction;
						cvx = car->corner[i].vel.x;
						cvy = car->corner[i].vel.y;
						cvz = car->corner[i].vel.z;

						tdble sum_v = sqrt(cvx*cvx + cvy*cvy + cvz*cvz);
						if (sum_v>1.0) {
							t3Dd fr_loc;
							friction.x = cvx/sum_v;
							friction.y = cvy/sum_v;
							friction.z = cvz/sum_v;
							NaiveRotate(friction, angles, &fr_loc);
							tdble C = 0.2 * dotProd;
							//printf ("V: %f %f %f\n",
							//car->DynGC.vel.x,
							//car->DynGC.vel.y,
							//car->DynGC.vel.z);
							//printf ("FR: (%f %f %f) k %f %f C %f\n",
							//fr_loc.x, 
							//fr_loc.y,
							//fr_loc.z,
							//wheel->trkPos.seg->surface->kRebound,
							//wheel->trkPos.seg->surface->kFriction,
							//C);
							forces.x += C*fr_loc.x;
							forces.y += C*fr_loc.y;
							forces.z += C*fr_loc.z;
							//printf ("%f %f\n", car->DynGC.vel.y, fr_loc.y);
							car->DynGC.vel.x += C*fr_loc.x;//*car->mass;
							car->DynGC.vel.y += C*fr_loc.y;//*car->mass;
							car->DynGC.vel.z += C*fr_loc.z;//*car->mass;

						}

						//						printf ("CZ: %f %f %f ->",
						//								car->rot_mom[SG_X],
						//								car->rot_mom[SG_Y],
						//								car->rot_mom[SG_Z]);
#if 1
						car->rot_mom[SG_X] += direction.x *
							car->mass *// car->Iinv.x *
							(forces.z * wheel->relPos.y
							 + forces.y * corner.z);
#endif
#if 1
						car->rot_mom[SG_Y] += direction.y*
							car->mass *// car->Iinv.y *
							(forces.z * wheel->relPos.x
							 + forces.x * corner.z);
#endif
#if 1
						car->rot_mom[SG_Z] += direction.z*
							car->mass * //car->Iinv.z *
							(forces.x * wheel->relPos.y +
							 -forces.y * wheel->relPos.x);
#endif
//						printf ("%f %f %f\n",
//								car->rot_mom[SG_X],
//								car->rot_mom[SG_Y],
//								car->rot_mom[SG_Z]);

						car->DynGCg.vel.ax*=.9;
						car->DynGCg.vel.ay*=.9;
						car->DynGCg.vel.az*=.9;
						//printf ("%d %d %d\n", SG_X, SG_Y, SG_Z);
						for (int i=0; i<3; i++) {
							if (fabs(car->rot_mom[i])>2.0*car->mass) {
								car->rot_mom[i] = 2.0*car->mass * SIGN(car->rot_mom[i]);
							}
						}
						car->rot_mom[SG_X]*=.999;
						car->rot_mom[SG_Y]*=.999;
						car->rot_mom[SG_Z]*=.999;
					}
#endif
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
			RtTrackSideNormalG(seg, corner->pos.ax, corner->pos.ay, TR_RGT, &normal);
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
			RtTrackSideNormalG(seg, corner->pos.ax, corner->pos.ay, TR_LFT, &normal);
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
		initDotProd = nx * corner->vel.x + ny * corner->vel.y;

		dotProd = initDotProd * curBarrier->surface->kFriction;
		car->DynGCg.vel.x -= nx * dotProd;
		car->DynGCg.vel.y -= ny * dotProd;
		{ // Transfer back to interface
			t3Dd angles;
			t3Dd rel_normal;
			angles.x = car->DynGCg.pos.ax;
			angles.y = car->DynGCg.pos.ay;
			angles.z = car->DynGCg.pos.az;
			NaiveRotate (normal, angles, &rel_normal);
			car->DynGC.acc.x -= rel_normal.x * dotProd/SimDeltaTime;
			car->DynGC.acc.y -= rel_normal.y * dotProd/SimDeltaTime;
			car->carElt->_accel_x -= rel_normal.x * dotProd/SimDeltaTime;
			car->carElt->_accel_y -= rel_normal.y * dotProd/SimDeltaTime;
		}
		dotprod2 = (nx * cx + ny * cy);
#if 0
		car->DynGCg.vel.az -= dotprod2 * dotProd / 10.0;
		if (fabs(car->DynGCg.vel.az) > 6.0) {
			car->DynGCg.vel.az = SIGN(car->DynGCg.vel.az) * 6.0;
		}
#else 
		car->rot_mom[SG_Z] +=  dotprod2 * dotProd / 10.0;
#endif
	
		/* rebound */
		dotProd = initDotProd;
		dmg = 0;
		if (dotProd<0) {
			if ((car->carElt->_state & RM_CAR_STATE_FINISH) == 0) {
				//dmg = curBarrier->surface->kDammage * fabs(dotProd) * simDammageFactor[car->carElt->_skillLevel];
				dmg = curBarrier->surface->kDammage * (0.5*initDotProd*initDotProd) * simDammageFactor[car->carElt->_skillLevel];
				car->dammage += (int)dmg;
				//printf("COL:%f \n", dmg);
			}
		}
		dotProd *= curBarrier->surface->kRebound;
		/* dotprod2 = (nx * cx + ny * cy); */

		if (dotProd < 0) {
			//tdble len_n = sqrt(normal.x * normal.x + normal.y * normal.y);
			car->collision |= 2;
			car->normal.x = normal.x * dmg;
			car->normal.y = normal.y * dmg;
			car->collpos.x = corner->pos.ax;//*cos_n + corner->pos.ay * sin_n;
			car->collpos.y = corner->pos.ay;//*cos_n + corner->pos.ax * sin_n;
			sgVec3 force;

			tdble invK = 0.01;
			force[0] = invK * nx * dmg;//dotProd;
			force[1] = invK * ny * dmg;//dotProd;
			force[2] = invK * (urandom()-0.5)*0.1;

			//printf ("- %f -\n", sgLengthVec3 (force));
			/* collision detected */
			car->DynGCg.vel.x -= nx * dotProd;
			car->DynGCg.vel.y -= ny * dotProd;
			{ // Transfer back to interface
				t3Dd angles;
				t3Dd rel_normal;
				angles.x = car->DynGCg.pos.ax;
				angles.y = car->DynGCg.pos.ay;
				angles.z = car->DynGCg.pos.az;
				NaiveRotate (normal, angles, &rel_normal);
				car->DynGC.acc.x -= rel_normal.x * dotProd/SimDeltaTime;
				car->DynGC.acc.y -= rel_normal.y * dotProd/SimDeltaTime;
				car->carElt->_accel_x -= rel_normal.x * dotProd/SimDeltaTime;
				car->carElt->_accel_y -= rel_normal.y * dotProd/SimDeltaTime;
			}
			/* car->DynGCg.vel.az -= dotprod2 * dotProd * 0.2; */
			if (sgLengthVec3 (force) > 0.01) {
				sgVec3 poc;
				poc[0] = corner->pos.x;
				poc[1] = corner->pos.y;
				poc[2] = (urandom()-0.5)*2.0;
				t3Dd angles;
				t3Dd original;
				t3Dd updated;
				angles.x = car->DynGCg.pos.ax;
				angles.y = car->DynGCg.pos.ay;
				angles.z = car->DynGCg.pos.az;	
			
				original.x = force[0];
				original.y = force[1];
				original.z = force[2];
				NaiveRotate (original, angles, &updated);
				force[0] = updated.x;
				force[1] = updated.y;
				force[2] = updated.z;
				sgNormaliseVec3(force);
				for (int i=0; i<3; i++) {
					force[i]*=dmg;
				}
				// just compute values, gr does deformation later.
				// must average position and add up force.
				SimCarCollideAddDeformation(car, poc, force);

				// add aero damage if applicable
				if (car->options->aero_damage) {
					SimAeroDamage (car, poc, sgLengthVec3(force));
				}
			}
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

    sgVec3	n, p1, p2;
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
	float dmg1 = 0.0;
    if ((car1->carElt->_state & RM_CAR_STATE_FINISH) == 0) {
		dmg1 = (CAR_DAMMAGE * (0.0002*j*j) * damFactor * simDammageFactor[car1->carElt->_skillLevel]);
		car1->dammage += (int) dmg1;
		//printf("COL1:%f \n", dmg1);
    }

    atmp = atan2(rbp[1], rbp[0]);
    if (fabs(atmp) < (PI / 3.0)) {
		damFactor = 1.5;
    } else {
		damFactor = 1.0;
    }
    /* printf("Coll %d -> %f - %f %f %f \n---\n", car2->carElt->index, damFactor, atan2(rbp[1], rbp[0]), car2->carElt->_yaw, atmp); */
	float dmg2=0.0;
    if ((car2->carElt->_state & RM_CAR_STATE_FINISH) == 0) {
		dmg2 = (CAR_DAMMAGE * (0.0002*j*j) * damFactor * simDammageFactor[car2->carElt->_skillLevel]);
		car2->dammage += (int) dmg2;
		//printf("COL2:%f \n", dmg2);
    }


	{
		sgVec3 force;
		tdble invK = 0.005;
		force[0] = -invK * v1ab[0] * v1ab[0] * fabs(n[0]);
		force[1] = -invK * v1ab[1] * v1ab[1] * fabs(n[1]);
		force[2] = 0;
		if (sgLengthVec3 (force) > 0.1) {
			tdble h=urandom()-0.5;
			p1[2] = h;
			p2[2] = h;
			t3Dd angles;
			t3Dd original;
			t3Dd updated;
			sgVec3 f;
			angles.x = car1->DynGCg.pos.ax;
			angles.y = car1->DynGCg.pos.ay;
			angles.z = car1->DynGCg.pos.az;	
			original.x = force[0];
			original.y = force[1];
			original.z = force[2];
			NaiveRotate (original, angles, &updated);
			f[0] = updated.x;
			f[1] = updated.y;
			f[2] = updated.z;
			//printf ("* %f *\n", sgLengthVec3 (force));
			//car1->ReInfo->_reGraphicItf.bendcar(car1->carElt->index, p1, f, 0);
#if 1
			sgNormaliseVec3(f);
			for (int i=0; i<3; i++) {
				f[i]*=dmg1;
			}
#endif
			SimCarCollideAddDeformation(car1, p1, f);
			sgNegateVec3 (force);
			angles.x = car2->DynGCg.pos.ax;
			angles.y = car2->DynGCg.pos.ay;
			angles.z = car2->DynGCg.pos.az;	
			original.x = force[0];
			original.y = force[1];
			original.z = force[2];
			NaiveRotate (original, angles, &updated);
			f[0] = updated.x;
			f[1] = updated.y;
			f[2] = updated.z;
#if 1
			sgNormaliseVec3(f);
			for (int i=0; i<3; i++) {
				f[i]*=dmg2;
			}
#endif
			SimCarCollideAddDeformation(car2, p2, f);
		}
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
			tdble delta = car->VelColl.az - car->DynGCg.vel.az;
			car->DynGCg.vel.az = car->VelColl.az;
			car->rot_mom[SG_Z] = car->VelColl.az/car->Iinv.z;
			//car->rot_mom[SG_Z] -= delta/car->Iinv.z;
		}
    }
}


extern tdble ConstantFriction (tdble u, tdble du)
{
	tdble u2 = u + du;
	if (u*du > 0.0) {
		return u;
	}
	if (u2*u <= 0.0)
		return 0.0;
	return u2;
}
extern tdble ConstantFriction (tdble u, tdble a, tdble dt)
{
	return ConstantFriction (u, a*dt);
}
