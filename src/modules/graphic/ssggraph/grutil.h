/***************************************************************************

    file                 : grutil.h
    created              : Wed Nov  1 22:35:08 CET 2000
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
 

#ifndef _GRUTIL_H_
#define _GRUTIL_H_

#include <stdio.h>

#define TRACE_GL(msg) { GLenum rc; if ((rc = glGetError()) != GL_NO_ERROR) printf("%s %s\n", msg, gluErrorString(rc)); }

#ifdef DEBUG
#define DBG_SET_NAME(base, name, index, subindex)		\
{								\
    char __buf__[256];						\
    if (subindex != -1) {					\
        sprintf(__buf__, "%s-%d-%d", name, index, subindex);	\
    } else {							\
	sprintf(__buf__, "%s-%d", name, index);			\
    }								\
    (base)->setName((const char *)__buf__);			\
}
#else
#define DBG_SET_NAME(base, name, index, subindex)
#endif
 

/* Vars to set before calling grSsgLoadTexCb */
extern float	grGammaValue;
extern int	grMipMap;

extern char *grFilePath;	/* Multiple path (: separated) used to search for files */
extern char *grTexturePath;


extern int grGetFilename(char *filename, char *filepath, char *buf);
extern GLuint grLoadTexture(char *filename, char *filepath, float screen_gamma, int mipmap);
extern ssgState *grSsgLoadTexState(char *img);
extern ssgState *grSsgLoadTexStateEx(char *img, char *filepath, int wrap, int mipmap);
extern int grPruneTree(ssgEntity *start, bool init);
extern void grForceState(ssgEntity *start, ssgState *state);
extern bool grLoadPngTexture (const char *fname, ssgTextureInfo* info);

#endif /* _GRUTIL_H_ */ 



