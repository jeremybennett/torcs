/***************************************************************************
                  driverselect.cpp -- drivers interactive selection                              
                             -------------------                                         
    created              : Mon Aug 16 20:40:44 CEST 1999
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

/** @file
    		This is a set of tools useful for race managers.
    @ingroup	racemantools
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <track.h>
#include <car.h>
#include <raceman.h>
#include <robot.h>
#include <racemantools.h>

#ifdef DMALLOC
#include "dmalloc.h"
#endif


static void		*scrHandle;
static tRmDrvSelect	*ds;
static int		selectedScrollList, unselectedScrollList;
static int		DrvLabelId;
static int		FocDrvLabelId;
static int		PickDrvNameLabelId;
static int		PickDrvCarLabelId;
static int		PickDrvCategoryLabelId;
static float		aColor[] = {1.0, 0.0, 0.0, 1.0};
static char		buf[256];    


typedef struct DrvElt
{
    struct DrvElt	*next;
    struct DrvElt	*prev;
    int			index;
    char		*dname;
    char		*name;
    int			sel;
} tDrvElt;

static tRingListHead DrvList = {(tRingList*)&DrvList, (tRingList*)&DrvList};

static void rmFreeDrvList(void);

static void
rmdsActivate(void * /* notused */)
{
    /* call display function of graphic */
}

static void
rmdsDeactivate(void * /* notused */)
{
    rmFreeDrvList();    
    GfuiScreenRelease(scrHandle);
    
    if (ds->prevScreen) {
	GfuiScreenActivate(ds->prevScreen);
    }
}

static void
rmdsSetFocus(void * /* dummy */)
{
    char	*name;
    tDrvElt	*curDrv;

    name = GfuiScrollListGetSelectedElement(scrHandle, selectedScrollList, (void**)&curDrv);
    if (name) {
	GfParmSetStr(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSED, curDrv->dname);
	GfParmSetNum(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, (char*)NULL, curDrv->index);
	GfuiLabelSetText(scrHandle, FocDrvLabelId, curDrv->name);
    }
}


static void
rmdsSelect(void * /* dummy */)
{
    char	*name;
    tDrvElt	*curDrv;
    int		index;
    
    sprintf(buf, "%s/%s", RM_SECT_DRIVERS, RM_LIST_DRIVERS);
    GfParmListClean(ds->param, buf);
    name = GfuiScrollListExtractElement(scrHandle, selectedScrollList, 0, (void**)&curDrv);
    index = 1;
    while (name != NULL) {
	sprintf(buf, "%s/%s/%d", RM_SECT_DRIVERS, RM_LIST_DRIVERS, index);
	GfParmSetNum(ds->param, buf, RM_ATTR_IDX, (char*)NULL, curDrv->index);
	GfParmSetStr(ds->param, buf, RM_ATTR_MODULE, curDrv->dname);
	index++;
	name = GfuiScrollListExtractElement(scrHandle, selectedScrollList, 0, (void**)&curDrv);
    }
    GfParmSetNum(ds->param, RM_SECT_DRIVERS, RM_ATTR_NDRIVERS, (char*)NULL, index-1);
    rmdsDeactivate(NULL);
}

static void
rmMove(void *vd)
{
    GfuiScrollListMoveSelectedElement(scrHandle, selectedScrollList, (int)vd);
    GfuiScrollListMoveSelectedElement(scrHandle, unselectedScrollList, (int)vd);
}

static void
rmdsClickOnDriver(void *dummy)
{
    char	*name;
    tDrvElt	*curDrv;
    void	*robhdle;

    name = GfuiScrollListGetSelectedElement(scrHandle, selectedScrollList, (void**)&curDrv);
    if (!name) {
	name = GfuiScrollListGetSelectedElement(scrHandle, unselectedScrollList, (void**)&curDrv);
    }
    
    if (name) {
	GfuiLabelSetText(scrHandle, PickDrvNameLabelId, curDrv->name);
	/* search driver infos */
	sprintf(buf, "drivers/%s/%s.xml", curDrv->dname, curDrv->dname);
	robhdle = GfParmReadFile(buf, GFPARM_RMODE_STD);
	if (robhdle != NULL) {
	    sprintf(buf, "%s/%s/%d", ROB_SECT_ROBOTS, ROB_LIST_INDEX, curDrv->index);
	    GfuiLabelSetText(scrHandle, PickDrvCarLabelId, GfParmGetStr(robhdle, buf, ROB_ATTR_CAR, ""));
	    GfuiLabelSetText(scrHandle, PickDrvCategoryLabelId, GfParmGetStr(robhdle, buf, ROB_ATTR_CATEGORY, ""));
	    GfParmReleaseHandle(robhdle);
	}
    }
}

