
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

static ssgSimpleState *skidState = NULL;

/** initialize the skidmak structure for a car*/
void grInitSkidmarks(tCarElt *car)
{
  int i=0; 
  int k=0;
/*   float	b_offset = 0; */
  /*  sgVec3 vtx;*/
  sgVec4		clr;
  ssgColourArray	*shd_clr = new ssgColourArray(1);
  ssgNormalArray	*shd_nrm = new ssgNormalArray(1);
  sgVec3		nrm;

  clr[0] = clr[1] = clr[2] = 0.2;
  clr[3] = 0.7;
  shd_clr->add(clr);
  nrm[0] = nrm[1] = 0.0;
  nrm[2] = 1.0;
  shd_nrm->add(nrm);
/*   ssgVertexArray * basevtx=new ssgVertexArray(4*2+1); */

  if (skidState == NULL) {
    skidState = new ssgSimpleState;
    skidState->disable(GL_LIGHTING);
    skidState->disable(GL_TEXTURE_2D);
    skidState->disable(GL_COLOR_MATERIAL);
  }
      
  grCarInfo[car->index].skidmarks=(tgrSkidmarks *)malloc (sizeof(tgrSkidmarks));
  for (i=0; i<4; i++)
    {
      for (k=0; k<MAXSTRIP_BYWHEEL; k++)
	{
	  grCarInfo[car->index].skidmarks->strips[i].state[k]=SKID_UNUSED;
	  grCarInfo[car->index].skidmarks->strips[i].vtx[k]=new ssgVertexArray(MAXPOINT_BY_STRIP+1);
	  grCarInfo[car->index].skidmarks->strips[i].vta[k]=new ssgVtxTableShadow(GL_TRIANGLE_STRIP,
									       grCarInfo[car->index].skidmarks->strips[i].vtx[k]
									       ,shd_nrm, NULL, shd_clr);
	  grCarInfo[car->index].skidmarks->strips[i].vta[k]->setCullFace(0);
	  grCarInfo[car->index].skidmarks->strips[i].vta[k]->setState(skidState);
	  grCarInfo[car->index].skidmarks->strips[i].timeStrip=0;
	  TheScene->addKid(grCarInfo[car->index].skidmarks->strips[i].vta[k]);
	}
      /** no skid is in used */
      grCarInfo[car->index].skidmarks->strips[i].running_skid=0;
      /** the next skid to used is the first one */
      grCarInfo[car->index].skidmarks->strips[i].next_skid=0;
      /** there was no skid for this wheel during the next shot */
      grCarInfo[car->index].skidmarks->strips[i].last_state_of_skid=0;
    }
}

