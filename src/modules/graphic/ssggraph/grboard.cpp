/***************************************************************************

    file                 : grboard.cpp
    created              : Thu Aug 17 23:52:20 CEST 2000
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


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <plib/ssg.h>

#include "grcam.h"
#include "grboard.h"
#include "grscene.h"
#include "grssgext.h"
#include "grshadow.h"
#include "grskidmarks.h"
#include "grsmoke.h"
#include "grcar.h"
#include "grmain.h"
#include "grutil.h"
#include <robottools.h>

#ifdef DMALLOC
#include "dmalloc.h"
#endif

static float grWhite[4] = {1.0, 1.0, 1.0, 1.0};
static float grRed[4] = {1.0, 0.0, 0.0, 1.0};
static float grBlue[4] = {0.0, 0.0, 1.0, 1.0};

#define NB_BOARDS	3

int grBoardWinx = 0;
int grBoardWinw = 800;
int grBoardWiny = 0;
int grBoardWinh = 600;

void
grSelectBoard(void *vp)
{
    int		val = (int)vp;
    
    switch (val) {
    case 0:
	grBoardFlag = (grBoardFlag + 1) % NB_BOARDS;
	GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_BOARD,
		     (char*)NULL, (tdble)grBoardFlag);
	break;
    case 1:
	grCounterFlag = 1 - grCounterFlag;
	GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_COUNTER,
		     (char*)NULL, (tdble)grCounterFlag);
	break;
    case 2:
	grLeaderFlag = 1 - grLeaderFlag;
	GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_LEADER,
		     (char*)NULL, (tdble)grLeaderFlag);
	break;
    case 3:
	grDebugFlag = 1 - grDebugFlag;
	GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_DEBUG,
		     (char*)NULL, (tdble)grDebugFlag);
	break;	
    case 4:
	grGFlag = 1 - grGFlag;
	GfParmSetNum(grHandle, GR_SCT_DISPMODE, GR_ATT_GGRAPH,
		     (char*)NULL, (tdble)grGFlag);
	break;	
    }
    GfParmWriteFile("config/graph.xml", grHandle, "graph", GFPARM_PARAMETER, "../dtd/params.dtd");    
}


static void 
writeTime(float *color, int font, int x, int y, tdble sec, int sgn)
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
    GfuiPrintString(buf, color, font, x, y, GFUI_ALIGN_HR_VB);
}

void
grDispDebug(float fps, tCarElt *car, tSituation * /* s */)
{
    char buf[256];
    int  x, y;
    tRoadCam *curCam;

    curCam = car->_trkPos.seg->cam;
    
    x = grBoardWinx + grBoardWinw - 100;
    y = grBoardWiny + grBoardWinh - 30;
    
    sprintf(buf, "FPS: %.1f", fps);
    GfuiPrintString(buf, grWhite, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    return;
    
    y -= 15;
    sprintf(buf, "Seg: %s", car->_trkPos.seg->name);
    GfuiPrintString(buf, grWhite, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    y -= 15;
    if (curCam) {
	sprintf(buf, "Cam: %s", curCam->name);
	GfuiPrintString(buf, grWhite, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
	y -= 15;
    }
	
}

void 
grDispGGraph(tCarElt *car)
{
    tdble X1, Y1, X2, Y2;    

    X1 = (tdble)(grBoardWinx + grBoardWinw - 100);
    Y1 = (tdble)(grBoardWiny + 100);
   
    X2 = -car->_DynGC.acc.y / 9.81 * 25.0 + X1;
    Y2 = car->_DynGC.acc.x / 9.81 * 25.0 + Y1;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(X1-50, Y1);
    glVertex2f(X1+50, Y1);
    glVertex2f(X1, Y1-50);
    glVertex2f(X1, Y1+50);
    glEnd();

#define THNSS	2.0
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(X1 - THNSS, Y1);
    glVertex2f(X1 + THNSS, Y1);
    glVertex2f(X1 + THNSS, Y1 + car->ctrl->accelCmd * 50.0);
    glVertex2f(X1 - THNSS, Y1 + car->ctrl->accelCmd * 50.0);

    glVertex2f(X1 - THNSS, Y1);
    glVertex2f(X1 + THNSS, Y1);
    glVertex2f(X1 + THNSS, Y1 - car->ctrl->brakeCmd * 50.0);
    glVertex2f(X1 - THNSS, Y1 - car->ctrl->brakeCmd * 50.0);

    glVertex2f(X1, Y1 - THNSS);
    glVertex2f(X1, Y1 + THNSS);
    glVertex2f(X1 - car->ctrl->steer * 100.0, Y1 + THNSS);
    glVertex2f(X1 - car->ctrl->steer * 100.0, Y1 - THNSS);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(X1, Y1);
    glVertex2f(X2, Y2);
    glEnd();

}

static void
grDispCarBoard1(tCarElt *car, tSituation *s)
{
    int  x, x2, y;
    char buf[256];
    float *clr;
    int dy, dy2, dx;
    
    x = 10;
    x2 = 110;
    dy = GfuiFontHeight(GFUI_FONT_MEDIUM_C);
    dy2 = GfuiFontHeight(GFUI_FONT_SMALL_C);
    y = grBoardWiny + grBoardWinh - dy - 5;
    sprintf(buf, "%d/%d - %s", car->_pos, s->_ncars, car->_name);
    dx = GfuiFontWidth(GFUI_FONT_MEDIUM_C, buf);
    dx = MAX(dx, (x2-x));
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
    glBegin(GL_QUADS);
    glColor4f(0.1, 0.1, 0.1, 0.8);
    glVertex2f(x-5, y + dy);
    glVertex2f(x+dx+5, y + dy);
    glVertex2f(x+dx+5, y-5 - dy2 * 8 /* lines */);
    glVertex2f(x-5, y-5 - dy2 * 8 /* lines */);
    glEnd();
    glDisable(GL_BLEND);

    GfuiPrintString(buf, grCarInfo[car->index].iconColor, GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB);
    y -= dy;

    dy = GfuiFontHeight(GFUI_FONT_SMALL_C);

    GfuiPrintString("Fuel:", grWhite, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    if (car->_fuel < 5.0) {
	clr = grRed;
    } else {
	clr = grWhite;
    }
    sprintf(buf, "%.1f l", car->_fuel);
    GfuiPrintString(buf, clr, GFUI_FONT_SMALL_C, x2, y, GFUI_ALIGN_HR_VB);
    y -= dy;
    
    if (car->_state & RM_CAR_STATE_BROKEN) {
	clr = grRed;
    } else {
	clr = grWhite;
    }
    
    GfuiPrintString("Dammages:", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    sprintf(buf, "%d", car->_dammage);
    GfuiPrintString(buf, clr, GFUI_FONT_SMALL_C, x2, y, GFUI_ALIGN_HR_VB);
    y -= dy;
    clr = grWhite;

    GfuiPrintString("Laps:", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    sprintf(buf, "%d / %d", car->_laps, s->_totLaps);
    GfuiPrintString(buf, clr, GFUI_FONT_SMALL_C, x2, y, GFUI_ALIGN_HR_VB);
    y -= dy;

    GfuiPrintString("Total:", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    writeTime(clr, GFUI_FONT_SMALL_C, x2, y, s->currentTime, 0);
    y -= dy;

    GfuiPrintString("Curr:", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    writeTime(clr, GFUI_FONT_SMALL_C, x2, y, car->_curLapTime, 0);    
    y -= dy;

    GfuiPrintString("Last:", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    writeTime(clr, GFUI_FONT_SMALL_C, x2, y, car->_lastLapTime, 0);    
    y -= dy;

    GfuiPrintString("Best:", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    writeTime(clr, GFUI_FONT_SMALL_C, x2, y, car->_bestLapTime, 0);    
    y -= dy;

    GfuiPrintString("Top Speed:", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    sprintf(buf, "%d", (int)(car->_topSpeed * 3.6));
    GfuiPrintString(buf, clr, GFUI_FONT_SMALL_C, x2, y, GFUI_ALIGN_HR_VB);
    y -= dy;
}

static void
grDispCarBoard2(tCarElt *car, tSituation *s)
{
    int  x, x2, x3, y;
    char buf[256];
    float *clr;
    int dy, dy2, dx;
    int lines, i;
    
    x = 10;
    x2 = 110;
    x3 = 170;
    dy = GfuiFontHeight(GFUI_FONT_MEDIUM_C);
    dy2 = GfuiFontHeight(GFUI_FONT_SMALL_C);

    y = grBoardWiny + grBoardWinh - dy - 5;

    sprintf(buf, "%d/%d - %s", car->_pos, s->_ncars, car->_name);
    dx = GfuiFontWidth(GFUI_FONT_MEDIUM_C, buf);
    dx = MAX(dx, (x3-x));
    lines = 7;
    for (i = 0; i < 4; i++) {
	if (car->ctrl->msg[i]) {
	    lines++;
	}
    }
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
    glBegin(GL_QUADS);
    glColor4f(0.1, 0.1, 0.1, 0.8);
    glVertex2f(x-5, y + dy);
    glVertex2f(x+dx+5, y + dy);
    glVertex2f(x+dx+5, y-5 - dy2 * lines);
    glVertex2f(x-5, y-5 - dy2 * lines);
    glEnd();
    glDisable(GL_BLEND);

    GfuiPrintString(buf, grCarInfo[car->index].iconColor, GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB);
    y -= dy;

    dy = GfuiFontHeight(GFUI_FONT_SMALL_C);

    GfuiPrintString("Fuel:", grWhite, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    if (car->_fuel < 5.0) {
	clr = grRed;
    } else {
	clr = grWhite;
    }
    sprintf(buf, "%.1f l", car->_fuel);
    GfuiPrintString(buf, clr, GFUI_FONT_SMALL_C, x2, y, GFUI_ALIGN_HR_VB);
    y -= dy;

    if (car->_state & RM_CAR_STATE_BROKEN) {
	clr = grRed;
    } else {
	clr = grWhite;
    }
    
    GfuiPrintString("Dammages:", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    sprintf(buf, "%d", car->_dammage);
    GfuiPrintString(buf, clr, GFUI_FONT_SMALL_C, x2, y, GFUI_ALIGN_HR_VB);
    y -= dy;
    clr = grWhite;
    
    GfuiPrintString("Laps:", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    sprintf(buf, "%d / %d", car->_laps, s->_totLaps);
    GfuiPrintString(buf, clr, GFUI_FONT_SMALL_C, x2, y, GFUI_ALIGN_HR_VB);
    y -= dy;

    GfuiPrintString("Best:", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    writeTime(clr, GFUI_FONT_SMALL_C, x2, y, car->_bestLapTime, 0);
    writeTime(clr, GFUI_FONT_SMALL_C, x3, y, car->_deltaBestLapTime, 1);
    y -= dy;

    GfuiPrintString("Time:", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
    writeTime(clr, GFUI_FONT_SMALL_C, x2, y, car->_curLapTime, 0);    
    y -= dy;

    if (car->_pos != 1) {
	sprintf(buf, "<- %s", s->cars[car->_pos - 2]->_name);
	GfuiPrintString(buf, clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
	if (s->cars[car->_pos - 2]->_laps == car->_laps) {
	    writeTime(clr, GFUI_FONT_SMALL_C, x3, y, s->cars[car->_pos - 2]->_curTime-car->_curTime, 1);
	} else {
	    GfuiPrintString("       --:--", clr, GFUI_FONT_SMALL_C, x3, y, GFUI_ALIGN_HR_VB);
	}
    } else {
	GfuiPrintString("<- ", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
	GfuiPrintString("       --:--", clr, GFUI_FONT_SMALL_C, x3, y, GFUI_ALIGN_HR_VB);
    }
    y -= dy;

    if (car->_pos != s->_ncars) {
	sprintf(buf, "-> %s", s->cars[car->_pos]->_name);
	GfuiPrintString(buf, clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
	if (s->cars[car->_pos]->_laps == car->_laps) {
	    writeTime(clr, GFUI_FONT_SMALL_C, x3, y, s->cars[car->_pos]->_curTime-car->_curTime, 1);    
	} else {
	    GfuiPrintString("       --:--", clr, GFUI_FONT_SMALL_C, x3, y, GFUI_ALIGN_HR_VB);
	}
    } else {
	GfuiPrintString("-> ", clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
	GfuiPrintString("       --:--", clr, GFUI_FONT_SMALL_C, x3, y, GFUI_ALIGN_HR_VB);
    }
    y -= dy;
    for (i = 0; i < 4; i++) {
	if (car->ctrl->msg[i]) {
	    GfuiPrintString(car->ctrl->msg[i], car->ctrl->msgColor, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
	    y -= dy;
	}
    }
    
}

void
grDispCarBoard(tCarElt *car, tSituation *s)
{
    switch(grBoardFlag) {
    case 0:
	break;
    case 1:
	grDispCarBoard1(car, s);
	break;
    case 2:
	grDispCarBoard2(car, s);
	break;
    default:
	break;
    }
}

static const char *gearStr[MAX_GEARS] = {"R", "N", "1", "2", "3", "4", "5", "6", "7", "8"};

void
grDispCounterBoard(tCarElt *car)
{
    int  x, y;
    char buf[256];
    GLfloat ledcolg[2][3] = { 
	{0.0, 0.2, 0.0},
	{0.0, 1.0, 0.0}
    };
    GLfloat ledcolr[2][3] = { 
	{0.2, 0.0, 0.0},
	{1.0, 0.0, 0.0}
    };
    int i;
    int	ledNb     = 20;
    int ledHeight = 10;
    int ledWidth  = 5;
    int ledSpace  = 2;
    int ledRed    = (int)((car->_enginerpmRedLine / car->_enginerpmMax) * (tdble)ledNb);
    int ledLit	  = (int)((car->_enginerpm / car->_enginerpmMax) * (tdble)ledNb);
    
    x = grBoardWinx + grBoardWinw / 2 - ((ledNb * ledWidth) + (ledNb - 1) * ledSpace) / 2;
    y = grBoardWiny + MAX(GfuiFontHeight(GFUI_FONT_BIG_C), GfuiFontHeight(GFUI_FONT_DIGIT));
    glBegin(GL_QUADS);
    glColor3f(0.1, 0.1, 0.1);
    glVertex2f(x - ledSpace, y + ledHeight + ledSpace);
    glVertex2f(x + ledNb * (ledWidth+ ledSpace), y + ledHeight + ledSpace);
    glVertex2f(x + ledNb * (ledWidth+ ledSpace), grBoardWiny);
    glVertex2f(x - ledSpace, grBoardWiny);
    for (i = 0; i < ledRed; i++) {
	if (i <= ledLit) {
	    glColor3fv(ledcolg[1]);
	} else {
	    glColor3fv(ledcolg[0]);
	}
	glVertex2f(x, y);
	glVertex2f(x + ledWidth, y);
	glVertex2f(x + ledWidth, y + ledHeight);
	glVertex2f(x, y + ledHeight);
	x += ledWidth + ledSpace;
    }
    for (i = ledRed; i < ledNb; i++) {
	if (i <= ledLit) {
	    glColor3fv(ledcolr[1]);
	} else {
	    glColor3fv(ledcolr[0]);
	}
	glVertex2f(x, y);
	glVertex2f(x + ledWidth, y);
	glVertex2f(x + ledWidth, y + ledHeight);
	glVertex2f(x, y + ledHeight);
	x += ledWidth + ledSpace;
    }
    glEnd();


    x = grBoardWinx + grBoardWinw/2;
    y = grBoardWiny;
    sprintf(buf, " kph %s", gearStr[car->_gear+car->_gearOffset]);
    GfuiPrintString(buf, grBlue, GFUI_FONT_BIG_C, x, y, GFUI_ALIGN_HL_VB);

    x = grBoardWinx + grBoardWinw/2;
    sprintf(buf, "%3d", abs((int)(car->_speed_x * 3.6)));
    GfuiPrintString(buf, grBlue, GFUI_FONT_DIGIT, x, y, GFUI_ALIGN_HR_VB);
}

void
grDispLeaderBoard(tCarElt *car, tSituation *s)
{
    int  x, x2, y, i, j;
    char buf[256];
    int maxi = MIN(grLeaderNb, s->_ncars);
    float *clr;
    int dy;
    int drawCurrent;

    x = grBoardWinx + 5;
    x2 = grBoardWinx + 170;
    y = grBoardWiny + 10;
    dy = GfuiFontHeight(GFUI_FONT_SMALL_C);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
    glBegin(GL_QUADS);
    glColor4f(0.1, 0.1, 0.1, 0.8);
    glVertex2f(x, grBoardWiny + 5);
    glVertex2f(grBoardWinx + 180, grBoardWiny + 5);
    glVertex2f(grBoardWinx + 180, y+ dy*maxi);
    glVertex2f(x, y+ dy*maxi);
    glEnd();
    glDisable(GL_BLEND);

    if (s->current+1 > maxi) {
	drawCurrent = 1;
    } else {
	drawCurrent = 0;
    }
    for (j = maxi; j > 0; j--) {
	if (drawCurrent) {
	    i = s->current+1;
	    drawCurrent = 0;
	} else {
	    i = j;
	}
	if (i == s->current+1) {
	    clr = grCarInfo[car->index].iconColor;
	    drawCurrent = 0;
	} else {
	    clr = grWhite;
	}
	sprintf(buf, "%3d: %s", i, s->cars[i-1]->_name);
	GfuiPrintString(buf, clr, GFUI_FONT_SMALL_C, x, y, GFUI_ALIGN_HL_VB);
	
	if (s->cars[i-1]->_state & RM_CAR_STATE_DNF) {
	    GfuiPrintString("       out", grRed, GFUI_FONT_SMALL_C, x2, y, GFUI_ALIGN_HR_VB);
	} else if (s->cars[i-1]->_timeBehindLeader == 0) {
	    if (i != 1) {
		GfuiPrintString("       --:--", clr, GFUI_FONT_SMALL_C, x2, y, GFUI_ALIGN_HR_VB);
	    } else {
		writeTime(clr, GFUI_FONT_SMALL_C, x2, y, s->cars[i-1]->_curTime, 0);
	    }
	} else {
	    if (i == 1) {
		writeTime(clr, GFUI_FONT_SMALL_C, x2, y, s->cars[i-1]->_curTime, 0);
	    } else {
		if (s->cars[i-1]->_lapsBehindLeader == 0) {
		    writeTime(clr, GFUI_FONT_SMALL_C, x2, y, s->cars[i-1]->_timeBehindLeader, 1);
		} else {
		    if (s->cars[i-1]->_lapsBehindLeader > 1) {
			sprintf(buf, "+%3d Laps", s->cars[i-1]->_lapsBehindLeader);
		    } else {
			sprintf(buf, "+%3d Lap", s->cars[i-1]->_lapsBehindLeader);
		    }
		    GfuiPrintString(buf, clr, GFUI_FONT_SMALL_C, x2, y, GFUI_ALIGN_HR_VB);
		}
	    }
	}
	y += dy;
    }
}

class myLoaderOptions : public ssgLoaderOptions
{
public:
  virtual void makeModelPath ( char* path, const char *fname ) const
  {
    ulFindFile ( path, model_dir, fname, NULL ) ;
  }

  virtual void makeTexturePath ( char* path, const char *fname ) const
  {
    ulFindFile ( path, texture_dir, fname, NULL ) ;
  }
} ;

void
grInitBoardCar(tCarElt *car)
{
    char		buf[4096];
    int			index;
    void		*handle;
    char		*param;
    myLoaderOptions	options ;
    tgrCarInfo		*carInfo;
    tgrCarInstrument	*curInst;
    tdble		xSz, ySz, xpos, ypos;
    tdble		needlexSz, needleySz;
    
    ssgSetCurrentOptions ( &options ) ;    
    
    index = car->index;	/* current car's index */
    carInfo = &grCarInfo[index];
    handle = car->_carHandle;

    /* Tachometer */
    curInst = &(carInfo->instrument[0]);
    
    /* Load the Tachometer texture */
    param = GfParmGetStr(handle, SECT_GROBJECTS, PRM_TACHO_TEX, "rpm8000.rgb");
    sprintf(buf, "drivers/%s/%d;drivers/%s;cars/%s;data/textures", car->_modName, car->_driverIndex, car->_modName, car->_carName);
    grFilePath = strdup(buf);
    curInst->texture = (ssgSimpleState*)grSsgLoadTexState(param);
    free(grFilePath);

    /* Load the intrument placement */
    xSz = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_XSZ, (char*)NULL, 128);
    ySz = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_YSZ, (char*)NULL, 128);
    xpos = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_XPOS, (char*)NULL, grBoardWinw / 2.0 - xSz);
    ypos = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_YPOS, (char*)NULL, 0);
    needlexSz = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_NDLXSZ, (char*)NULL, 50);
    needleySz = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_NDLYSZ, (char*)NULL, 2);
    curInst->needleXCenter = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_XCENTER, (char*)NULL, xSz / 2.0) + xpos;
    curInst->needleYCenter = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_YCENTER, (char*)NULL, ySz / 2.0) + ypos;
    curInst->digitXCenter = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_XDIGITCENTER, (char*)NULL, xSz / 2.0) + xpos;
    curInst->digitYCenter = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_YDIGITCENTER, (char*)NULL, 16) + ypos; 
    curInst->minValue = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_MINVAL, (char*)NULL, 0);
    curInst->maxValue = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_MAXVAL, (char*)NULL, RPM2RADS(10000)) - curInst->minValue;
    curInst->minAngle = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_MINANG, "deg", 225);
    curInst->maxAngle = GfParmGetNum(handle, SECT_GROBJECTS, PRM_TACHO_MAXANG, "deg", -45) - curInst->minAngle;
    curInst->monitored = &(car->_enginerpm);
    curInst->prevVal = curInst->minAngle;
    
    curInst->CounterList = glGenLists(1);
    glNewList(curInst->CounterList, GL_COMPILE);
    glBegin(GL_TRIANGLE_STRIP);
    {
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex2f(xpos, ypos);
	glTexCoord2f(0.0, 1.0); glVertex2f(xpos, ypos + ySz);
	glTexCoord2f(1.0, 0.0); glVertex2f(xpos + xSz, ypos);
	glTexCoord2f(1.0, 1.0); glVertex2f(xpos + xSz, ypos + ySz);
    }
    glEnd();
    glEndList();

    curInst->needleList = glGenLists(1);
    glNewList(curInst->needleList, GL_COMPILE);
    glBegin(GL_TRIANGLE_STRIP);
    {
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex2f(0, -needleySz);
	glVertex2f(0, needleySz);
	glVertex2f(needlexSz, -needleySz / 2.0);
	glVertex2f(needlexSz, needleySz / 2.0);
    }
    glEnd();
    glEndList();


    /* Speedometer */
    curInst = &(carInfo->instrument[1]);
    
    /* Load the Speedometer texture */
    param = GfParmGetStr(handle, SECT_GROBJECTS, PRM_SPEEDO_TEX, "speed360.rgb");
    sprintf(buf, "drivers/%s/%d;drivers/%s;cars/%s;data/textures", car->_modName, car->_driverIndex, car->_modName, car->_carName);
    grFilePath = strdup(buf);
    curInst->texture = (ssgSimpleState*)grSsgLoadTexState(param);
    free(grFilePath);

    /* Load the intrument placement */
    xSz = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_XSZ, (char*)NULL, 128);
    ySz = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_YSZ, (char*)NULL, 128);
    xpos = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_XPOS, (char*)NULL, grBoardWinw / 2.0);
    ypos = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_YPOS, (char*)NULL, 0);
    needlexSz = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_NDLXSZ, (char*)NULL, 50);
    needleySz = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_NDLYSZ, (char*)NULL, 2);
    curInst->needleXCenter = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_XCENTER, (char*)NULL, xSz / 2.0) + xpos;
    curInst->needleYCenter = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_YCENTER, (char*)NULL, ySz / 2.0) + ypos;
    curInst->digitXCenter = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_XDIGITCENTER, (char*)NULL, xSz / 2.0) + xpos;
    curInst->digitYCenter = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_YDIGITCENTER, (char*)NULL, 10) + ypos; 
    curInst->minValue = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_MINVAL, (char*)NULL, 0);
    curInst->maxValue = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_MAXVAL, (char*)NULL, 100) - curInst->minValue;
    curInst->minAngle = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_MINANG, "deg", 225);
    curInst->maxAngle = GfParmGetNum(handle, SECT_GROBJECTS, PRM_SPEEDO_MAXANG, "deg", -45) - curInst->minAngle;
    curInst->monitored = &(car->_speed_x);
    curInst->prevVal = curInst->minAngle;
    
    curInst->CounterList = glGenLists(1);
    glNewList(curInst->CounterList, GL_COMPILE);
    glBegin(GL_TRIANGLE_STRIP);
    {
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex2f(xpos, ypos);
	glTexCoord2f(0.0, 1.0); glVertex2f(xpos, ypos + ySz);
	glTexCoord2f(1.0, 0.0); glVertex2f(xpos + xSz, ypos);
	glTexCoord2f(1.0, 1.0); glVertex2f(xpos + xSz, ypos + ySz);
    }
    glEnd();
    glEndList();

    curInst->needleList = glGenLists(1);
    glNewList(curInst->needleList, GL_COMPILE);
    glBegin(GL_TRIANGLE_STRIP);
    {
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex2f(0, -needleySz);
	glVertex2f(0, needleySz);
	glVertex2f(needlexSz, -needleySz / 2.0);
	glVertex2f(needlexSz, needleySz / 2.0);
    }
    glEnd();
    glEndList();
    
}