static void
rmSelectDeselect(void * dummy )
{
    char	*name;
    int		src, dst;
    tDrvElt	*curDrv;
    char	*cardllname;
    int		robotIdx;
    int		sel = 0;

    src = unselectedScrollList;
    name = GfuiScrollListExtractSelectedElement(scrHandle, src, (void**)&curDrv);
    if (name) {
	dst = selectedScrollList;
	GfuiScrollListInsertElement(scrHandle, dst, name, 100, (void*)curDrv);
    } else {
	sel = 1;
	src = selectedScrollList;
	name = GfuiScrollListExtractSelectedElement(scrHandle, src, (void**)&curDrv);
	if (name) {
	    dst = unselectedScrollList;
	    GfuiScrollListInsertElement(scrHandle, dst, name, 100, (void*)curDrv);
	} else {
	    return;
	}
    }

    cardllname = GfParmGetStr(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSED, "");
    robotIdx = (int)GfParmGetNum(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, (char*)NULL, 0);
    if (sel) {
	cardllname = GfParmGetStr(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSED, "");
	robotIdx = (int)GfParmGetNum(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, (char*)NULL, 0);
	if ((curDrv->index == robotIdx) && (strcmp(curDrv->dname, cardllname) == 0)) {
	    /* the focused element was deselected select a new one */
	    name = GfuiScrollListGetElement(scrHandle, selectedScrollList, 0, (void**)&curDrv);
	    if (name) {
		GfParmSetStr(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSED, curDrv->dname);
		GfParmSetNum(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, (char*)NULL, curDrv->index);
		GfuiLabelSetText(scrHandle, FocDrvLabelId, curDrv->name);
	    } else {
		GfParmSetStr(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSED, "");
		GfParmSetNum(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, (char*)NULL, 0);
		GfuiLabelSetText(scrHandle, FocDrvLabelId, "");
	    }
	}
    } else {
	if (strlen(cardllname) == 0) {
	    GfParmSetStr(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSED, curDrv->dname);
	    GfParmSetNum(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, (char*)NULL, curDrv->index);
	    GfuiLabelSetText(scrHandle, FocDrvLabelId, curDrv->name);
	}
    }
    rmdsClickOnDriver(NULL);
}

static void
rmdsAddKeys(void)
{
    GfuiAddKey(scrHandle, 27, "Cancel Selection", NULL, rmdsDeactivate);
    GfuiAddSKey(scrHandle, GLUT_KEY_F1, "Help", scrHandle, GfuiHelpScreen);
    GfuiAddSKey(scrHandle, GLUT_KEY_F12, "Screen-Shot", NULL, GfuiScreenShot);
    GfuiAddKey(scrHandle, '-', "Move Up", (void*)-1, rmMove);
    GfuiAddKey(scrHandle, '+', "Move Down", (void*)1, rmMove);
    GfuiAddKey(scrHandle, 13, "Select/Deselect", NULL, rmSelectDeselect);
    GfuiAddKey(scrHandle, 'f', "Set Focus", NULL, rmdsSetFocus);
    
}

/** Interactive Drivers list selection
    @param	vs	Pointer on tRmDrvSelect structure (cast to void)
    @warning	The race manager params are modified but not saved.
 */
