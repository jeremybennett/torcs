/***************************************************************************

    file                 : grutil.cpp
    created              : Wed Nov  1 21:33:22 CET 2000
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
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include <plib/ssg.h>

#include <tgf.h>

#include "grutil.h"
#include "grmultitexstate.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

float		grGammaValue = 1.8;
int		grMipMap = 0;

char		*grFilePath = NULL;	/* Multiple path (; separated) used to search for files */
char		*grTexturePath = NULL;	/* Default ssg path */


int
grGetFilename(char *filename, char *filepath, char *buf)
{
    char	*c1, *c2;
    int		found = 0;
    int		lg;
    
    if (filepath) {
	c1 = filepath;
	c2 = c1;
	while ((!found) && (c2 != NULL)) {
	    c2 = strchr(c1, ';');
	    if (c2 == NULL) {
		sprintf(buf, "%s/%s", c1, filename);
	    } else {
		lg = c2 - c1;
		strncpy(buf, c1, lg);
		buf[lg] = '/';
		strcpy(buf + lg + 1, filename);
	    }
	    if (ulFileExists(buf)) {
		found = 1;
	    }
	    c1 = c2 + 1;
	}
    } else {
	strcpy(buf, filename);
	if (ulFileExists(buf)) {
	    found = 1;
	}
    }
    if (!found) {
	GfOut("File %s not found\n", filename);
	GfOut("File Path was %s\n", filepath);
	return 0;
    }

    return 1;
}


GLuint
grLoadTexture(char *filename, char *filepath, float screen_gamma, int mipmap)
{
    GLbyte	*tex;
    int		w, h;
    GLuint	image;
    GLenum	gluerr= (GLenum) 0;
    char	buf[256];

    if (!grGetFilename(filename, filepath, buf)) {
	return 0;
    }
    GfOut("Loading %s\n", buf);
    
    tex = (GLbyte*)GfImgReadPng(buf, &w, &h, screen_gamma);
    glGenTextures(1, &image);
    glBindTexture(GL_TEXTURE_2D, image);
    /* build the OPENGL texture */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (mipmap) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluerr=(GLenum)gluBuild2DMipmaps(GL_TEXTURE_2D, mipmap, w, w, GL_RGBA, 
					 GL_UNSIGNED_BYTE, (GLvoid *)(tex));
	if(gluerr) {
	    GfTrace("grLoadTexture: %s %s\n", buf, gluErrorString(gluerr));
	    free(tex);
	    return 0;
	}
    } else {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)(tex));
    }

#ifndef WIN32    
    /* free(tex); */
#endif
    glBindTexture(GL_TEXTURE_2D, 0);

    return image;
}


bool
grLoadPngTexture (const char *fname, ssgTextureInfo* info)
{
    GLbyte	*tex;
    int		w, h;
    GLenum	gluerr = (GLenum) 0;
    char 	*buf;
    char	*s;
    int		mipmap = 1;
    
    TRACE_GL("Load: grLoadPngTexture start");

    buf = strdup(fname);

    GfOut("Loading %s\n", buf);

    /* find the filename extension */
    s = strrchr(buf, '.');
    if (s) {
	*s = 0;
    }
    
    /* search for the texture parameters */
    s = strrchr(buf, '_');
      
    if (s) {
	/* no mipmap */
	if (strncmp(s, "_nmm", 4) == 0) {
	    mipmap = 0;
	}
    }
    free(buf);

    tex = (GLbyte*)GfImgReadPng(fname, &w, &h, 2.0);
    if (!tex) {
	return false;
    }
    /* build the OPENGL texture */
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (mipmap) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluerr=(GLenum)gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, 
					 GL_UNSIGNED_BYTE, (GLvoid *)(tex));
	if(gluerr) {
	    GfTrace("grLoadTexture: %s %s\n", fname, gluErrorString(gluerr));
	    free(tex);
	    return false;
	}
    } else {
	/* XXX Not working: why ? */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)(tex));
    }
    
    /* free(tex); */

    if (info) {
	info -> width  = w;
	info -> height = h;
	info -> depth  = 4;
	info -> alpha  = true;
    }
    TRACE_GL("Load: grLoadPngTexture stop");

    return true;
}


typedef struct stlist
{
    struct stlist	*next;
    ssgSimpleState	*state;
    char		*name;
} stlist;

static stlist * stateList = NULL;

static ssgSimpleState *
grGetState(char *img)
{
    stlist	*curr;
  
    curr = stateList;
    while (curr != NULL) {
	if (strcmp(curr->name, img) == 0) {
	    return curr->state;
	}
	curr = curr->next;
    }
    return NULL;
}

void
grShutdownState(void)
{
    stlist	*curr;
    stlist	*next;

    curr = stateList;
    while (curr != NULL) {
	next = curr->next;
	free(curr->name);
	//curr->state->deRef(); // it's already deleted
	free(curr);
	curr = next;
    }
    stateList = NULL;
}


