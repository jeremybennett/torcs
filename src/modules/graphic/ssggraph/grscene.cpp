/***************************************************************************

    file                 : grscene.cpp
    created              : Mon Aug 21 20:13:56 CEST 2000
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
#include "grutil.h"
#include "grssgext.h"
#include "win32_glext.h"
#ifdef DMALLOC
#include "dmalloc.h"
#endif

int grWrldX;
int grWrldY;
int grWrldZ;
int grWrldMaxSize;
tTrack 	 *grTrack;

int    BackgroundType;
GLuint BackgroundList;
GLuint BackgroundTex;
GLuint BackgroundList2;
GLuint BackgroundTex2;

ssgStateSelector	*grEnvSelector;
grMultiTexState	*grEnvState=NULL;
grMultiTexState	*grEnvShadowState=NULL;
#define NB_BG_FACES	20
#define BG_DIST		1.0

ssgRoot *TheScene;

static void initBackground(void);

static void customizePits(void);

static ssgLoaderOptionsEx	grloaderOptions;
extern ssgEntity *grssgLoadAC3D ( const char *fname, const ssgLoaderOptions* options );

#define DISTG 80



#ifdef GUIONS
DoV_t  PlayableDistanceOfView;
DoV_t  UnPlayableDistanceOfView;
DoV_t * currentDistanceOfView=&PlayableDistanceOfView;
DistanceOfViewHashing_t * SceneHashing=NULL;


int computeSceneHashing(tTrack *track)
{
  tTrackSeg *seg1=track->seg;
  tTrackSeg *seg=NULL;
  tTrackSeg *seg2=NULL;
  int i=0;
  int j=0;
  int dist=0;
  int lmap=0;
  tdble length=0;
  tdble rearlength=0;
  /* allocate enough space for the hash */
  printf("computescenehashing 0\n");
  if(SceneHashing!=NULL)
    free(SceneHashing);

  SceneHashing=(DistanceOfViewHashing_t *)(malloc(sizeof(DistanceOfViewHashing_t)*track->nseg));
  printf("computescenehashing %d\n",track->nseg);
  printf("front global= %f\n",PlayableDistanceOfView.FrontLevelGroupGlobal);
  printf("front level1= %f\n",PlayableDistanceOfView.FrontLevelGroup1);
  printf("front level2= %f\n",PlayableDistanceOfView.FrontLevelGroup2);
  printf("front level3= %f\n",PlayableDistanceOfView.FrontLevelGroup3);
  printf("rear global= %f\n",PlayableDistanceOfView.RearLevelGroupGlobal);
  printf("rear level1= %f\n",PlayableDistanceOfView.RearLevelGroup1);
  printf("rear level2= %f\n",PlayableDistanceOfView.RearLevelGroup2);
  printf("rear level3= %f\n",PlayableDistanceOfView.RearLevelGroup3);
  for (i = 0, seg = track->seg; i < track->nseg; i++, seg = seg->next)
    {
      /*if (i==0)printf("%d,",seg->id);*/
      SceneHashing[i].name=seg->name;
      SceneHashing[i].ViewGroup=g_hash_table_new (g_str_hash, g_str_equal);
      SceneHashing[i].ViewGroup_num=0;
      SceneHashing[i].ViewGroupMap1_num=0;
      SceneHashing[i].ViewGroupMap2_num=0;
      SceneHashing[i].ViewGroupMap3_num=0;
      /* now setup the hash for each entry */
      /*printf("dealing with TKMN%d factor=%f\n",seg->id,seg->DoVfactor);*/
      dist=0;
      length=0;
      for (j=0, seg2=seg; j<track->nseg; j++, seg2=seg2->next)
	{
	  hashMapElement * helt;
	  char  buf[256];
	  length+=seg2->length;
	  if (length>PlayableDistanceOfView.FrontLevelGroupGlobal*seg->DoVfactor)
	    break;
	  helt=(hashMapElement *)malloc(sizeof(hashMapElement ));
	  if (length<PlayableDistanceOfView.FrontLevelGroup1*seg->DoVfactor)
	    {
	      sprintf(buf,"___TKMN%d_gl1",seg2->id);
	      /*printf("inserting ___TKMN%d_gl1 %f\n",seg2->id,length);*/
	      helt->name=strdup(buf);
	      helt->numberOfMapToApply=0;
	      g_hash_table_insert(SceneHashing[i].ViewGroup,
                                             helt->name,
				  helt);
	      SceneHashing[i].ViewGroup_num++;
	    }
	  if (length<PlayableDistanceOfView.FrontLevelGroup2*seg->DoVfactor)
	    {
	      sprintf(buf,"___TKMN%d_gl2",seg2->id);
	      /*printf("inserting ___TKMN%d_gl2 %f\n",seg2->id,length);*/
	      helt->name=strdup(buf);
	      helt->numberOfMapToApply=0;
	      g_hash_table_insert(SceneHashing[i].ViewGroup,
                                             helt->name,
				  helt);
	      SceneHashing[i].ViewGroup_num++;
	    }
	  if (length<PlayableDistanceOfView.FrontLevelGroup3*seg->DoVfactor)
	    {
	      sprintf(buf,"___TKMN%d_gl3",seg2->id);
	      /*printf("inserting ___TKMN%d_gl3 %f\n",seg2->id,length);*/
	      helt->name=strdup(buf);
	      helt->numberOfMapToApply=0;
	      g_hash_table_insert(SceneHashing[i].ViewGroup,
                                             helt->name,
				  helt);
	      SceneHashing[i].ViewGroup_num++;
	    }
	  sprintf(buf,"___TKMN%d_gl0",seg2->id);
	  /*printf("inserting ___TKMN%d_gl0 %f\n",seg2->id,length);*/
	  helt->name=strdup(buf);
	  helt->numberOfMapToApply=0;
	  g_hash_table_insert(SceneHashing[i].ViewGroup,
			      helt->name,
			      helt);
	  SceneHashing[i].ViewGroup_num++;

	  sprintf(buf,"TKMN%d",seg2->id);
	  /*printf("inserting TKMN%d %f\n",seg2->id,length);*/
	  helt->name=strdup(buf);
	  helt->numberOfMapToApply=0;
	  g_hash_table_insert(SceneHashing[i].ViewGroup,
			      helt->name,
			      helt);
	  SceneHashing[i].ViewGroup_num++;
	}

      dist=0;
      /*printf("dealing with TKMN%d in rear side\n",seg->id);*/
      rearlength=0;
      for (j=0, seg2=seg; j<track->nseg; j++, seg2=seg2->prev)
	{
	  hashMapElement * helt;
	  char  buf[256];
	  rearlength+=seg2->length;
	  if (rearlength>PlayableDistanceOfView.RearLevelGroupGlobal*seg->DoVfactor)
	    break;
	  helt=(hashMapElement *)malloc(sizeof(hashMapElement ));
	  if (rearlength<PlayableDistanceOfView.RearLevelGroup1*seg->DoVfactor)
	    {
	      sprintf(buf,"___TKMN%d_gl1",seg2->id);
	      /*printf("inserting ___TKMN%d_gl1 %f\n",seg2->id,rearlength);*/
	      helt->name=strdup(buf);
	      helt->numberOfMapToApply=0;
	      g_hash_table_insert(SceneHashing[i].ViewGroup,
                                             helt->name,
				  helt);
	      SceneHashing[i].ViewGroup_num++;
	    }
	  if (rearlength<PlayableDistanceOfView.RearLevelGroup2*seg->DoVfactor)
	    {
	      sprintf(buf,"___TKMN%d_gl2",seg2->id);
	      /*printf("inserting ___TKMN%d_gl2 %f\n",seg2->id,rearlength);*/
	      helt->name=strdup(buf);
	      helt->numberOfMapToApply=0;
	      g_hash_table_insert(SceneHashing[i].ViewGroup,
                                             helt->name,
				  helt);
	      SceneHashing[i].ViewGroup_num++;
	    }
	  if (rearlength<PlayableDistanceOfView.RearLevelGroup3*seg->DoVfactor)
	    {
	      sprintf(buf,"___TKMN%d_gl3",seg2->id);
	      /*printf("inserting ___TKMN%d_gl3 %f\n",seg2->id,rearlength);*/
	      helt->name=strdup(buf);
	      helt->numberOfMapToApply=0;
	      g_hash_table_insert(SceneHashing[i].ViewGroup,
                                             helt->name,
				  helt);
	      SceneHashing[i].ViewGroup_num++;
	    }
	  sprintf(buf,"___TKMN%d_gl0",seg2->id);
	  /*printf("inserting ___TKMN%d_gl0 %f\n",seg2->id,rearlength);*/
	  helt->name=strdup(buf);
	  helt->numberOfMapToApply=0;
	  g_hash_table_insert(SceneHashing[i].ViewGroup,
			      helt->name,
			      helt);
	  SceneHashing[i].ViewGroup_num++;

	  sprintf(buf,"TKMN%d",seg2->id);
	  /*printf("inserting TKMN%d %f\n",seg2->id,rearlength);*/
	  helt->name=strdup(buf);
	  helt->numberOfMapToApply=0;
	  g_hash_table_insert(SceneHashing[i].ViewGroup,
			      helt->name,
			      helt);
	  SceneHashing[i].ViewGroup_num++;
	}




      /*printf("TKMN%d %d\n",seg->id,SceneHashing[i].ViewGroup_num);*/

    }
  
  /*printf("\n");*/
  return 0;
}
#endif /* GUIONS */


