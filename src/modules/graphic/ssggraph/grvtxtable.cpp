/***************************************************************************

    file                 : grvtxtable.cpp
    created              : Fri Mar 22 23:16:44 CET 2002
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

#include <plib/ssg.h>
#include "grvtxtable.h"
#include "grmain.h"
#include "grcam.h"
#include "grshadow.h"
#include "grskidmarks.h"
#ifdef DMALLOC
#include "dmalloc.h"
#endif
#ifdef WIN32
#include "win32_glext.h"
#endif
#include "grscene.h"
#include "grcar.h"
#include "grutil.h"

void grVtxTable::copy_from ( grVtxTable *src, int clone_flags )
{
  ssgVtxTable::copy_from ( src, clone_flags ) ;
  if ( src->texcoords1 != NULL && ( clone_flags & SSG_CLONE_GEOMETRY ) )
    texcoords1 = (ssgTexCoordArray *)( src -> texcoords1 -> clone ( clone_flags )) ;
  else
    texcoords1 = src -> texcoords1 ;

  if ( src->texcoords2 != NULL && ( clone_flags & SSG_CLONE_GEOMETRY ) )
    texcoords2 = (ssgTexCoordArray *)( src -> texcoords2 -> clone ( clone_flags )) ;
  else
    texcoords2 = src -> texcoords2 ;

  if ( src->texcoords3 != NULL && ( clone_flags & SSG_CLONE_GEOMETRY ) )
    texcoords3 = (ssgTexCoordArray *)( src -> texcoords3 -> clone ( clone_flags )) ;
  else
    texcoords3 = src -> texcoords3 ;
  numMapLevel=src->numMapLevel;
  mapLevelBitmap=src->mapLevelBitmap;
  internalType=src->mapLevelBitmap;

  if (src->internalType==ARRAY)
    {
      numStripes=src->numStripes;
      ssgDeRefDelete ( indices ) ;
      if ( src->indices != NULL && ( clone_flags & SSG_CLONE_GEOMETRY ) )
	indices = (ssgIndexArray *)( src -> indices -> clone ( clone_flags )) ;
      else
	indices = src -> indices ;
      if ( indices != NULL )
	indices -> ref () ;
      
      ssgDeRefDelete ( stripes ) ;
      if ( src->stripes != NULL && ( clone_flags & SSG_CLONE_GEOMETRY ) )
	stripes = (ssgIndexArray *)( src -> stripes -> clone ( clone_flags )) ;
      else
	stripes = src -> stripes ;
      if ( stripes != NULL )
	stripes -> ref () ;
    }
}

ssgBase *grVtxTable::clone ( int clone_flags )
{
  grVtxTable *b = new grVtxTable(1,LEVEL0);
  b -> copy_from ( this, clone_flags ) ;
  return b ;
}

/*grVtxTable::grVtxTable ()
{
  grVtxTable(1,LEVEL0);
}
*/

grVtxTable::grVtxTable (int _numMapLevel,int _mapLevel ) 
{
  numMapLevel=_numMapLevel;
  mapLevelBitmap=_mapLevel;
  indexCar= -1;
  texcoords1 =NULL ;
  texcoords2 =NULL ;
  texcoords3 =NULL ;
  state1=state2=state3=NULL;
  internalType=TABLE;
  numStripes=0;
  ssgVtxTable();
}