/** update if necessary the skidmarks for a car */
void grUpdateSkidmarks(tCarElt *car)
{
  int i=0;
  /* ssgVtxTable	*tmp;*/
  sgVec3	vtx;
  sgVec3	*tvtx;
  ssgVertexArray * basevtx=NULL;
  double t;

  t=GfTimeClock();

  for (i=0; i<4; i++)
    {
      /*if (i!=0 && i!=2)
	continue;*/
      if (t-grCarInfo[car->index].skidmarks->strips[i].timeStrip<DELTATSTRIP)
	continue;

      if ((car->_speed_x * car->_speed_x + car->_speed_y * car->_speed_y) > 10.0)
	if (car->_skid[i]>0.0)
	  {

	    basevtx=new ssgVertexArray(4*2+1);
	    
	    vtx[0]=car->priv->wheel[i].relPos.x-car->_tireHeight(i);
	    vtx[1]=car->priv->wheel[i].relPos.y-car->_tireWidth(i) / 2.0;
	    vtx[2]=car->priv->wheel[i].relPos.z-car->_wheelRadius(i)*1.1 ;
	    basevtx->add(vtx);
	    vtx[0]=car->priv->wheel[i].relPos.x-car->_tireHeight(i);
	    vtx[1]=car->priv->wheel[i].relPos.y+car->_tireWidth(i) / 2.0;
	    vtx[2]=car->priv->wheel[i].relPos.z-car->_wheelRadius(i)*1.1 ;
	    basevtx->add(vtx);
	    grCarInfo[car->index].skidmarks->base=new ssgVtxTable(GL_TRIANGLE_STRIP, basevtx, NULL, NULL, NULL);
	    grCarInfo[car->index].skidmarks->base->transform(grCarInfo[car->index].carPos);
	    grCarInfo[car->index].skidmarks->base->getVertexList((void**)&tvtx);
	    /** this is the begining of a skid or the continue 
		of the last one */
	    if (grCarInfo[car->index].skidmarks->strips[i].last_state_of_skid==0)
	      {
		
		/* begin case */
		grCarInfo[car->index].skidmarks->strips[i].last_state_of_skid=1;
		/* start a new one */
		grCarInfo[car->index].skidmarks->strips[i].running_skid=grCarInfo[car->index].skidmarks->strips[i].next_skid;
		if (grCarInfo[car->index].skidmarks->strips[i].state[grCarInfo[car->index].skidmarks->strips[i].running_skid]!=SKID_UNUSED)
		  {
		    grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].running_skid]->removeAll();
		    //printf("clearing [%d] %d\n",i,grCarInfo[car->index].skidmarks->strips[i].running_skid);
		  }

		grCarInfo[car->index].skidmarks->strips[i].state[grCarInfo[car->index].skidmarks->strips[i].running_skid]=SKID_BEGIN;
		grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(tvtx[0]);
		grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(tvtx[1]);
		//printf("begin [%d] skid %d x=%.2f y=%.2f \n",i,grCarInfo[car->index].skidmarks->strips[i].running_skid,tvtx[0][0],tvtx[0][1]);
		grCarInfo[car->index].skidmarks->strips[i].vta[grCarInfo[car->index].skidmarks->strips[i].running_skid]->recalcBSphere();
		grCarInfo[car->index].skidmarks->strips[i].size[grCarInfo[car->index].skidmarks->strips[i].running_skid]=2;
	      }
	    else
	      {
		/* continue case */
		grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(tvtx[0]);
		grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].running_skid]->add(tvtx[1]);
		//printf("continue [%d] x=%.2f y=%.2f \n",i,tvtx[0][0],tvtx[0][1]);
		grCarInfo[car->index].skidmarks->strips[i].size[grCarInfo[car->index].skidmarks->strips[i].running_skid]+=2;
		if ( grCarInfo[car->index].skidmarks->strips[i].state[grCarInfo[car->index].skidmarks->strips[i].running_skid]==SKID_BEGIN)
		  {
		    grCarInfo[car->index].skidmarks->strips[i].state[grCarInfo[car->index].skidmarks->strips[i].running_skid]=SKID_RUNNING;
		    /*TheScene->addKid(grCarInfo[car->index].skidmarks->strips[i].vta[grCarInfo[car->index].skidmarks->strips[i].running_skid]);*/
		  }
		grCarInfo[car->index].skidmarks->strips[i].vta[grCarInfo[car->index].skidmarks->strips[i].running_skid]->recalcBSphere();
	      }
	    basevtx->removeAll();
	    delete grCarInfo[car->index].skidmarks->base;

	  }
	else
	  {
	    /** this is the end of a skid or there is nothing to do */
	    if (grCarInfo[car->index].skidmarks->strips[i].last_state_of_skid!=0)
	      {
		/* end the running skid */
		grCarInfo[car->index].skidmarks->strips[i].state[grCarInfo[car->index].skidmarks->strips[i].running_skid]=SKID_STOPPED;
		grCarInfo[car->index].skidmarks->strips[i].vta[grCarInfo[car->index].skidmarks->strips[i].running_skid]->recalcBSphere();
		grCarInfo[car->index].skidmarks->strips[i].last_state_of_skid=0;
		//printf("end skid [%d] %d\n",i,grCarInfo[car->index].skidmarks->strips[i].running_skid);

		grCarInfo[car->index].skidmarks->strips[i].next_skid+=1;
		if (grCarInfo[car->index].skidmarks->strips[i].next_skid>=MAXSTRIP_BYWHEEL)
		  {
		    grCarInfo[car->index].skidmarks->strips[i].next_skid=0;
		    /* reset the next skid vertexArray*/
		    grCarInfo[car->index].skidmarks->strips[i].vtx[grCarInfo[car->index].skidmarks->strips[i].next_skid]->removeAll();
		    //printf("remove all in skid [%d] %d\n",i,grCarInfo[car->index].skidmarks->strips[i].next_skid);
		    /*TheScene->removeKid(grCarInfo[car->index].skidmarks->strips[i].vta[grCarInfo[car->index].skidmarks->strips[i].next_skid]);*/
		  
		  }
	      }
	    else
	      {

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

  for (z=0; z<grNbCars; z++)
    {
      free(grCarInfo[z].skidmarks);
      grCarInfo[z].skidmarks=NULL;
      for (i=0; i<4; i++)
	{
	  for (k=0; k<MAXSTRIP_BYWHEEL; k++)
	    {
	      if (grCarInfo[z].skidmarks->strips[i].state[k]!=SKID_UNUSED)
		{
		    TheScene->removeKid(grCarInfo[z].skidmarks->strips[i].vta[k]);
		}
	    }
	}
    }
}


void grDrawSkidmarks (tCarElt *car)
{
  /* nothing to do */
  
  
}