int preScene(ssgEntity *e)
{
#ifdef GUIONS
  char *p=NULL ;
  int id=0;
  char *q=NULL;
  int max=0;

  p=(((ssgBranchCb*)e)->getKid(0))->getName();
  if (p==NULL)
    return TRUE;
  q=strstr(p,"TKMN");
  id=segIndice;
  if (q)
    {
      if (g_hash_table_lookup(SceneHashing[segIndice].ViewGroup,p)!=NULL)
	{
	  /*printf("%d accepting %s\n",segIndice,p);*/
	  return TRUE;
	}
      else
	{
	  /*printf("rejecting %s\n",p);*/
	  return FALSE;
	}
      /*q=q+strlen("TKMN");
	id=atoi(q);
	max=grTrack->seg->prev->id;
	if (max-segIndice<DISTG)
	{
	if (id>segIndice)
	{
	return TRUE;
	}
	if (id< (DISTG-(max-segIndice)))
	{
	return TRUE;
	}
	if (id>(segIndice-DISTG))
	{
	return TRUE;
	}
	return FALSE;
	}
	if (segIndice<DISTG)
	{
	if (id<segIndice)
	{
	return TRUE;
	}
	if (id>(max-(DISTG-segIndice)))
	{
	return TRUE;
	}
	if (id<segIndice+DISTG)
	{
	return TRUE;
	}
	return FALSE;
	}
	if (id<(segIndice+DISTG) && id>(segIndice-DISTG))
	{
	return TRUE;
	}
	return (FALSE);
      */
    }
  /* printf("%d accepting %s\n",segIndice,p);*/
#endif /* GUIONS */

  return TRUE;
}

