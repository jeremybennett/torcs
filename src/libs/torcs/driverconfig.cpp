/***************************************************************************

    file                 : driverconfig.cpp
    created              : Wed Apr 26 20:05:12 CEST 2000
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgf.h>
#include <track.h>
#include <robot.h>
#include "driverconfig.h"

#define NO_DRV	"--- empty ---"
#define dllname   "human"
#define DRV_FILE  "drivers/human/human.xml"
#define PREF_FILE "drivers/human/preferences.xml"

#define	HM_SECT_PREF	"Preferences"
#define HM_LIST_DRV	"Drivers"
#define HM_ATT_TRANS	"transmission"
#define HM_ATT_ABS	"ABS on"
#define HM_ATT_ASR	"ASR on"
#define HM_ATT_NBPITS	"programmed pit stops"
#define HM_VAL_AUTO	"auto"
#define HM_VAL_MANUAL	"manual"

static char *level_str[] = { ROB_VAL_ROOKIE, ROB_VAL_AMATEUR, ROB_VAL_SEMI_PRO, ROB_VAL_PRO };

static char buf[1024];

static int	scrollList;
static void	*scrHandle = NULL;
static void	*prevHandle = NULL;

static void	*PrefHdle = NULL;

static int NameEditId;
static int CarEditId;
static int CatEditId;
static int RaceNumEditId;
static int TransEditId;
static int PitsEditId;
static int SkillId;

#define NB_DRV	10

typedef struct tInfo
{
    char	*name;
    char	*dispname;
} tInfo;

struct tCarInfo;

typedef struct tCatInfo
{
    struct tCatInfo	*next;
    struct tCatInfo	*prev;
    tInfo		info;
    tRingListHead	CarsInfoList;
} tCatInfo;

typedef struct tCarInfo
{
    struct tCarInfo	*next;
    struct tCarInfo	*prev;
    tInfo		info;
    tCatInfo		*cat;
} tCarInfo;

typedef struct PlayerInfo
{
    tInfo	info;
    tCarInfo	*carinfo;
    int		racenumber;
    char	*transmission;
    int		nbpitstops;
    float	color[4];
    int		skill_level;
} tPlayerInfo;

#define _Name		info.name
#define _DispName	info.dispname

static tPlayerInfo PlayersInfo[NB_DRV];

static tRingListHead CatsInfoList = {(tRingList*)&CatsInfoList, (tRingList*)&CatsInfoList};

static tPlayerInfo	*curPlayer;

static void
refreshEditVal(void)
{
    char	buf[32];

    if (curPlayer == NULL) {
	GfuiEditboxSetString(scrHandle, NameEditId, "");
	GfuiEnable(scrHandle, NameEditId, GFUI_DISABLE);

	GfuiEditboxSetString(scrHandle, RaceNumEditId, "");
	GfuiEnable(scrHandle, RaceNumEditId, GFUI_DISABLE);

	GfuiLabelSetText(scrHandle, CarEditId, "");
	GfuiEnable(scrHandle, CarEditId, GFUI_DISABLE);
	
	GfuiLabelSetText(scrHandle, CatEditId, "");

	GfuiEditboxSetString(scrHandle, RaceNumEditId, "");
	GfuiEnable(scrHandle, RaceNumEditId, GFUI_DISABLE);

	GfuiLabelSetText(scrHandle, TransEditId, "");

	GfuiEditboxSetString(scrHandle, PitsEditId, "");
	GfuiEnable(scrHandle, PitsEditId, GFUI_DISABLE);

	GfuiLabelSetText(scrHandle, SkillId, "");
    } else {
	GfuiEditboxSetString(scrHandle, NameEditId, curPlayer->_DispName);
	GfuiEnable(scrHandle, NameEditId, GFUI_ENABLE);

	sprintf(buf, "%d", curPlayer->racenumber);
	GfuiEditboxSetString(scrHandle, RaceNumEditId, buf);
	GfuiEnable(scrHandle, RaceNumEditId, GFUI_ENABLE);

	GfuiLabelSetText(scrHandle, CarEditId, curPlayer->carinfo->_DispName);
	GfuiEnable(scrHandle, CarEditId, GFUI_ENABLE);

	GfuiLabelSetText(scrHandle, CatEditId, curPlayer->carinfo->cat->_DispName);

	sprintf(buf, "%d", curPlayer->racenumber);
	GfuiEditboxSetString(scrHandle, RaceNumEditId, buf);
	GfuiEnable(scrHandle, RaceNumEditId, GFUI_ENABLE);

	GfuiLabelSetText(scrHandle, TransEditId, curPlayer->transmission);

	sprintf(buf, "%d", curPlayer->nbpitstops);
	GfuiEditboxSetString(scrHandle, PitsEditId, buf);
	GfuiEnable(scrHandle, PitsEditId, GFUI_ENABLE);

	GfuiLabelSetText(scrHandle, SkillId, level_str[curPlayer->skill_level]);
    }
}

static void
onSelect(void *Dummy)
{
    GfuiScrollListGetSelectedElement(scrHandle, scrollList, (void**)&curPlayer);
    refreshEditVal();
}

static void
GenCarsInfo(void)
{
    tCarInfo	*curCar;
    tCatInfo	*curCat;
    tCatInfo	*tmpCat;
    tFList	*files;
    tFList	*curFile;
    char	buf[256];
    void	*carparam;
    char	*str;
    void	*hdle;

    /* Empty the lists */
    while ((curCat = (tCatInfo*)GfRlstUnlinkFirst(&CatsInfoList)) != NULL) {
	while ((curCar = (tCarInfo*)GfRlstUnlinkFirst(&(curCat->CarsInfoList))) != NULL) {
	    free(curCar->_Name);
	    free(curCar);
	}
	free(curCat->_Name);
	free(curCat);
    }

    files = GfDirGetList("categories");
    curFile = files;
    if ((curFile != NULL) && (curFile->name[0] != '.')) {
	do {
	    curFile = curFile->next;
	    curCat = (tCatInfo*)calloc(1, sizeof(tCatInfo));
	    GfRlstInit(&(curCat->CarsInfoList));
	    str = strchr(curFile->name, '.');
	    *str = '\0';
	    curCat->_Name = strdup(curFile->name);
	    sprintf(buf, "categories/%s.xml", curFile->name);
	    hdle = GfParmReadFile(buf, GFPARM_RMODE_STD);
	    if (!hdle) {
		continue;
	    }
	    curCat->_DispName = GfParmGetName(hdle);
	    GfRlstAddLast(&CatsInfoList, (tRingList*)curCat);
	} while (curFile != files);
    }
    GfDirFreeList(files, NULL);
    
    files = GfDirGetList("cars");
    curFile = files;
    if ((curFile != NULL) && (curFile->name[0] != '.')) {
	do {
	    curFile = curFile->next;
	    curCar = (tCarInfo*)calloc(1, sizeof(tCarInfo));
	    curCar->_Name = strdup(curFile->name);
	    sprintf(buf, "cars/%s/%s.xml", curFile->name, curFile->name);
	    carparam = GfParmReadFile(buf, GFPARM_RMODE_STD);
	    if (!carparam) {
		continue;
	    }
	    curCar->_DispName = GfParmGetName(carparam);
	    /* search for the category */
	    str = GfParmGetStr(carparam, SECT_CAR, PRM_CATEGORY, "");
	    curCat = (tCatInfo*)GfRlstGetFirst(&CatsInfoList);
	    if (curCat != NULL) {
		do {
		    if (strcmp(curCat->_Name, str) == 0) {
			break;
		    }
		} while ((curCat = (tCatInfo*)GfRlstGetNext(&CatsInfoList, (tRingList*)curCat)) != NULL);
	    }
	    curCar->cat = curCat;
	    GfRlstAddLast(&(curCat->CarsInfoList), (tRingList*)curCar);
	} while (curFile != files);
    }
    GfDirFreeList(files, NULL);

    /* Remove the empty categories */
    curCat = (tCatInfo*)GfRlstGetFirst(&CatsInfoList);
    do {
	curCar = (tCarInfo*)GfRlstGetFirst(&(curCat->CarsInfoList));
	tmpCat = curCat;
	curCat = (tCatInfo*)GfRlstGetNext(&CatsInfoList, (tRingList*)curCat);
	if (curCar == NULL) {
	    GfOut("Removing empty category %s\n", tmpCat->_DispName);
	    GfRlstUnlinkElt((tRingList*)tmpCat);
	    free(tmpCat->_Name);
	    free(tmpCat);
	}
    } while (curCat  != NULL);
    
}