void
grDispCounterBoard2(tCarElt *car)
{
    int			index;
    tgrCarInstrument	*curInst;
    tdble		val;
    char		buf[32];

    index = car->index;	/* current car's index */
    curInst = &(grCarInfo[index].instrument[0]);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, curInst->texture->getTextureHandle());
    glCallList(curInst->CounterList);
    glBindTexture(GL_TEXTURE_2D, 0);

    val = (*(curInst->monitored) - curInst->minValue) / curInst->maxValue;
    if (val > 1.0) {
	val = 1.0;
    } else if (val < 0.0) {
	val = 0.0;
    }
    
    val = curInst->minAngle + val * curInst->maxAngle;

    RELAXATION(val, curInst->prevVal, 30);
    
    glPushMatrix();
    glTranslatef(curInst->needleXCenter, curInst->needleYCenter, 0);
    glRotatef(val, 0, 0, 1);
    glCallList(curInst->needleList);
    glPopMatrix();

    GfuiPrintString((char*)(gearStr[car->_gear+car->_gearOffset]), grRed, GFUI_FONT_BIG_C,
		    (int)curInst->digitXCenter, (int)(curInst->digitYCenter), GFUI_ALIGN_HC_VB);

   
    curInst = &(grCarInfo[index].instrument[1]);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, curInst->texture->getTextureHandle());
    glCallList(curInst->CounterList);
    glBindTexture(GL_TEXTURE_2D, 0);

    val = (*(curInst->monitored) - curInst->minValue) / curInst->maxValue;
    if (val > 1.0) {
	val = 1.0;
    } else if (val < 0.0) {
	val = 0.0;
    }
    val = curInst->minAngle + val * curInst->maxAngle;

    RELAXATION(val, curInst->prevVal, 30);
    
    glPushMatrix();
    glTranslatef(curInst->needleXCenter, curInst->needleYCenter, 0);
    glRotatef(val, 0, 0, 1);
    glCallList(curInst->needleList);
    glPopMatrix();

    sprintf(buf, "%3d", abs((int)(car->_speed_x * 3.6)));
    GfuiPrintString(buf, grBlue, GFUI_FONT_DIGIT,
		    (int)curInst->digitXCenter, (int)(curInst->digitYCenter), GFUI_ALIGN_HC_VB);
   
}

void
grInitBoard(void)
{
}

void
grShutdownBoard(void)
{
}


