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

extern void gfDirInit(void);
extern void gfModInit(void);
extern void gfOsInit(void);
extern void gfParamInit(void);
extern void gfRlstInit(void);

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
    gfModInit();
    gfOsInit();
    gfParamInit();
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


/** Convert a time in seconds (float) to an ascii string.
    @ingroup	screen
    @param	sec	Time to convert
    @param	sgn	Flag to indicate if the sign (+) is to be displayed for positive values of time.
    @return	Time string.
    @warning	The returned string has to be free by the caller.
 */
char * 
GfTime2Str(tdble sec, int sgn)
{
    char  buf[256];
    char* sign;

    if (sec < 0.0) {
	sec = -sec;
	sign = "-";
    } else {
	if (sgn) {
	    sign = "+";
	} else {
	    sign = "  ";
	}
    }
    int h = (int)(sec / 3600.0);
    sec -= 3600 * h;
    int m = (int)(sec / 60.0);
    sec -= 60 * m;
    int s = (int)(sec);
    sec -= s;
    int c = (int)floor((sec) * 100.0);
    if (h) {
	(void)sprintf(buf, "%s%2.2d:%2.2d:%2.2d:%2.2d", sign,h,m,s,c);
    } else if (m) {
	(void)sprintf(buf, "   %s%2.2d:%2.2d:%2.2d", sign,m,s,c);
    } else {
	(void)sprintf(buf, "      %s%2.2d:%2.2d", sign,s,c);
    }
    return strdup(buf);
}


static char *localDir = "";
static char *libDir = "";
static char *dataDir = "";

char *
GetLocalDir(void)
{
    return localDir;
}

void
SetLocalDir(char *buf)
{
    localDir = strdup(buf);
}

char *
GetLibDir(void)
{
    return libDir;
}

void
SetLibDir(char *buf)
{
    libDir = strdup(buf);
}

char *
GetDataDir(void)
{
    return dataDir;
}

void
SetDataDir(char *buf)
{
    dataDir = strdup(buf);
}



static int singleTextureMode = 0;

int
GetSingleTextureMode (void)
{
    return singleTextureMode;
}

void
SetSingleTextureMode (void)
{   
    singleTextureMode = 1;
}