static void
UpdtScrollList(void)
{
    char	*str;
    int		i;
    void	*tmp;

    /* free the previous scrollist elements */
    while((str = GfuiScrollListExtractElement(scrHandle, scrollList, 0, (void**)&tmp)) != NULL) {
    }
    for (i = 0; i < NB_DRV; i++) {
	GfuiScrollListInsertElement(scrHandle, scrollList, PlayersInfo[i]._DispName, i, (void*)&(PlayersInfo[i]));
    }
}

static void
DeletePlayer(void *dummy)
{
    if (curPlayer) {
	curPlayer->_DispName = strdup(NO_DRV);
	refreshEditVal();
	UpdtScrollList();
    }
}

static int
GenDrvList(void)
{
    void	*drvinfo;
    char	sstring[256];
    int		i;
    int		j;
    char 	*driver;
    tCarInfo	*car;
    tCatInfo	*cat;
    char	*str;
    int		found;

    sprintf(buf, "%s%s", LocalDir, DRV_FILE);
    drvinfo = GfParmReadFile(buf, GFPARM_RMODE_REREAD);
    if (drvinfo == NULL) {
	return -1;
    }
    for (i = 0; i < NB_DRV; i++) {
	sprintf(sstring, "%s/%s/%d", ROB_SECT_ROBOTS, ROB_LIST_INDEX, i+1);
	driver = GfParmGetStr(drvinfo, sstring, ROB_ATTR_NAME, "");
	if (strlen(driver) == 0) {
	    PlayersInfo[i]._DispName = strdup(NO_DRV);
	    PlayersInfo[i]._Name = dllname;
	    PlayersInfo[i].carinfo = (tCarInfo*)GfRlstGetFirst(&(((tCatInfo*)GfRlstGetFirst(&CatsInfoList))->CarsInfoList));
	    PlayersInfo[i].racenumber = 0;
	    PlayersInfo[i].color[0] = 1.0;
	    PlayersInfo[i].color[1] = 1.0;
	    PlayersInfo[i].color[2] = 0.5;
	    PlayersInfo[i].color[3] = 1.0;
	} else {
	    PlayersInfo[i]._DispName = strdup(driver);
	    PlayersInfo[i]._Name = dllname;
	    PlayersInfo[i].skill_level = 0;
	    str = GfParmGetStr(drvinfo, sstring, ROB_ATTR_LEVEL, level_str[0]);
	    for(j = 0; j < (int)(sizeof(level_str)/sizeof(char*)); j++) {
		if (strcmp(level_str[j], str) == 0) {
		    PlayersInfo[i].skill_level = j;
		    break;
		}
	    }
	    str = GfParmGetStr(drvinfo, sstring, ROB_ATTR_CAR, "");
	    found = 0;
	    cat = (tCatInfo*)GfRlstGetFirst(&CatsInfoList);
	    PlayersInfo[i].carinfo = (tCarInfo*)GfRlstGetFirst(&(cat->CarsInfoList));
	    do {
		car = (tCarInfo*)GfRlstGetFirst(&(cat->CarsInfoList));
		if (car != NULL) {
		    do {
			if (strcmp(car->_Name, str) == 0) {
			    found = 1;
			    PlayersInfo[i].carinfo = car;
			}
		    } while (!found && ((car = (tCarInfo*)GfRlstGetNext(&(cat->CarsInfoList), (tRingList*)car)) != NULL));
		}
	    } while (!found && ((cat = (tCatInfo*)GfRlstGetNext(&CatsInfoList, (tRingList*)cat)) != NULL));
	    PlayersInfo[i].racenumber  = (int)GfParmGetNum(drvinfo, sstring, ROB_ATTR_RACENUM, (char*)NULL, 0);
	    PlayersInfo[i].color[0]    = (float)GfParmGetNum(drvinfo, sstring, ROB_ATTR_RED, (char*)NULL, 1.0);
	    PlayersInfo[i].color[1]    = (float)GfParmGetNum(drvinfo, sstring, ROB_ATTR_GREEN, (char*)NULL, 1.0);;
	    PlayersInfo[i].color[2]    = (float)GfParmGetNum(drvinfo, sstring, ROB_ATTR_BLUE, (char*)NULL, 0.5);;	    
	    PlayersInfo[i].color[3]    = 1.0;
	}
    }
    UpdtScrollList();

    sprintf(buf, "%s%s", LocalDir, PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_REREAD);
    if (PrefHdle == NULL) {
	return -1;
    }
    for (i = 0; i < NB_DRV; i++) {
	sprintf(sstring, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, i+1);
	str = GfParmGetStr(PrefHdle, sstring, HM_ATT_TRANS, HM_VAL_AUTO);
	if (strcmp(str, HM_VAL_AUTO) == 0) {
	    PlayersInfo[i].transmission = HM_VAL_AUTO;
	} else {
	    PlayersInfo[i].transmission = HM_VAL_MANUAL;
	}
	PlayersInfo[i].nbpitstops = (int)GfParmGetNum(PrefHdle, sstring, HM_ATT_NBPITS, (char*)NULL, 0);
    }
    return 0;
}

