/***************************************************************************
                          tgf.cpp -- The Gaming Framework                            
                             -------------------                                         
    created              : Fri Aug 13 22:31:43 CEST 1999
    copyright            : (C) 1999 by Eric Espie                         
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

#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <time.h>

#include "gui.h"

extern void gfDirInit(void);
extern void gfModInit(void);
extern void gfOsInit(void);
extern void gfParamInit(void);
extern void gfScreenInit(void);
/* extern void gfTraceInit(void); */
extern void gfMenuInit(void);
extern void gfRlstInit(void);

char *LocalDir = "";

// <esppat>
#ifdef WIN32
#include <crtdbg.h>
#include <assert.h>
void *
_tgf_win_malloc(size_t size)
{
#ifdef _DEBUG
 char * p = (char*)GlobalAlloc(GMEM_FIXED, size + 12 );

 *(int*)( p ) = size + 12;
 *( (int*)p + 1 ) = 123456789;
 *( (int*)( p + size + 12 ) - 1 ) = 987654321;

 return p + 8;
#else // _DEBUG
 char * p = (char*)GlobalAlloc(GMEM_FIXED, size + 4 );

 *(int*)( p ) = size;

 return p + 4;
#endif // _DEBUG
}

void *
_tgf_win_calloc(size_t num, size_t size)
{
 void * p = _tgf_win_malloc(num * size);
 memset(p, 0, num * size);
 return p;
}

void *
_tgf_win_realloc(void * memblock, size_t size)
{
 void * p = _tgf_win_malloc(size);

 if (!p) {
  _tgf_win_free(memblock);

  return NULL;
 }
 else {
  memcpy(p, memblock, min(*(int*)((char*)memblock-4), (int)size) );
  
  return p;
 }
}

void
_tgf_win_free(void * memblock)
{
 if (!memblock)
  return;

#ifdef _DEBUG
 char * p = (char*)memblock - 8;

 if ( !_CrtIsValidPointer( p, 4, TRUE ) )
  assert( 0 );

 if ( !_CrtIsValidPointer( p, *(int*)p, TRUE ) )
  assert( 0 );

 if ( *( (int*)p + 1 ) != 123456789 )
  assert( 0 );

 if( *( (int*)( p + *(int*)p ) - 1 ) != 987654321 )
  assert( 0 );

 GlobalFree((char*)memblock - 8);
#else // _DEBUG
 GlobalFree((char*)memblock - 4);
#endif // _DEBUG
}

char *
_tgf_win_strdup(const char * str)
{
 char * s = (char*)_tgf_win_malloc(strlen(str)+1);
 strcpy(s,str);

 return s;
}
#endif // WIN32
// </esppat>


void
GfInit(void)
{
    gfDirInit();
    gfuiInit();
    gfMenuInit();
    gfModInit();
    gfOsInit();
    gfParamInit();
    gfScreenInit();
    gfRlstInit();
/*     gfTraceInit(); */
}

void
gfMeanReset(tdble v, tMeanVal *pvt)
{
    int		i;

    for (i = 0; i < GF_MEAN_MAX_VAL; i++) {
	pvt->val[i] = v;
    }
}

tdble
gfMean(tdble v, tMeanVal *pvt, int n, int w)
{
    int		i;
    tdble	sum;
    
    if (n > pvt->curNum) {
	if (pvt->curNum < GF_MEAN_MAX_VAL) {
	    pvt->curNum++;
	}
	n = pvt->curNum;
    } else {
	pvt->curNum = n;
    }
    sum = 0;
    for (i = 0; i < n; i++) {
	pvt->val[i] = pvt->val[i + 1];
	sum += pvt->val[i];
    }
    pvt->val[n] = v;
    sum += (tdble)w * v;
    sum /= (tdble)(n + w);

    return sum;
}

static char bufstr[1024];

char *
GfGetTimeStr(void)
{
    struct tm		*stm;
    time_t		t;

    t = time(NULL);
    stm = localtime(&t);
    sprintf(bufstr, "%4d%02d%02d%02d%02d%02d",
	    stm->tm_year+1900,
	    stm->tm_mon+1,
	    stm->tm_mday,
	    stm->tm_hour,
	    stm->tm_min,
	    stm->tm_sec);

    return bufstr;
}