ssgState *
grSsgLoadTexState(char *img)
{
    char		buf[256];
    char		*s;
    GLuint		tex;
    ssgSimpleState     	*st;
    stlist		*curr;

    /* remove the directory */
    s = strrchr(img, '/');
    if (s == NULL) {
	s = img;
    } else {
	s++;
    }
    if (!grGetFilename(s, grFilePath, buf)) {
	GfOut("grSsgLoadTexState: File %s not found\n", s);
	return NULL;
    }
    
    st = grGetState(buf);
    if (st != NULL) {
	return (ssgState*)st;
    }

    st = new ssgSimpleState;
    st->ref();			/* cannot be removed */
    st->enable(GL_LIGHTING);
    st->enable(GL_TEXTURE_2D);
    st->enable(GL_BLEND);
    st->setColourMaterial(GL_AMBIENT_AND_DIFFUSE);
   
    curr = (stlist*)calloc(sizeof(stlist), 1);
    curr->next = stateList;
    stateList = curr;
    curr->state = st;
    curr->name = strdup(buf);


    if (strcmp(buf + strlen(buf) - 4, ".png") == 0) {
	tex = grLoadTexture(buf, NULL, grGammaValue, grMipMap);
	st->setTexture(tex);
    } else {
	GfOut("Loading %s\n", buf);
	st->setTexture(buf);
    }
    return (ssgState*)st;
}

ssgState *
grSsgEnvTexState(char *img)
{
    char		buf[256];
    char		*s;
    GLuint		tex;
    grMultiTexState    	*st;
    stlist		*curr;

    /* remove the directory */
    s = strrchr(img, '/');
    if (s == NULL) {
	s = img;
    } else {
	s++;
    }
    if (!grGetFilename(s, grFilePath, buf)) {
	GfOut("grSsgLoadTexState: File %s not found\n", s);
	return NULL;
    }
    
    st = new grMultiTexState;
    st->ref();			/* cannot be removed */
    st->enable(GL_LIGHTING);
    st->enable(GL_TEXTURE_2D);
    st->enable(GL_BLEND);
    st->setColourMaterial(GL_AMBIENT_AND_DIFFUSE);
    
    curr = (stlist*)calloc(sizeof(stlist), 1);
    curr->next = stateList;
    stateList = curr;
    curr->state = st;
    curr->name = strdup(buf);

    if (strcmp(buf + strlen(buf) - 4, ".png") == 0) {
	tex = grLoadTexture(buf, NULL, grGammaValue, grMipMap);
	st->setTexture(tex);
    } else {
	GfOut("Loading %s\n", buf);
	st->setTexture(buf);
    }
    return (ssgState*)st;
}

ssgState *
grSsgLoadTexStateEx(char *img, char *filepath, int wrap, int mipmap)
{
    char		buf[256];
    char		*s;
    ssgSimpleState	*st;
    stlist		*curr;

    /* remove the directory */
    s = strrchr(img, '/');
    if (s == NULL) {
	s = img;
    } else {
	s++;
    }
    if (!grGetFilename(s, filepath, buf)) {
	GfOut("File %s not found\n", s);
	return NULL;
    }
    
    st = grGetState(buf);
    if (st != NULL) {
	return (ssgState*)st;
    }

    st = new ssgSimpleState;
    st->ref();			/* cannot be removed */
    st->enable(GL_LIGHTING);
    st->enable(GL_TEXTURE_2D);
    st->enable(GL_BLEND);
    st->setColourMaterial(GL_AMBIENT_AND_DIFFUSE);
    
    curr = (stlist*)calloc(sizeof(stlist), 1);
    curr->next = stateList;
    stateList = curr;
    curr->state = st;
    curr->name = strdup(buf);


    GfOut("Loading %s\n", buf);
    st->setTexture(buf, wrap, wrap, mipmap);
    
    return (ssgState*)st;
}

int
grPruneTree(ssgEntity *start, bool init)
{
    int		i;
    static int	nb;

    if (init == TRUE) {
	nb = 0;
    }

    for (i = start->getNumKids() - 1; i >= 0; i--) {
	ssgEntity *k = ((ssgBranch*)start)->getKid(i);
	if (k->getNumKids() != 0) {
	    grPruneTree(k, FALSE);
	}
	/* pruning can remove all the kids... */
	if (k->getNumKids() == 0) {
	    if (k->isAKindOf(ssgTypeBranch())) {
		((ssgBranch*)start)->removeKid(i);
		nb++;
#if AGGRESSIVE_PRUNING
	    } else if (k->isAKindOf(ssgTypeVtxTable())) {
		if (((ssgVtxTable*)k)->getNumVertices() == 0) {
		    ((ssgBranch*)start)->removeKid(i);
		    nb++;
		}
#endif
	    }
	}
    }
    return nb;
}

void
grForceState(ssgEntity *start, ssgState *state)
{
    int i;
    
    for (i = start->getNumKids() - 1; i >= 0; i--) {
	ssgEntity *k = ((ssgBranch*)start)->getKid(i);
	if (k->getNumKids() != 0) {
	    grForceState(k, state);
	} else {
	    if (k->isAKindOf(_SSG_TYPE_VTXTABLE)) {
		((ssgVtxTable*)k)->setState(state);
	    }
	}
    }
}