static void
SaveDrvList(void *dummy)
{
    void	*drvinfo;
    char	str[32];
    int		i;

    sprintf(buf, "%s%s", LocalDir, DRV_FILE);
    drvinfo = GfParmReadFile(buf, GFPARM_RMODE_STD);
    if (drvinfo == NULL) {
	return;
    }
    for (i = 0; i < NB_DRV; i++) {
	sprintf(str, "%s/%s/%d", ROB_SECT_ROBOTS, ROB_LIST_INDEX, i+1);
	if (strcmp(PlayersInfo[i]._DispName, NO_DRV) == 0) {
	    GfParmSetStr(drvinfo, str, ROB_ATTR_NAME, "");
	} else {
	    GfParmSetStr(drvinfo, str, ROB_ATTR_NAME, PlayersInfo[i]._DispName);
	    GfParmSetStr(drvinfo, str, ROB_ATTR_CAR, PlayersInfo[i].carinfo->_Name);
	    GfParmSetNum(drvinfo, str, ROB_ATTR_RACENUM, (char*)NULL, PlayersInfo[i].racenumber);
	    GfParmSetNum(drvinfo, str, ROB_ATTR_RED, (char*)NULL, PlayersInfo[i].color[0]);
	    GfParmSetNum(drvinfo, str, ROB_ATTR_GREEN, (char*)NULL, PlayersInfo[i].color[1]);
	    GfParmSetNum(drvinfo, str, ROB_ATTR_BLUE, (char*)NULL, PlayersInfo[i].color[2]);
	    GfParmSetStr(drvinfo, str, ROB_ATTR_TYPE, ROB_VAL_HUMAN);
	    GfParmSetStr(drvinfo, str, ROB_ATTR_LEVEL, level_str[PlayersInfo[i].skill_level]);
	}
    }
    GfParmWriteFile(NULL, drvinfo, dllname, GFPARM_PARAMETER, "../../config/params.dtd");

    sprintf(buf, "%s%s", LocalDir, PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    for (i = 0; i < NB_DRV; i++) {
	sprintf(str, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, i+1);
	GfParmSetStr(PrefHdle, str, HM_ATT_TRANS, PlayersInfo[i].transmission);
	GfParmSetNum(PrefHdle, str, HM_ATT_NBPITS, (char*)NULL, (tdble)PlayersInfo[i].nbpitstops);
    }
    GfParmWriteFile(NULL, PrefHdle, "preferences", GFPARM_PARAMETER, "../../config/params.dtd");
    GfParmReleaseHandle(PrefHdle);
    PrefHdle = NULL;
    GfuiScreenActivate(prevHandle);
    return;
}


static void
ChangeName(void *dummy)
{
    char	*val;

    val = GfuiEditboxGetString(scrHandle, NameEditId);
    if (curPlayer != NULL) {
	if (curPlayer->_DispName) {
	    free(curPlayer->_DispName);
	}
	if (strlen(val)) {
	    curPlayer->_DispName = strdup(val);
	} else {
	    curPlayer->_DispName = strdup(NO_DRV);
	}
    }
    UpdtScrollList();
}

static void
ChangeNum(void *dummy)
{
    char	*val;
    char	buf[32];
    
    val = GfuiEditboxGetString(scrHandle, RaceNumEditId);
    if (curPlayer != NULL) {
	curPlayer->racenumber = (int)strtol(val, (char **)NULL, 0);
	sprintf(buf, "%d", curPlayer->racenumber);
	GfuiEditboxSetString(scrHandle, RaceNumEditId, buf);
    }
}

static void
ChangePits(void *dummy)
{
    char	*val;
    char	buf[32];
    
    val = GfuiEditboxGetString(scrHandle, PitsEditId);
    if (curPlayer != NULL) {    
	curPlayer->nbpitstops = (int)strtol(val, (char **)NULL, 0);
	sprintf(buf, "%d", curPlayer->nbpitstops);
	GfuiEditboxSetString(scrHandle, PitsEditId, buf);
    }
}

static void
ChangeCar(void *vp)
{
    tCarInfo	*car;
    tCatInfo	*cat;
    
    if (curPlayer == NULL) {
	return;
    }
    cat = curPlayer->carinfo->cat;
    if (vp == 0) {
	car = (tCarInfo*)GfRlstGetPrev(&(cat->CarsInfoList), (tRingList*)curPlayer->carinfo);
	if (car == NULL) {
	    car = (tCarInfo*)GfRlstGetLast(&(cat->CarsInfoList));
	}
    } else {
	car = (tCarInfo*)GfRlstGetNext(&(cat->CarsInfoList), (tRingList*)curPlayer->carinfo);
	if (car == NULL) {
	    car = (tCarInfo*)GfRlstGetFirst(&(cat->CarsInfoList));
	}
    }
    curPlayer->carinfo = car;
    refreshEditVal();
}

static void
ChangeCat(void *vp)
{
    tCarInfo	*car;
    tCatInfo	*cat;
    
    if (curPlayer == NULL) {
	return;
    }
    cat = curPlayer->carinfo->cat;
    if (vp == 0) {
	do {
	    cat = (tCatInfo*)GfRlstGetPrev(&CatsInfoList, (tRingList*)cat);
	    if (cat == NULL) {
		cat = (tCatInfo*)GfRlstGetLast(&CatsInfoList);
	    }
	    car = (tCarInfo*)GfRlstGetFirst(&(cat->CarsInfoList));
	} while (car == NULL);	/* skip empty categories */
    } else {
	do {
	    cat = (tCatInfo*)GfRlstGetNext(&CatsInfoList, (tRingList*)cat);
	    if (cat == NULL) {
		cat = (tCatInfo*)GfRlstGetFirst(&CatsInfoList);
	    }
	    car = (tCarInfo*)GfRlstGetFirst(&(cat->CarsInfoList));
	} while (car == NULL);	/* skip empty categories */
    }
    curPlayer->carinfo = car;
    refreshEditVal();
}

static void
ChangeLevel(void *vp)
{
    if (curPlayer == NULL) {
	return;
    }
    if (vp == 0) {
	curPlayer->skill_level--;
	if (curPlayer->skill_level < 0) {
	    curPlayer->skill_level = sizeof(level_str)/sizeof(char*) - 1;
	}
    } else {
	curPlayer->skill_level++;
	if (curPlayer->skill_level == sizeof(level_str)/sizeof(char*)) {
	    curPlayer->skill_level = 0;
	}
    }
    refreshEditVal();
}

static void
ChangeTrans(void *dummy)
{
    if (curPlayer == NULL) {
	return;
    }
    if (curPlayer->transmission != HM_VAL_AUTO) {
	curPlayer->transmission = HM_VAL_AUTO;
    } else {
	curPlayer->transmission = HM_VAL_MANUAL;
    }
    refreshEditVal();
}

void *
TorcsDriverMenuInit(void *prevMenu)
{
    int		x, y, x2, dy;
    
    /* screen already created */
    if (scrHandle) {
	GenCarsInfo();
	GenDrvList();
	return scrHandle;
    }
    prevHandle = prevMenu;
    
    scrHandle = GfuiScreenCreate();
    GfuiTitleCreate(scrHandle, "Player Configuration", strlen("Player Configuration"));

    GfuiScreenAddBgImg(scrHandle, "data/img/splash-qrdrv.png");

    GfuiLabelCreate(scrHandle, "Players", GFUI_FONT_LARGE, 496, 400, GFUI_ALIGN_HC_VB, 0);

    scrollList = GfuiScrollListCreate(scrHandle, GFUI_FONT_MEDIUM_C,
				      396, 390 - NB_DRV * GfuiFontHeight(GFUI_FONT_MEDIUM_C),
				      GFUI_ALIGN_HL_VB, 200, NB_DRV * GfuiFontHeight(GFUI_FONT_MEDIUM_C), GFUI_SB_NONE,
				      NULL, onSelect);

    GfuiButtonCreate(scrHandle, "Delete", GFUI_FONT_LARGE, 496, 340 - NB_DRV * GfuiFontHeight(GFUI_FONT_MEDIUM_C),
		     140, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, DeletePlayer, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GenCarsInfo();
    if (GenDrvList()) {
	GfuiScreenRelease(scrHandle);
	return NULL;
    }

    x = 20;
    x2 = 170;
    y = 370;
    dy = 30;

    GfuiLabelCreate(scrHandle, "Name:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    NameEditId = GfuiEditboxCreate(scrHandle, "", GFUI_FONT_MEDIUM_C,
				    x2+10, y, 180, 16, NULL, (tfuiCallback)NULL, ChangeName);
    y -= dy;
    GfuiLabelCreate(scrHandle, "Category:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
		       "data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
		       x2, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)0, ChangeCat,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);	    
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
		       "data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
		       x2 + 170, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)1, ChangeCat,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    CatEditId = GfuiLabelCreate(scrHandle, "", GFUI_FONT_MEDIUM_C, x2 + 30, y, GFUI_ALIGN_HL_VB, 32);
    y -= dy;
    GfuiLabelCreate(scrHandle, "Car:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
		       "data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
		       x2, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)0, ChangeCar,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);	    
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
		       "data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
		       x2 + 170, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)1, ChangeCar,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    CarEditId = GfuiLabelCreate(scrHandle, "", GFUI_FONT_MEDIUM_C, x2 + 30, y, GFUI_ALIGN_HL_VB, 32);
    y -= dy;
    GfuiLabelCreate(scrHandle, "Race Number:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    RaceNumEditId = GfuiEditboxCreate(scrHandle, "0", GFUI_FONT_MEDIUM_C,
				      x2+10, y, 0, 2, NULL, (tfuiCallback)NULL, ChangeNum);
    y -= dy;
    GfuiLabelCreate(scrHandle, "Transmission:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
		       "data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
		       x2, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)0, ChangeTrans,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);	    
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
		       "data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
		       x2 + 170, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)1, ChangeTrans,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    TransEditId = GfuiLabelCreate(scrHandle, "", GFUI_FONT_MEDIUM_C, x2 + 30, y, GFUI_ALIGN_HL_VB, 32);
    y -= dy;
    GfuiLabelCreate(scrHandle, "Pit Stops:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    PitsEditId = GfuiEditboxCreate(scrHandle, "", GFUI_FONT_MEDIUM_C,
				   x2+10, y, 0, 2, NULL, (tfuiCallback)NULL, ChangePits);
    y -= dy;
    GfuiLabelCreate(scrHandle, "Level:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
		       "data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
		       x2, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)0, ChangeLevel,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);	    
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
		       "data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
		       x2 + 170, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)1, ChangeLevel,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    SkillId = GfuiLabelCreate(scrHandle, "", GFUI_FONT_MEDIUM_C, x2 + 30, y, GFUI_ALIGN_HL_VB, 32);
    
    GfuiButtonCreate(scrHandle, "Accept", GFUI_FONT_LARGE, 210, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
     NULL, SaveDrvList, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiButtonCreate(scrHandle, "Cancel", GFUI_FONT_LARGE, 430, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
     prevMenu, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiAddKey(scrHandle, 13, "Select Track", NULL, SaveDrvList, NULL);
    GfuiAddKey(scrHandle, 27, "Cancel Selection", prevMenu, GfuiScreenActivate, NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_F12, "Screen-Shot", NULL, GfuiScreenShot, NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_LEFT, "Previous Car", (void*)0, ChangeCar, NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_RIGHT, "Next Car", (void*)1, ChangeCar, NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_UP, "Previous Car Category", (void*)0, ChangeCat, NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_DOWN, "Next Car Category", (void*)1, ChangeCat, NULL);

    refreshEditVal();
    return scrHandle;
}