void
RmDriversSelect(void *vs)
{
    tModList	*list;
    tModList	*curmod;
    char	dname[256];
    char	*sp;
    char	*cardllname;
    int		i, index;
    tDrvElt	*curDrv;
    int		nCars, robotIdx;

#define B_BASE  380
#define B_HT    30

    ds = (tRmDrvSelect*)vs;

    scrHandle = GfuiScreenCreateEx((float*)NULL, NULL, rmdsActivate, NULL, (tfuiCallback)NULL, 1);
    GfuiScreenAddBgImg(scrHandle, "data/img/splash-qrdrv.png");

    rmdsAddKeys();
    
    GfuiTitleCreate(scrHandle, "Select Drivers", strlen("Select Drivers"));

    GfuiLabelCreate(scrHandle,
		    "Selected",
		    GFUI_FONT_LARGE,
		    120, 400, GFUI_ALIGN_HC_VB,
		    0);

    GfuiLabelCreate(scrHandle,
		    "Not Selected",
		    GFUI_FONT_LARGE,
		    496, 400, GFUI_ALIGN_HC_VB,
		    0);

    selectedScrollList = GfuiScrollListCreate(scrHandle, GFUI_FONT_MEDIUM_C, 20, 80, GFUI_ALIGN_HL_VB,
					      200, 310, GFUI_SB_RIGHT, NULL, rmdsClickOnDriver);
    unselectedScrollList = GfuiScrollListCreate(scrHandle, GFUI_FONT_MEDIUM_C, 396, 80, GFUI_ALIGN_HL_VB,
						200, 310, GFUI_SB_RIGHT, NULL, rmdsClickOnDriver);


    GfuiButtonCreate(scrHandle, "Accept", GFUI_FONT_LARGE, 210, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, rmdsSelect, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiButtonCreate(scrHandle, "Cancel", GFUI_FONT_LARGE, 430, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, rmdsDeactivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiButtonCreate(scrHandle, "Move Up", GFUI_FONT_MEDIUM, 320, B_BASE, 100, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     (void*)-1, rmMove, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiButtonCreate(scrHandle, "Move Down", GFUI_FONT_MEDIUM, 320, B_BASE - B_HT, 100, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     (void*)1, rmMove, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    
    GfuiButtonCreate(scrHandle, "Select", GFUI_FONT_MEDIUM, 320, B_BASE - 2 * B_HT, 100, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     (void*)0, rmSelectDeselect, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    
    GfuiButtonCreate(scrHandle, "Deselect", GFUI_FONT_MEDIUM, 320, B_BASE - 3 * B_HT, 100, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     (void*)1, rmSelectDeselect, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    
    GfuiButtonCreate(scrHandle, "Set Focus", GFUI_FONT_MEDIUM, 320, B_BASE - 4 * B_HT, 100, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, rmdsSetFocus, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    
    list = (tModList *)NULL;
    GfModInfoDir(CAR_IDENT, "drivers", 1, &list);

    curmod = list;
    if (curmod != NULL) {
	do {
	    curmod = curmod->next;
	    for (i = 0; i < MAX_MOD_ITF; i++) {
		if (curmod->modInfo[i].name) {
		    sp = strrchr(curmod->sopath, '/');
		    if (sp == NULL) {
			sp = curmod->sopath;
		    } else {
			sp++;
		    }
		    strcpy(dname, sp);
		    dname[strlen(dname) - strlen(DLLEXT) - 1] = 0; /* cut .so or .dll */
		    curDrv = (tDrvElt*)calloc(1, sizeof(tDrvElt));
		    curDrv->index = curmod->modInfo[i].index;
		    curDrv->dname = strdup(dname);
		    curDrv->name = strdup(curmod->modInfo[i].name);
		    GfRlstAddLast(&DrvList, (tRingList*)curDrv);
		}
	    }
	} while (curmod != list);
    }

    nCars = (int)GfParmGetNum(ds->param, RM_SECT_DRIVERS, RM_ATTR_NDRIVERS, (char*)NULL, 0);
    index = 1;
    for (i = 1; i < nCars+1; i++) {
	sprintf(dname, "%s/%s/%d", RM_SECT_DRIVERS, RM_LIST_DRIVERS, i);
	cardllname = GfParmGetStr(ds->param, dname, RM_ATTR_MODULE, "");
	robotIdx = (int)GfParmGetNum(ds->param, dname, RM_ATTR_IDX, (char*)NULL, 0);

	curDrv = (tDrvElt*)GfRlstGetFirst(&DrvList);
	if (curDrv != NULL) {
	    do {
		if ((curDrv->index == robotIdx) && (strcmp(curDrv->dname, cardllname) == 0)) {
		    GfuiScrollListInsertElement(scrHandle, selectedScrollList, curDrv->name, index, (void*)curDrv);
		    curDrv->sel = index++;
		    break;
		}
	    } while ((curDrv = (tDrvElt*)GfRlstGetNext(&DrvList, (tRingList*)curDrv)) != NULL);
	}
    }

    curDrv = (tDrvElt*)GfRlstGetFirst(&DrvList);
    if (curDrv != NULL) {
	do {
	    if (curDrv->sel == 0) {
		GfuiScrollListInsertElement(scrHandle, unselectedScrollList, curDrv->name, 1000, (void*)curDrv);
	    }
	} while ((curDrv = (tDrvElt*)GfRlstGetNext(&DrvList, (tRingList*)curDrv)) != NULL);
    }

    GfuiLabelCreate(scrHandle, "Focused:", GFUI_FONT_MEDIUM, 320, B_BASE - 5 * B_HT, GFUI_ALIGN_HC_VB, 0);
    cardllname = GfParmGetStr(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSED, "");
    robotIdx = (int)GfParmGetNum(ds->param, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, (char*)NULL, 0);
    curDrv = (tDrvElt*)GfRlstGetFirst(&DrvList);
    if (curDrv != NULL) {
	do {
	    if ((curDrv->index == robotIdx) && (strcmp(curDrv->dname, cardllname) == 0)) {
		break;
	    }
	} while ((curDrv = (tDrvElt*)GfRlstGetNext(&DrvList, (tRingList*)curDrv)) != NULL);
    }
    if (curDrv == NULL) {
	curDrv = (tDrvElt*)GfRlstGetFirst(&DrvList);
    }
    if (curDrv == NULL) {
	FocDrvLabelId = GfuiLabelCreate(scrHandle, "", GFUI_FONT_MEDIUM_C,
					320, B_BASE - 5 * B_HT - GfuiFontHeight(GFUI_FONT_MEDIUM), GFUI_ALIGN_HC_VB, 256);
    } else {
	FocDrvLabelId = GfuiLabelCreate(scrHandle, curDrv->name, GFUI_FONT_MEDIUM_C,
					320, B_BASE - 5 * B_HT - GfuiFontHeight(GFUI_FONT_MEDIUM), GFUI_ALIGN_HC_VB, 256);
    }

    /* Picked Driver Info */
    GfuiLabelCreate(scrHandle, "Driver:", GFUI_FONT_MEDIUM, 320, B_BASE - 7 * B_HT, GFUI_ALIGN_HC_VB, 0);
    PickDrvNameLabelId = GfuiLabelCreateEx(scrHandle, "", aColor, GFUI_FONT_MEDIUM_C,
					   320, B_BASE - 7 * B_HT - GfuiFontHeight(GFUI_FONT_MEDIUM), GFUI_ALIGN_HC_VB, 256);
    GfuiLabelCreate(scrHandle, "Car:", GFUI_FONT_MEDIUM, 320, B_BASE - 8 * B_HT, GFUI_ALIGN_HC_VB, 0);
    PickDrvCarLabelId = GfuiLabelCreateEx(scrHandle, "", aColor, GFUI_FONT_MEDIUM_C,
					  320, B_BASE - 8 * B_HT - GfuiFontHeight(GFUI_FONT_MEDIUM), GFUI_ALIGN_HC_VB, 256);
    GfuiLabelCreate(scrHandle, "Category:", GFUI_FONT_MEDIUM, 320, B_BASE - 9 * B_HT, GFUI_ALIGN_HC_VB, 0);
    PickDrvCategoryLabelId = GfuiLabelCreateEx(scrHandle, "", aColor, GFUI_FONT_MEDIUM_C,
					       320, B_BASE - 9 * B_HT - GfuiFontHeight(GFUI_FONT_MEDIUM), GFUI_ALIGN_HC_VB, 256);
    GfuiMenuDefaultKeysAdd(scrHandle);
    GfuiScreenActivate(scrHandle);
}


static void
rmFreeDrvList(void)
{
    tDrvElt	*cur;

    while ((cur = (tDrvElt*)GfRlstUnlinkFirst(&DrvList)) != NULL) {
	free(cur->name);
	free(cur);
    }
}













/**************************/
/* SELECT A SINGLE DRIVER */
/**************************/

static void
rmds2PrevNext(void *vsel)
{
    tDrvElt	*cur;
    
    if ((int)vsel == 0) {
	cur = (tDrvElt*)GfRlstUnlinkLast(&DrvList);
	if (cur != NULL) {
	    GfRlstAddFirst(&DrvList, (tRingList*)cur);
	}
    } else {
	cur = (tDrvElt*)GfRlstUnlinkFirst(&DrvList);
	if (cur != NULL) {
	    GfRlstAddLast(&DrvList, (tRingList*)cur);
	}
    }
    cur = (tDrvElt*)GfRlstGetFirst(&DrvList);
    if (cur != NULL) {
	GfuiLabelSetText(scrHandle, DrvLabelId, cur->name);
    }
    /* Change the track draw here */
}

static void
rmds2Select(void * /* dummy */)
{
    tDrvElt	*cur;
    char	path[256];

    cur = (tDrvElt*)GfRlstGetFirst(&DrvList);
    if (cur != NULL) {
	sprintf(path, "%s/%s", RM_SECT_DRIVERS, RM_LIST_DRIVERS);
	GfParmListClean(ds->param, path);
	sprintf(path, "%s/%s/1", RM_SECT_DRIVERS, RM_LIST_DRIVERS);
	GfParmSetNum(ds->param, path, RM_ATTR_IDX, (char*)NULL, cur->index);
	GfParmSetStr(ds->param, path, RM_ATTR_MODULE, cur->dname);
	GfParmSetNum(ds->param, RM_SECT_DRIVERS, RM_ATTR_NDRIVERS, (char*)NULL, 1);
    }
    rmdsDeactivate(NULL);
}

static void
rmds2AddKeys(void)
{
    GfuiAddKey(scrHandle, 13, "Select Driver", NULL, rmds2Select);
    GfuiAddKey(scrHandle, 27, "Cancel Selection", NULL, rmdsDeactivate);
    GfuiAddSKey(scrHandle, GLUT_KEY_LEFT, "Previous Driver", (void*)0, rmds2PrevNext);
    GfuiAddSKey(scrHandle, GLUT_KEY_RIGHT, "Next Driver", (void*)1, rmds2PrevNext);
    GfuiAddSKey(scrHandle, GLUT_KEY_F12, "Screen-Shot", NULL, GfuiScreenShot);
    
}

/** Interactive driver selection
    @param	vs	Pointer on a tRmDrvSelect structure (cast to void *)
    @warning	The race manager's parameters are updated but not saved.
 */
void
RmDriverSelect(void *vs)
{
    tModList	*list;
    tModList	*curmod;
    char	dname[256];
    char	path[256];
    char	*sp;
    char	*cardllname;
    int		i;
    tDrvElt	*curDrv;
    int		robotIdx;
    
    ds = (tRmDrvSelect*)vs;

    list = (tModList *)NULL;
    GfModInfoDir(CAR_IDENT, "drivers", 1, &list);

    curmod = list;
    if (curmod != NULL) {
	do {
	    curmod = curmod->next;
	    for (i = 0; i < MAX_MOD_ITF; i++) {
		if (curmod->modInfo[i].name) {
		    sp = strrchr(curmod->sopath, '/');
		    if (sp == NULL) {
			sp = curmod->sopath;
		    } else {
			sp++;
		    }
		    strcpy(dname, sp);
		    dname[strlen(dname) - strlen(DLLEXT) - 1] = 0; /* cut .so or .dll */
		    curDrv = (tDrvElt*)calloc(1, sizeof(tDrvElt));
		    curDrv->index = curmod->modInfo[i].index;
		    curDrv->dname = strdup(dname);
		    curDrv->name = strdup(curmod->modInfo[i].name);
		    GfRlstAddLast(&DrvList, (tRingList*)curDrv);
		}
	    }
	} while (curmod != list);
    }

    sprintf(path, "%s/%s/1", RM_SECT_DRIVERS, RM_LIST_DRIVERS);
    cardllname = GfParmGetStr(ds->param, path, RM_ATTR_MODULE, "");
    robotIdx = (int)GfParmGetNum(ds->param, path, RM_ATTR_IDX, (char*)NULL, 0);

    curDrv = (tDrvElt*)GfRlstGetFirst(&DrvList);
    if (curDrv != NULL) {
	do {
	    if ((curDrv->index == robotIdx) && (strcmp(curDrv->dname, cardllname) == 0)) {
		GfRlstSeekElt(&DrvList, (tRingList*)curDrv);
		break;
	    }
	} while ((curDrv = (tDrvElt*)GfRlstGetNext(&DrvList, (tRingList*)curDrv)) != NULL);
    }
    
    scrHandle = GfuiScreenCreateEx((float*)NULL, NULL, rmdsActivate, NULL, (tfuiCallback)NULL, 1);
    GfuiScreenAddBgImg(scrHandle, "data/img/splash-qrdrv.png");

    rmds2AddKeys();

    GfuiTitleCreate(scrHandle, "Select Driver", strlen("Select Driver"));

    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-left.png",
		       "data/img/arrow-left.png",
		       "data/img/arrow-left.png",
		       "data/img/arrow-left-pushed.png",
		       80, 400, GFUI_ALIGN_HC_VB, 0,
		       (void*)0, rmds2PrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    
    curDrv = (tDrvElt*)GfRlstGetFirst(&DrvList);
    DrvLabelId = GfuiLabelCreate(scrHandle,
				   curDrv->name,
				   GFUI_FONT_LARGE,
				   320, 400, GFUI_ALIGN_HC_VB,
				   32);

    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right-pushed.png",
		       540, 400, GFUI_ALIGN_HC_VB, 0,
		       (void*)1, rmds2PrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiMenuBackQuitButtonCreate(scrHandle, "Select", "Select the driver", NULL, rmds2Select);
    
    GfuiScreenActivate(scrHandle);
}