grVtxTable::grVtxTable ( GLenum ty, ssgVertexArray   *vl,
			 ssgIndexArray    * stripeIndex,
			 int _numstripes,
			 ssgIndexArray    *il,
			 ssgNormalArray   *nl,
			 ssgTexCoordArray *tl,
			 ssgTexCoordArray *tl1,
			 ssgTexCoordArray *tl2,
			 ssgTexCoordArray *tl3,
			 int _numMapLevel,
			 int _mapLevel,
			 ssgColourArray   *cl, 
			 int _indexCar ) : ssgVtxTable( ty, vl, nl, tl, cl )
{
  type = ssgTypeVtxTable () ;
  numMapLevel=_numMapLevel;
  mapLevelBitmap=_mapLevel;
  indexCar= _indexCar;
  texcoords1 = (tl1!=NULL) ? tl1 : new ssgTexCoordArray () ;
  texcoords2 = (tl2!=NULL) ? tl2 : new ssgTexCoordArray () ;
  texcoords3 = (tl3!=NULL) ? tl3 : new ssgTexCoordArray () ;
  texcoords1 -> ref () ;
  texcoords2 -> ref () ;
  texcoords3 -> ref () ;
  state1=state2=state3=NULL;
  internalType=ARRAY;
  /*internalType=TABLE;*/
  indices = (il!=NULL) ? il : new ssgIndexArray () ;
  indices -> ref () ;
  stripes = (stripeIndex!=NULL) ? stripeIndex : new ssgIndexArray () ;
  stripes -> ref () ;
  numStripes=_numstripes;


}

grVtxTable::grVtxTable ( GLenum ty, ssgVertexArray   *vl,
			 ssgNormalArray   *nl,
			 ssgTexCoordArray *tl,
			 ssgTexCoordArray *tl1,
			 ssgTexCoordArray *tl2,
			 ssgTexCoordArray *tl3,
			 int _numMapLevel,
			 int _mapLevel,
			 ssgColourArray   *cl,
			 int _indexCar) : ssgVtxTable( ty, vl, nl, tl, cl )
{
  type = ssgTypeVtxTable () ;
  numMapLevel=_numMapLevel;
  mapLevelBitmap=_mapLevel;
  indexCar= _indexCar;
  texcoords1 = (tl1!=NULL) ? tl1 : new ssgTexCoordArray () ;
  texcoords2 = (tl2!=NULL) ? tl2 : new ssgTexCoordArray () ;
  texcoords3 = (tl3!=NULL) ? tl3 : new ssgTexCoordArray () ;
  texcoords1 -> ref () ;
  texcoords2 -> ref () ;
  texcoords3 -> ref () ;
  /*printf(" numMapLevel =%d , mapLevel=%d \n",numMapLevel,mapLevelBitmap);	*/
  state1=state2=state3=NULL;
  internalType=TABLE;
  numStripes=0;
}

grVtxTable::~grVtxTable ()
{
  /*  ssgDeRefDelete ( vertices  ) ;
      ssgDeRefDelete ( normals   ) ;
      ssgDeRefDelete ( colours   ) ; */
      ssgDeRefDelete ( texcoords1 ) ;
      ssgDeRefDelete ( texcoords2 ) ;
      ssgDeRefDelete ( texcoords3 ) ;
      if(internalType==ARRAY)
	{
	  ssgDeRefDelete ( indices      ) ;
	  ssgDeRefDelete ( stripes      ) ;
	}

} 

void grVtxTable::setState1 ( ssgState *st )
{
    ssgDeRefDelete ( state1 ) ;

    state1 = (grMultiTexState *)st ;

    if ( state1 != NULL )
      state1->ref() ;
}

void grVtxTable::setState2 ( ssgState *st )
{
    ssgDeRefDelete ( state2 ) ;

    state2 = (grMultiTexState *)st ;

    if ( state2 != NULL )
      state2->ref() ;
}

void grVtxTable::setState3 ( ssgState *st )
{
    ssgDeRefDelete ( state3 ) ;

    state3 = (grMultiTexState *)st ;

    if ( state3 != NULL )
      state3->ref() ;
}
void grVtxTable::draw ()
{
  if ( ! preDraw () )
    return ;

  if ( hasState () ) getState () -> apply () ;

  /*stats_num_leaves++ ;
    stats_num_vertices += getNumVertices() ;*/

#ifdef _SSG_USE_DLIST
  if ( dlist )
    glCallList ( dlist ) ;
  else
#endif
    
    /*printf("draw_geo numMapLevel =%d , mapLevel=%d \n",numMapLevel,mapLevelBitmap);	*/
    if(internalType==TABLE)
      {
	if (mapLevelBitmap==LEVEL0 || maxTextureUnits==1)
	  ssgVtxTable::draw_geometry () ;
	else if (mapLevelBitmap<0)
	  draw_geometry_for_a_car () ;
	else 
	  draw_geometry_multi () ;
      }
    else
      {
      	if (mapLevelBitmap==LEVEL0 || maxTextureUnits==1)
	  draw_geometry_array () ;
	else if (mapLevelBitmap<0)
	  /*draw_geometry_for_a_car_array () ;*/
	  draw_geometry_array ();
	else 
	  /*draw_geometry_multi_array () ;*/
	  draw_geometry_array ();
      }
  if ( postDrawCB != NULL )
    (*postDrawCB)(this) ;
}