int
grInitScene(void)
{
    void		*hndl = grTrackHandle;
    ssgLight *          light = ssgGetLight(0);

    GLfloat mat_specular[]={0.3,0.3,0.3,1.0};
    GLfloat mat_shininess[] ={50.0};
    GLfloat light_position[]={0,0,200,0.0};
    GLfloat lmodel_ambient[]={0.2,0.2,0.2,1.0};
    GLfloat lmodel_diffuse[]={0.8,0.8,0.8,1.0};

    if (grHandle==NULL)
      grHandle = GfParmReadFile(GR_PARAM_FILE, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
#ifdef GUIONS

    PlayableDistanceOfView.FrontLevelGroupGlobal=GfParmGetNum(grHandle, GR_SCT_PLAYABLE_DOV,
							      GR_ATT_FRONT_GLOBAL,
							      (char*)NULL, 600);
    PlayableDistanceOfView.FrontLevelGroup3=GfParmGetNum(grHandle, GR_SCT_PLAYABLE_DOV,
							      GR_ATT_FRONT_LEVEL3,
							      (char*)NULL, 150);
    PlayableDistanceOfView.FrontLevelGroup2=GfParmGetNum(grHandle, GR_SCT_PLAYABLE_DOV,
							      GR_ATT_FRONT_LEVEL2,
							      (char*)NULL, 300);
    PlayableDistanceOfView.FrontLevelGroup1=GfParmGetNum(grHandle, GR_SCT_PLAYABLE_DOV,
							      GR_ATT_FRONT_LEVEL1,
							      (char*)NULL, 500);

    PlayableDistanceOfView.RearLevelGroupGlobal=GfParmGetNum(grHandle, GR_SCT_PLAYABLE_DOV,
							      GR_ATT_REAR_GLOBAL,
							      (char*)NULL, 350);
    PlayableDistanceOfView.RearLevelGroup3=GfParmGetNum(grHandle, GR_SCT_PLAYABLE_DOV,
							      GR_ATT_REAR_LEVEL3,
							      (char*)NULL, 100);
    PlayableDistanceOfView.RearLevelGroup2=GfParmGetNum(grHandle, GR_SCT_PLAYABLE_DOV,
							      GR_ATT_REAR_LEVEL2,
							      (char*)NULL, 200);
    PlayableDistanceOfView.RearLevelGroup1=GfParmGetNum(grHandle, GR_SCT_PLAYABLE_DOV,
							      GR_ATT_REAR_LEVEL1,
							      (char*)NULL, 300);
#endif /* GUIONS */
    GfParmReleaseHandle(grHandle);
    mat_specular[0] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_SPEC_R, NULL, mat_specular[0]);
    mat_specular[1] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_SPEC_G, NULL, mat_specular[1]);
    mat_specular[2] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_SPEC_B, NULL, mat_specular[2]);
    lmodel_ambient[0] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_AMBIENT_R, NULL, lmodel_ambient[0]);
    lmodel_ambient[1] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_AMBIENT_G, NULL, lmodel_ambient[1]);
    lmodel_ambient[2] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_AMBIENT_B, NULL, lmodel_ambient[2]);
    lmodel_diffuse[0] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_DIFFUSE_R, NULL, lmodel_diffuse[0]);
    lmodel_diffuse[1] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_DIFFUSE_G, NULL, lmodel_diffuse[1]);
    lmodel_diffuse[2] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_DIFFUSE_B, NULL, lmodel_diffuse[2]);
    mat_shininess[0] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_SHIN, NULL, mat_shininess[0]);
    light_position[0] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_LIPOS_X, NULL, light_position[0]);
    light_position[1] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_LIPOS_Y, NULL, light_position[1]);
    light_position[2] = GfParmGetNum(hndl, TRK_SECT_GRAPH, TRK_ATT_LIPOS_Z, NULL, light_position[2]);

    glShadeModel(GL_SMOOTH);
    /*glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
      glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);
      glLightModelfv (GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
      glLightfv(GL_LIGHT0, GL_SPECULAR, light_position);
    */
    light->setPosition(light_position[0],light_position[1],light_position[2]);
    light->setColour(GL_AMBIENT,lmodel_ambient);
    light->setColour(GL_DIFFUSE,lmodel_diffuse);
    light->setColour(GL_SPECULAR,mat_specular);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    /* GUIONS GL_TRUE */
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);

