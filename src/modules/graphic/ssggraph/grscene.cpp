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
#include "grutil.h"
#include "grssgext.h"

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

#define NB_BG_FACES	20
#define BG_DIST		1.0

ssgRoot *TheScene;

static void initBackground(void);

static void customizePits(void);

static ssgLoaderOptionsEx	grloaderOptions(NULL, NULL, NULL, NULL);


int grInitScene(tTrack *track)
{
    void	*hndl;
    char	*acname;
    ssgEntity	*desc;
    char	buf[256];

    grTrack = track;
    TheScene = new ssgRoot;
    initBackground();

    glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    grWrldX = (int)(track->max.x - track->min.x + 1);
    grWrldY = (int)(track->max.y - track->min.y + 1);
    grWrldZ = (int)(track->max.z - track->min.z + 1);
    grWrldMaxSize = (int)(MAX(MAX(grWrldX, grWrldY), grWrldZ));

    hndl = GfParmReadFile(track->filename, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    acname = GfParmGetStr(hndl, TRK_SECT_GRAPH, TRK_ATT_3DDESC, "track.ac");
    if (strlen(acname) == 0) {
	return -1;
    }

    sprintf(buf, "tracks/%s;data/textures;data/img;.", grTrack->internalname);
    ssgTexturePath(buf);
    sprintf(buf, "tracks/%s", grTrack->internalname);
    ssgModelPath(buf);
    
    desc = ssgLoad(acname, &grloaderOptions);

    TheScene->addKid(desc);

    customizePits();

    return 0;
}


void grDrawScene(void)
{
    TRACE_GL("refresh: ssgCullAndDraw start");

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    ssgCullAndDraw(TheScene);
    
    TRACE_GL("refresh: ssgCullAndDraw");
}

void grShutdownScene(void)
{
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

    sprintf(buf, "tracks/%s;data/img;data/textures;.", grTrack->internalname);

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
}


void grDrawBackground(struct Camera *cam)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(67.5, grviewRatio, 0.1, 100000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (cam->camtype) {
    case CAM_LOOKAT:
	gluLookAt(cam->ucam.lookat.eye[0], cam->ucam.lookat.eye[1], cam->ucam.lookat.eye[2],
		  cam->ucam.lookat.center[0], cam->ucam.lookat.center[1], cam->ucam.lookat.center[2],
		  cam->ucam.lookat.up[0], cam->ucam.lookat.up[1], cam->ucam.lookat.up[2]);
	break;

    case CAM_FCT:
	gluLookAt(cam->ucam.fcam.eye[0], cam->ucam.fcam.eye[1], cam->ucam.fcam.eye[2],
		  cam->ucam.fcam.center[0], cam->ucam.fcam.center[1], cam->ucam.fcam.center[2],
		  cam->ucam.fcam.up[0], cam->ucam.fcam.up[1], cam->ucam.fcam.up[2]);
	break;
    }
    

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glPushMatrix();
    glTranslatef(grCamPos.x, grCamPos.y, grCamPos.z);
    glBindTexture(GL_TEXTURE_2D, BackgroundTex);
    glCallList(BackgroundList);
    if (BackgroundType > 2) {
	glBindTexture(GL_TEXTURE_2D, BackgroundTex2);
	glCallList(BackgroundList2);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

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