void grVtxTable::draw_geometry_multi () 
{

  /*GUIONS */
  /*printf("draw_geo_multy numMapLevel =%d , mapLevel=%d \n",numMapLevel,mapLevelBitmap);	*/
  if (numMapLevel>1)state1->apply(1);
  if (numMapLevel>2)state2->apply(2);

  int num_colours   = getNumColours   () ;
  int num_normals   = getNumNormals   () ;
  int num_vertices  = getNumVertices  () ;
  int num_texcoords = getNumTexCoords () ;

  sgVec3 *vx = (sgVec3 *) vertices  -> get(0) ;
  sgVec3 *nm = (sgVec3 *) normals   -> get(0) ;
  sgVec2 *tx = (sgVec2 *) texcoords -> get(0) ;
  sgVec2 *tx1 = NULL;
  sgVec2 *tx2 = NULL;
  if (numMapLevel>1) 
    tx1=(sgVec2 *) texcoords1 -> get(0) ;
  if (numMapLevel>2) 
    tx2=(sgVec2 *) texcoords2 -> get(0) ;

  sgVec4 *cl = (sgVec4 *) colours   -> get(0) ;

  TRACE_GL("draw_geometry_multi: start");
  glBegin ( gltype ) ;
  TRACE_GL("draw_geometry_multi: 1");

  if ( num_colours == 0 ) glColor4f   ( 1.0f, 1.0f, 1.0f, 1.0f ) ;
  if ( num_colours == 1 ){
    glColor4fv  ( cl [ 0 ] ) ;
    /*printf("setup color\n");
      glColor4f ( cl [ 0 ][0]*numMapLevel,cl [ 0 ][1]*numMapLevel,
      cl [ 0 ][2]*numMapLevel,cl [ 0 ][3]);*/
  }
  TRACE_GL("draw_geometry_multi: 2");
  if ( num_normals == 1 ) glNormal3fv ( nm [ 0 ] ) ;
  for ( int i = 0 ; i < num_vertices ; i++ )
  {
    /*if ( num_colours   > 1 ) glColor4fv    ( cl [ i ] ) ;*/
    if ( num_normals   > 1 ) glNormal3fv   ( nm [ i ] ) ;
    if ( num_texcoords > 1 ){ /*glTexCoord2fv ( tx [ i ] ) ;*/
      glMultiTexCoord2fvARB(GL_TEXTURE0_ARB,tx [ i ] );
      TRACE_GL("draw_geometry_multi: 3");
      if (numMapLevel>1) glMultiTexCoord2fvARB(GL_TEXTURE1_ARB,tx1 [ i ] );
      TRACE_GL("draw_geometry_multi: 4");
      if (numMapLevel>2) glMultiTexCoord2fvARB(GL_TEXTURE2_ARB,tx2 [ i ] );
      TRACE_GL("draw_geometry_multi: 5");
    }
    glVertex3fv ( vx [ i ] ) ;
    TRACE_GL("draw_geometry_multi: 6");
  }
  TRACE_GL("draw_geometry_multi: 15");
  glEnd () ;
/*   { GLenum rc; if ((rc = glGetError()) != GL_NO_ERROR) printf("vert=%d norm=%d lev=%d tex=%d\n", num_vertices, num_normals, numMapLevel, num_texcoords); */
/*   } */
  
 
  TRACE_GL("draw_geometry_multi: 7");
  if (numMapLevel>1) {
      glActiveTextureARB ( GL_TEXTURE1_ARB ) ;
      TRACE_GL("draw_geometry_multi: 8");
      glDisable ( GL_TEXTURE_2D ) ; 
      TRACE_GL("draw_geometry_multi: 9");
  }
  if (numMapLevel>2) {
      glActiveTextureARB ( GL_TEXTURE2_ARB ) ;
      TRACE_GL("draw_geometry_multi: 10");
      glDisable ( GL_TEXTURE_2D ) ; 
      TRACE_GL("draw_geometry_multi: 11");
  }
  if (numMapLevel>3) {
      glActiveTextureARB ( GL_TEXTURE3_ARB ) ;
      TRACE_GL("draw_geometry_multi: 12");
      glDisable ( GL_TEXTURE_2D ) ; 
      TRACE_GL("draw_geometry_multi: 13");
  }
  glActiveTextureARB ( GL_TEXTURE0_ARB ) ;
  TRACE_GL("draw_geometry_multi: 14");

}