#ifdef GL_SEPARATE_SPECULAR_COLOR 
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
#else
#ifdef GL_SEPARATE_SPECULAR_COLOR_EXT
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT,GL_SEPARATE_SPECULAR_COLOR_EXT);
#endif
#endif
    
    

    return 0;
}

static ssgLoaderOptionsEx	options;

int
grLoadScene(tTrack *track)
{
    void		*hndl = grTrackHandle;
    char		*acname;
    ssgEntity		*desc;
    char		buf[256];

    if (maxTextureUnits==0)
      {
	InitMultiTex();   
	if( maxTextureUnits>1)
	  {
	    glActiveTextureARB ( GL_TEXTURE1_ARB ) ;
	    glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	    glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	    glActiveTextureARB ( GL_TEXTURE0_ARB ) ;
	  }
      }

    glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    /*glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
      glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);*/

    ssgSetCurrentOptions(&options);
    ssgAddTextureFormat(".png", grLoadPngTexture);
    grTrack = track;
    TheScene = new ssgRoot;
    initBackground();
    
    grWrldX = (int)(track->max.x - track->min.x + 1);
    grWrldY = (int)(track->max.y - track->min.y + 1);
    grWrldZ = (int)(track->max.z - track->min.z + 1);
    grWrldMaxSize = (int)(MAX(MAX(grWrldX, grWrldY), grWrldZ));

    acname = GfParmGetStr(hndl, TRK_SECT_GRAPH, TRK_ATT_3DDESC, "track.ac");
    if (strlen(acname) == 0) {
	return -1;
    }

    sprintf(buf, "tracks/%s/%s;data/textures;data/img;.", grTrack->category, grTrack->internalname);
    ssgTexturePath(buf);
    sprintf(buf, "tracks/%s/%s", grTrack->category, grTrack->internalname);
    ssgModelPath(buf);
    /*desc = ssgLoad((const char *)acname*/ /* , (const ssgLoaderOptions *)&grloaderOptions *//* );*/
    desc = grssgLoadAC3D(acname, NULL);
    TheScene->addKid(desc);
    /* TheScene->setCallback(SSG_CALLBACK_PREDRAW, preScene); */
#ifdef GUIONS
    computeSceneHashing(track);
#endif /* GUIONS */
    customizePits();

    return 0;
}