/* static tdble rrz=0; */

void grVtxTable::draw_geometry_for_a_car ()
{
  tdble ttx=0;
  tdble tty=0;
  tdble ttz=0;
  sgMat4 mat ;
  /*sgMat4 mat1 ;*/

  /* GUIONS : first apply the env state */
  /*if (state1)
    state1->apply(1);*/
  if (mapLevelBitmap<=LEVELC2 )
    {
      ttx=grCarInfo[indexCar].distFromStart/40;
      sgMakeTransMat4 ( mat, ttx, tty, ttz ) ;
      grEnvState->apply(2);
      glMatrixMode(GL_TEXTURE);
      glLoadIdentity () ;
      glMultMatrixf ( (float *)mat ) ;
      glMatrixMode(GL_MODELVIEW);

    }


  if (mapLevelBitmap==LEVELC3)
    {
      sgVec3 axis;
      axis[0]=0;
      axis[1]=0;
      axis[2]=1;
      grEnvShadowState->apply(1);
      glMatrixMode(GL_TEXTURE);
      /*sgMakeTransMat4 ( mat, ttx, tty, ttz ) ;*/
      glLoadIdentity () ;
      /*ttx=grCarInfo[indexCar].distFromStart/200;
	if (grCarInfo[indexCar].envAngle>180.0)
	ttx=-ttx;
	sgMakeTransMat4 ( mat, ttx, tty, ttz ) ;
	glMultMatrixf ( (float *)mat ) ;*/
      sgMakeRotMat4 ( mat,grCarInfo[indexCar].envAngle, axis) ;
      glMultMatrixf ( (float *)mat ) ;
      /*glMultMatrixf ( (float *)grCarInfo[indexCar].carPos ) ;
	rrz+=0.001;*/
      /*glMultMatrixf ( (float *) grCarInfo[indexCar].carPos ) ;*/
      /*glMultMatrixf ( (float *) mat ) ; */
      glMatrixMode(GL_MODELVIEW);
      
      
    }
  else
    {
      /*grEnvState->apply(1);*/
      grEnvShadowState->apply(1);

      glActiveTextureARB ( GL_TEXTURE1_ARB ) ;
      glEnable ( GL_TEXTURE_2D ) ; 
      glEnable(GL_TEXTURE_GEN_S);
      glEnable(GL_TEXTURE_GEN_T);
    }


  int num_colours   = getNumColours   () ;
  int num_normals   = getNumNormals   () ;
  int num_vertices  = getNumVertices  () ;
  int num_texcoords = getNumTexCoords () ;

  sgVec3 *vx = (sgVec3 *) vertices  -> get(0) ;
  sgVec3 *nm = (sgVec3 *) normals   -> get(0) ;
  sgVec2 *tx = (sgVec2 *) texcoords -> get(0) ;
  sgVec2 *tx1 = (sgVec2 *) texcoords1 -> get(0) ;
  sgVec2 *tx2 = (sgVec2 *) texcoords2 -> get(0) ;
  sgVec4 *cl = (sgVec4 *) colours   -> get(0) ;


  glBegin ( gltype ) ;

  if ( num_colours == 0 ) glColor4f   ( 1.0f, 1.0f, 1.0f, 1.0f ) ;
  if ( num_colours == 1 ) glColor4fv  ( cl [ 0 ] ) ;
  if ( num_normals == 1 ) glNormal3fv ( nm [ 0 ] ) ;

  for ( int i = 0 ; i < num_vertices ; i++ )
  {
    /*if ( num_colours   > 1 ) glColor4fv    ( cl [ i ] ) ;*/
    if ( num_normals   > 1 ) glNormal3fv   ( nm [ i ] ) ;
    if ( num_texcoords > 1 ) { 
      /*glTexCoord2fv ( tx [ i ] ) ;*/
      glMultiTexCoord2fvARB(GL_TEXTURE0_ARB,tx [ i ] );
      glMultiTexCoord2fvARB(GL_TEXTURE2_ARB,tx1 [ i ] );
      if (mapLevelBitmap==LEVELC3)
	glMultiTexCoord2fvARB(GL_TEXTURE1_ARB,tx2 [ i ] );

    }
    
    glVertex3fv ( vx [ i ] ) ;
  }
 
  glEnd () ;
  TRACE_GL("draw_geometry_for_a_car: 15");

  glActiveTextureARB ( GL_TEXTURE1_ARB ) ;
  glDisable ( GL_TEXTURE_2D ) ; 
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glMatrixMode(GL_TEXTURE);
  glLoadIdentity () ;
  glMatrixMode(GL_MODELVIEW);
  glActiveTextureARB ( GL_TEXTURE2_ARB ) ;
  glDisable ( GL_TEXTURE_2D ) ; 
  glActiveTextureARB ( GL_TEXTURE0_ARB ) ;
}


void grVtxTable::draw_geometry_array ()
{
  int num_colours   = getNumColours   () ;
  int num_normals   = getNumNormals   () ;
  int num_texcoords = getNumTexCoords () ;

  sgVec3 *nm = (sgVec3 *) normals   -> get(0) ;
  sgVec4 *cl = (sgVec4 *) colours   -> get(0) ;

  if ( num_colours == 0 ) glColor4f   ( 1.0f, 1.0f, 1.0f, 1.0f ) ;
  if ( num_colours == 1 ) glColor4fv  ( cl [ 0 ] ) ;
  if ( num_normals == 1 ) glNormal3fv ( nm [ 0 ] ) ;
  
  glPushClientAttrib ( GL_CLIENT_VERTEX_ARRAY_BIT ) ;

  /*  if ( num_colours > 1 )
  {
    glEnableClientState ( GL_COLOR_ARRAY ) ;
    glColorPointer ( 4, GL_FLOAT, 0, colours->get(0) ) ;
    }*/
  if ( num_normals > 1 )
  {
    glEnableClientState ( GL_NORMAL_ARRAY ) ;
    glNormalPointer ( GL_FLOAT, 0, normals->get(0) ) ;
  }
  if ( num_texcoords > 1 )
  {
    glEnableClientState ( GL_TEXTURE_COORD_ARRAY ) ;
    glTexCoordPointer ( 2, GL_FLOAT, 0, texcoords->get(0) ) ;
  }
  glEnableClientState ( GL_VERTEX_ARRAY ) ;
  glVertexPointer ( 3, GL_FLOAT, 0, vertices->get(0) ) ;

  glClientActiveTextureARB(GL_TEXTURE0_ARB);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  /*
  glClientActiveTextureARB(GL_TEXTURE1_ARB);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  */

  int i=0 ; 
  short *ii = NULL;
  /*short *ii = indices->get(0);*/
  int j=0;
  int p=0;
  /*int i = getNumIndices ();*/

  for (j=0; j<numStripes; j++)
    {
      i=(short)*(stripes->get(j));
      ii=indices->get(p);
      glDrawElements ( gltype, i, GL_UNSIGNED_SHORT, ii ) ;
      p+=i;
    }
  glPopClientAttrib ( ) ;
}