void grDrawScene(void)
{
    TRACE_GL("refresh: ssgCullAndDraw start");
    /*glEnable(GL_DEPTH_TEST);*/
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    /*glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);*/
    
    ssgCullAndDraw(TheScene);

    TRACE_GL("refresh: ssgCullAndDraw");
}

void grShutdownScene(void)
{
    grShutdownSmoke ();
    delete TheScene;
    glDeleteTextures(1, &BackgroundTex);
    glDeleteLists(BackgroundList, 1);
    if (BackgroundType > 2) {
	glDeleteTextures(1, &BackgroundTex2);
	glDeleteLists(BackgroundList2, 1);
    }
}

static void
initBackground(void)
{
    int			i;
    float		x, y, z1, z2;
    float		alpha, texLen;
    tTrackGraphicInfo	*graphic;
    ssgSimpleState	*envst;
    char		buf[256];

    sprintf(buf, "tracks/%s/%s;data/img;data/textures;.", grTrack->category, grTrack->internalname);

    graphic = &grTrack->graphic;
    glClearColor(graphic->bgColor[0], graphic->bgColor[1], graphic->bgColor[2], 1.0);
    BackgroundTex = BackgroundTex2 = 0;

    z1 = -0.5;
    z2 = 0.8;
    BackgroundType = graphic->bgtype;
    switch (BackgroundType) {
    case 0:
	GfOut("Loading texture %s\n", graphic->background);
	BackgroundTex = grLoadTexture(graphic->background, buf, 1.8, 0);
	BackgroundList = glGenLists(1);
	glNewList(BackgroundList, GL_COMPILE);
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i < NB_BG_FACES + 1; i++) {
	    alpha = (float)i * 2 * PI / (float)NB_BG_FACES;
	    texLen = (float)i / (float)NB_BG_FACES;
	    
	    x = BG_DIST * cos(alpha);
	    y = BG_DIST * sin(alpha);
	    
	    glTexCoord2f(texLen*4.0, 0);   glVertex3f(x, y, z1);
	    glTexCoord2f(texLen*4.0, 1.0); glVertex3f(x, y, z2);
	}
	glEnd();
	glEndList();
	break;
    case 2:
	GfOut("Loading texture %s\n", graphic->background);
	BackgroundTex = grLoadTexture(graphic->background, buf, 1.8, 0);
	BackgroundList = glGenLists(1);
	glNewList(BackgroundList, GL_COMPILE);
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i < NB_BG_FACES/4 + 1; i++) {
	    alpha = (float)i * 2 * PI / (float)NB_BG_FACES;
	    texLen = (float)i / (float)NB_BG_FACES;
	    
	    x = BG_DIST * cos(alpha);
	    y = BG_DIST * sin(alpha);
	    
	    glTexCoord2f(texLen*4.0, 0.0);   glVertex3f(x, y, z1);
	    glTexCoord2f(texLen*4.0, 0.5); glVertex3f(x, y, z2);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (i = NB_BG_FACES/4; i < NB_BG_FACES/2 + 1; i++) {
	    alpha = (float)i * 2 * PI / (float)NB_BG_FACES;
	    texLen = (float)i / (float)NB_BG_FACES;
	    
	    x = BG_DIST * cos(alpha);
	    y = BG_DIST * sin(alpha);
	    
	    glTexCoord2f(texLen*4.0, 0.5);   glVertex3f(x, y, z1);
	    glTexCoord2f(texLen*4.0, 1.0); glVertex3f(x, y, z2);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (i = NB_BG_FACES/2; i < 3*NB_BG_FACES/4 + 1; i++) {
	    alpha = (float)i * 2 * PI / (float)NB_BG_FACES;
	    texLen = (float)i / (float)NB_BG_FACES;
	    
	    x = BG_DIST * cos(alpha);
	    y = BG_DIST * sin(alpha);
	    
	    glTexCoord2f(texLen*4.0, 0.0);   glVertex3f(x, y, z1);
	    glTexCoord2f(texLen*4.0, 0.5); glVertex3f(x, y, z2);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (i = 3*NB_BG_FACES/4; i < NB_BG_FACES + 1; i++) {
	    alpha = (float)i * 2 * PI / (float)NB_BG_FACES;
	    texLen = (float)i / (float)NB_BG_FACES;
	    
	    x = BG_DIST * cos(alpha);
	    y = BG_DIST * sin(alpha);
	    
	    glTexCoord2f(texLen*4.0, 0.5);   glVertex3f(x, y, z1);
	    glTexCoord2f(texLen*4.0, 1.0); glVertex3f(x, y, z2);
	}
	glEnd();
	glEndList();
	break;
    case 4:
	GfOut("Loading texture %s\n", graphic->background);
	BackgroundTex = grLoadTexture(graphic->background, buf, 1.8, 0);
	BackgroundList = glGenLists(1);
	glNewList(BackgroundList, GL_COMPILE);
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i < NB_BG_FACES/4 + 1; i++) {
	    alpha = (float)i * 2 * PI / (float)NB_BG_FACES;
	    texLen = (float)i / (float)NB_BG_FACES;
	    
	    x = BG_DIST * cos(alpha);
	    y = BG_DIST * sin(alpha);
	    
	    glTexCoord2f(texLen*4.0, 0.0);   glVertex3f(x, y, z1);
	    glTexCoord2f(texLen*4.0, 0.5); glVertex3f(x, y, z2);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (i = NB_BG_FACES/4; i < NB_BG_FACES/2 + 1; i++) {
	    alpha = (float)i * 2 * PI / (float)NB_BG_FACES;
	    texLen = (float)i / (float)NB_BG_FACES;
	    
	    x = BG_DIST * cos(alpha);
	    y = BG_DIST * sin(alpha);
	    
	    glTexCoord2f(texLen*4.0, 0.5);   glVertex3f(x, y, z1);
	    glTexCoord2f(texLen*4.0, 1.0); glVertex3f(x, y, z2);
	}
	glEnd();
	glEndList();
	GfOut("Loading texture %s\n", graphic->background2);
	BackgroundTex2 = grLoadTexture(graphic->background2, buf, 1.8, 0);
	BackgroundList2 = glGenLists(1);
	glNewList(BackgroundList2, GL_COMPILE);	
	glBegin(GL_QUAD_STRIP);
	for (i = NB_BG_FACES/2; i < 3*NB_BG_FACES/4 + 1; i++) {
	    alpha = (float)i * 2 * PI / (float)NB_BG_FACES;
	    texLen = (float)i / (float)NB_BG_FACES;
	    
	    x = BG_DIST * cos(alpha);
	    y = BG_DIST * sin(alpha);
	    
	    glTexCoord2f(texLen*4.0, 0.0);   glVertex3f(x, y, z1);
	    glTexCoord2f(texLen*4.0, 0.5); glVertex3f(x, y, z2);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (i = 3*NB_BG_FACES/4; i < NB_BG_FACES + 1; i++) {
	    alpha = (float)i * 2 * PI / (float)NB_BG_FACES;
	    texLen = (float)i / (float)NB_BG_FACES;
	    
	    x = BG_DIST * cos(alpha);
	    y = BG_DIST * sin(alpha);
	    
	    glTexCoord2f(texLen*4.0, 0.5);   glVertex3f(x, y, z1);
	    glTexCoord2f(texLen*4.0, 1.0); glVertex3f(x, y, z2);
	}
	glEnd();
	glEndList();
	break;
    default:
	break;
    }

    /* Environment Mapping Settings */
    grEnvSelector = new ssgStateSelector(graphic->envnb);
    grGammaValue = 1.8;
    grMipMap = 0;
    grFilePath = buf;
    for (i = 0; i < graphic->envnb; i++) {
      GfOut("Loading Environment Mapping Image %s\n", graphic->env[i]);
      envst = (ssgSimpleState*)grSsgLoadTexState(graphic->env[i]);
      envst->enable(GL_BLEND);
      grEnvSelector->setStep(i, envst);
    }
    grEnvSelector->selectStep(0); /* mandatory !!! */
    grEnvState=(grMultiTexState*)grSsgEnvTexState(graphic->env[0]);
    grEnvShadowState=(grMultiTexState*)grSsgEnvTexState("envshadow.png");
    if (grEnvShadowState==NULL)
      {
	ulSetError ( UL_WARNING, "grscene:initBackground Failed to open envshadow.png for reading") ;
	ulSetError ( UL_WARNING, "        mandatory for top env mapping ") ;
	ulSetError ( UL_WARNING, "        should be in the .xml !! ") ;
	ulSetError ( UL_WARNING, "        copy the envshadow.png from g-track-2 to the track you selected ") ;
	ulSetError ( UL_WARNING, "        c'est pas classe comme sortie, mais ca evite un crash ") ;
	exit(-1);
      }
}


void grDrawBackground(cGrCamera *cam)
{
    t3Dd *camPos;
    t3Dd *camCenter;
    t3Dd *camUp;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(67.5, grviewRatio, 0.1, 100000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camPos = cam->getPos();
    camCenter = cam->getCenter();
    camUp = cam->getUp();
   
    gluLookAt(camPos->x, camPos->y, camPos->z, 
	      camCenter->x, camCenter->y, camCenter->z,
	      camUp->x, camUp->y, camUp->z);
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glPushMatrix();
    glTranslatef(camPos->x, camPos->y, camPos->z);
    glBindTexture(GL_TEXTURE_2D, BackgroundTex);
    glCallList(BackgroundList);
    if (BackgroundType > 2) {
	glBindTexture(GL_TEXTURE_2D, BackgroundTex2);
	glCallList(BackgroundList2);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

/*     GLfloat fogColor[4]={0.4,0.4,0.5,0.5}; */
/*     glFogi(GL_FOG_MODE,GL_EXP2); */
/*     glFogfv(GL_FOG_COLOR,fogColor); */
/*     glFogf(GL_FOG_DENSITY,0.002); */
/*     glHint(GL_FOG_HINT,GL_DONT_CARE); */
/*     glFogf(GL_FOG_START,8000.0); */
/*     glFogf(GL_FOG_END, 10000); */
/*     glEnable(GL_FOG); */

}

static void
customizePits(void)
{
    tTrackPitInfo	*pits;
    int			i;
    tdble		x, y;
    tdble		x2, y2, z2;

    pits = &(grTrack->pits);
    /* draw the pit identification */

    switch (pits->type) {
    case TR_PIT_ON_TRACK_SIDE:
	for (i = 0; i < pits->nMaxPits; i++) {
	    char		buf[256];
	    t3Dd		normalvector;
	    sgVec3		vtx;
	    sgVec4		clr = {0,0,0,1};
	    sgVec3		nrm = {0,1,0};
	    sgVec2		tex;
	    ssgState		*st;
	    ssgVertexArray	*pit_vtx = new ssgVertexArray(4);
	    ssgTexCoordArray	*pit_tex = new ssgTexCoordArray(4);
	    ssgColourArray	*pit_clr = new ssgColourArray(1);
	    ssgNormalArray	*pit_nrm = new ssgNormalArray(1);
	    
	    pit_clr->add(clr);
	    pit_nrm->add(nrm);

	    if (pits->driversPits[i].car) {
		sprintf(buf, "drivers/%s/%d;drivers/%s;data/textures;data/img;.",
			pits->driversPits[i].car->_modName, pits->driversPits[i].car->_driverIndex,
			pits->driversPits[i].car->_modName);
	    } else {
		sprintf(buf, "data/textures;data/img;.");
	    }
	    
	    st = grSsgLoadTexStateEx("logo.rgb", buf, FALSE, FALSE);

	    RtTrackLocal2Global(&(pits->driversPits[i].pos), &x, &y, pits->driversPits[i].pos.type);
	    RtTrackSideNormalG(pits->driversPits[i].pos.seg, x, y, pits->side, &normalvector);
	    x2 = x - pits->width/2.0 * normalvector.x + pits->len/2.0 * normalvector.y;
	    y2 = y - pits->width/2.0 * normalvector.y - pits->len/2.0 * normalvector.x;
	    z2 = RtTrackHeightG(pits->driversPits[i].pos.seg, x2, y2);

	    tex[0] = -0.7;
	    tex[1] = 0.33;
	    vtx[0] = x2;
	    vtx[1] = y2;
	    vtx[2] = z2;
	    pit_tex->add(tex);
	    pit_vtx->add(vtx);
	    
	    tex[0] = -0.7;
	    tex[1] = 1.1;
	    vtx[0] = x2;
	    vtx[1] = y2;
	    vtx[2] = z2 + 4.8;
	    pit_tex->add(tex);
	    pit_vtx->add(vtx);
	    
	    x2 = x - pits->width/2.0 * normalvector.x - pits->len/2.0 * normalvector.y;
	    y2 = y - pits->width/2.0 * normalvector.y + pits->len/2.0 * normalvector.x;
	    z2 = RtTrackHeightG(pits->driversPits[i].pos.seg, x2, y2);

	    tex[0] = 1.3;
	    tex[1] = 0.33;
	    vtx[0] = x2;
	    vtx[1] = y2;
	    vtx[2] = z2;
	    pit_tex->add(tex);
	    pit_vtx->add(vtx);
	    
	    tex[0] = 1.3;
	    tex[1] = 1.1;
	    vtx[0] = x2;
	    vtx[1] = y2;
	    vtx[2] = z2 + 4.8;
	    pit_tex->add(tex);
	    pit_vtx->add(vtx);

	    ssgVtxTable *pit = new ssgVtxTable(GL_TRIANGLE_STRIP, pit_vtx, pit_nrm, pit_tex, pit_clr);
	    pit->setState(st);
	    pit->setCullFace(0);
	    TheScene->addKid(pit);
	}
	break;
    case TR_PIT_ON_SEPARATE_PATH:
	break;
    case TR_PIT_NONE:
	break;	
    }

}
