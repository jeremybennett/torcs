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
#include <tgfclient.h>
#include <track.h>
#include <robot.h>
#include <playerpref.h>
#include <controlconfig.h>

#include "driverconfig.h"

#define NO_DRV	"--- empty ---"
#define dllname   "human"

static char *level_str[] = { ROB_VAL_ROOKIE, ROB_VAL_AMATEUR, ROB_VAL_SEMI_PRO, ROB_VAL_PRO };
static const int nbLevels = sizeof(level_str) / sizeof(level_str[0]);

static char buf[1024];

static float LabelColor[] = {1.0, 0.0, 1.0, 1.0};

static int	scrollList;
static void	*scrHandle = NULL;
static void	*prevHandle = NULL;

static void	*PrefHdle = NULL;

static int NameEditId;
static int CarEditId;
static int CatEditId;
static int RaceNumEditId;
static int GearChangeEditId;
static int PitsEditId;
static int SkillEditId;
static int AutoReverseEditId;
static int AutoReverseLeftId;
static int AutoReverseRightId;
static int AutoReverseLabelId;

/* Struct to define a generic ("internal name / id", "displayable name") pair */
typedef struct tInfo
{
    char	*name;
    char	*dispname;
} tInfo;

#define _Name		info.name
#define _DispName	info.dispname

/* Car names and car categories double-linked lists structs */
struct tCarInfo;
struct tCatInfo;

GF_TAILQ_HEAD(CarsInfoHead, struct tCarInfo);
GF_TAILQ_HEAD(CatsInfoHead, struct tCatInfo);

typedef struct tCatInfo
{
    struct tCatInfo	*next;
    struct tCatInfo	*prev;
    tInfo		info;
    tCarsInfoHead	CarsInfoList;
    GF_TAILQ_ENTRY(struct tCatInfo) link;
} tCatInfo;

typedef struct tCarInfo
{
    struct tCarInfo	*next;
    struct tCarInfo	*prev;
    tInfo		info;
    tCatInfo		*cat;
    GF_TAILQ_ENTRY(struct tCarInfo) link;
} tCarInfo;

/* Player info struct */
typedef struct PlayerInfo
{
    tInfo	info;
    tCarInfo	*carinfo;
    int		racenumber;
    char	*gearchange;
    int		nbpitstops;
    float	color[4];
    int		skilllevel;
    int		autoreverse;
} tPlayerInfo;


/* Number of human drivers (= players) slots in the array */
#define NB_DRV	10

/* The human driver (= player) info array */
static tPlayerInfo PlayersInfo[NB_DRV];

/* The car category / name double-linked lists */
static tCatsInfoHead CatsInfoList;

/* The currently selected player */
static tPlayerInfo	*curPlayer;

/* A bool to ("yes", "no") conversion table */
static char *Yn[] = {HM_VAL_YES, HM_VAL_NO};


/* Load screen editable fields with relevant values :
   - all empty if no player selected,
   - from selected player current settings otherwise 
*/
static void
refreshEditVal(void)
{
    int autoRevVisible = GFUI_INVISIBLE;

    if (curPlayer == NULL) {

	GfuiEditboxSetString(scrHandle, NameEditId, "");
	GfuiEnable(scrHandle, NameEditId, GFUI_DISABLE);

	GfuiEditboxSetString(scrHandle, RaceNumEditId, "");
	GfuiEnable(scrHandle, RaceNumEditId, GFUI_DISABLE);

	GfuiLabelSetText(scrHandle, CarEditId, "");
	GfuiEnable(scrHandle, CarEditId, GFUI_DISABLE);
	
	GfuiLabelSetText(scrHandle, CatEditId, "");
	GfuiEnable(scrHandle, CatEditId, GFUI_DISABLE);

	GfuiLabelSetText(scrHandle, GearChangeEditId, "");
	GfuiEnable(scrHandle, GearChangeEditId, GFUI_DISABLE);

	GfuiEditboxSetString(scrHandle, PitsEditId, "");
	GfuiEnable(scrHandle, PitsEditId, GFUI_DISABLE);

	GfuiLabelSetText(scrHandle, SkillEditId, "");
	GfuiEnable(scrHandle, SkillEditId, GFUI_DISABLE);

	GfuiLabelSetText(scrHandle, AutoReverseEditId, "");
	GfuiEnable(scrHandle, AutoReverseEditId, GFUI_DISABLE);

    } else {

	GfuiEditboxSetString(scrHandle, NameEditId, curPlayer->_DispName);
	GfuiEnable(scrHandle, NameEditId, GFUI_ENABLE);

	sprintf(buf, "%d", curPlayer->racenumber);
	GfuiEditboxSetString(scrHandle, RaceNumEditId, buf);
	GfuiEnable(scrHandle, RaceNumEditId, GFUI_ENABLE);

	GfuiLabelSetText(scrHandle, CarEditId, curPlayer->carinfo->_DispName);
	GfuiEnable(scrHandle, CarEditId, GFUI_ENABLE);

	GfuiLabelSetText(scrHandle, CatEditId, curPlayer->carinfo->cat->_DispName);
	GfuiEnable(scrHandle, CatEditId, GFUI_ENABLE);

	sprintf(buf, "%d", curPlayer->racenumber);
	GfuiEditboxSetString(scrHandle, RaceNumEditId, buf);
	GfuiEnable(scrHandle, RaceNumEditId, GFUI_ENABLE);

	GfuiLabelSetText(scrHandle, GearChangeEditId, curPlayer->gearchange);
	GfuiEnable(scrHandle, GearChangeEditId, GFUI_ENABLE);

	sprintf(buf, "%d", curPlayer->nbpitstops);
	GfuiEditboxSetString(scrHandle, PitsEditId, buf);
	GfuiEnable(scrHandle, PitsEditId, GFUI_ENABLE);

	GfuiLabelSetText(scrHandle, SkillEditId, level_str[curPlayer->skilllevel]);
	GfuiEnable(scrHandle, AutoReverseEditId, GFUI_ENABLE);

	GfuiLabelSetText(scrHandle, AutoReverseEditId, Yn[curPlayer->autoreverse]);
	GfuiEnable(scrHandle, AutoReverseEditId, GFUI_ENABLE);

	if (curPlayer->gearchange == HM_VAL_AUTO)
	    autoRevVisible = GFUI_VISIBLE;
    }

    GfuiVisibilitySet(scrHandle, AutoReverseLabelId, autoRevVisible);
    GfuiVisibilitySet(scrHandle, AutoReverseLeftId, autoRevVisible);
    GfuiVisibilitySet(scrHandle, AutoReverseEditId, autoRevVisible);
    GfuiVisibilitySet(scrHandle, AutoReverseRightId, autoRevVisible);
}

static void
onSelect(void * /* Dummy */)
{
    GfuiScrollListGetSelectedElement(scrHandle, scrollList, (void**)&curPlayer);
    refreshEditVal();
}

/* Load the car category info / car info double-linked lists
   from installed category dirs and car description xml files */
static void
GenCarsInfo(void)
{
	tCarInfo	*curCar;
	tCatInfo	*curCat;
	tCatInfo	*tmpCat;
	tFList	*files;
	tFList	*curFile;
	void	*carparam;
	char	*str;
	void	*hdle;

	/* Empty the lists */
	while ((curCat = GF_TAILQ_FIRST(&CatsInfoList)) != NULL) {
		GF_TAILQ_REMOVE(&CatsInfoList, curCat, link);
		while ((curCar = GF_TAILQ_FIRST(&(curCat->CarsInfoList))) != NULL) {
			GF_TAILQ_REMOVE(&(curCat->CarsInfoList), curCar, link);
			free(curCar->_Name);
			free(curCar);
		}
		free(curCat->_Name);
		free(curCat);
	}

	/* Load the category list */
	files = GfDirGetList("categories");
	curFile = files;
	if ((curFile != NULL) && (curFile->name[0] != '.')) {
		do {
			curFile = curFile->next;
			curCat = (tCatInfo*)calloc(1, sizeof(tCatInfo));
			GF_TAILQ_INIT(&(curCat->CarsInfoList));
			str = strchr(curFile->name, '.');
			*str = '\0';
			curCat->_Name = strdup(curFile->name);
			sprintf(buf, "categories/%s.xml", curFile->name);
			hdle = GfParmReadFile(buf, GFPARM_RMODE_STD);
			if (!hdle) {
			continue;
			}
			curCat->_DispName = GfParmGetName(hdle);
			GF_TAILQ_INSERT_TAIL(&CatsInfoList, curCat, link);
		} while (curFile != files);
	}
	GfDirFreeList(files, NULL, true, true);
    
    /* Load the car info list */
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
	    curCat = GF_TAILQ_FIRST(&CatsInfoList);
	    if (curCat != NULL) {
		do {
		    if (strcmp(curCat->_Name, str) == 0) {
			break;
		    }
		} while ((curCat = GF_TAILQ_NEXT(curCat, link)) != NULL);
	    }
	    curCar->cat = curCat;
	    GF_TAILQ_INSERT_TAIL(&(curCat->CarsInfoList), curCar, link);
	} while (curFile != files);
    }
    GfDirFreeList(files, NULL, true, true);

    /* Remove the empty categories */
    curCat = GF_TAILQ_FIRST(&CatsInfoList);
    do {
	curCar = GF_TAILQ_FIRST(&(curCat->CarsInfoList));
	tmpCat = curCat;
	curCat = GF_TAILQ_NEXT(curCat, link);
	if (curCar == NULL) {
	    GfOut("Removing empty category %s\n", tmpCat->_DispName);
	    GF_TAILQ_REMOVE(&CatsInfoList, tmpCat, link);
	    free(tmpCat->_Name);
	    free(tmpCat);
	}
    } while (curCat  != NULL);
    
}

/* Update players scroll-list from PlayersInfo array */
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

/* Remove the selected player from the list, and update players scroll-list and all editable fields*/
static void
DeletePlayer(void * /* dummy */)
{
    if (curPlayer) {
	curPlayer->_DispName = strdup(NO_DRV);
	refreshEditVal();
	UpdtScrollList();
    }
}

/* Activate the control config screen if a player is selected */
static void
ConfControls(void * /* dummy */ )
{
    int index;
    
    if (curPlayer) {
	index = curPlayer - PlayersInfo + 1;
	GfuiScreenActivate(TorcsControlMenuInit(scrHandle, index, curPlayer->gearchange));
    }
}

/* Load human driver (=player) info list (PlayersInfo) from preferences and human drivers files ;
   load associated scroll list */
static int
GenDrvList(void)
{
	void *drvinfo;
	char sstring[256];
	int i;
	int j;
	char *driver;
	tCarInfo *car;
	tCatInfo *cat;
	char *str;
	int found;

	sprintf(buf, "%s%s", GetLocalDir(), HM_DRV_FILE);
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
			PlayersInfo[i].carinfo = GF_TAILQ_FIRST(&((GF_TAILQ_FIRST(&CatsInfoList))->CarsInfoList));
			PlayersInfo[i].racenumber = 0;
			PlayersInfo[i].color[0] = 1.0;
			PlayersInfo[i].color[1] = 1.0;
			PlayersInfo[i].color[2] = 0.5;
			PlayersInfo[i].color[3] = 1.0;
		} else {
			PlayersInfo[i]._DispName = strdup(driver);
			PlayersInfo[i]._Name = dllname;
			PlayersInfo[i].skilllevel = 0;
			str = GfParmGetStr(drvinfo, sstring, ROB_ATTR_LEVEL, level_str[0]);
			for(j = 0; j < nbLevels; j++) {
				if (strcmp(level_str[j], str) == 0) {
					PlayersInfo[i].skilllevel = j;
					break;
				}
			}
			str = GfParmGetStr(drvinfo, sstring, ROB_ATTR_CAR, "");
			found = 0;
			cat = GF_TAILQ_FIRST(&CatsInfoList);
			PlayersInfo[i].carinfo = GF_TAILQ_FIRST(&(cat->CarsInfoList));
			do {
				car = GF_TAILQ_FIRST(&(cat->CarsInfoList));
				if (car != NULL) {
					do {
						if (strcmp(car->_Name, str) == 0) {
							found = 1;
							PlayersInfo[i].carinfo = car;
						}
					} while (!found && ((car = GF_TAILQ_NEXT(car, link)) != NULL));
				}
			} while (!found && ((cat = GF_TAILQ_NEXT(cat, link)) != NULL));
			PlayersInfo[i].racenumber  = (int)GfParmGetNum(drvinfo, sstring, ROB_ATTR_RACENUM, (char*)NULL, 0);
			PlayersInfo[i].color[0]    = (float)GfParmGetNum(drvinfo, sstring, ROB_ATTR_RED, (char*)NULL, 1.0);
			PlayersInfo[i].color[1]    = (float)GfParmGetNum(drvinfo, sstring, ROB_ATTR_GREEN, (char*)NULL, 1.0);;
			PlayersInfo[i].color[2]    = (float)GfParmGetNum(drvinfo, sstring, ROB_ATTR_BLUE, (char*)NULL, 0.5);;
			PlayersInfo[i].color[3]    = 1.0;
		}
    }
    UpdtScrollList();

    sprintf(buf, "%s%s", GetLocalDir(), HM_PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_REREAD);
    if (PrefHdle == NULL) {
		GfParmReleaseHandle(drvinfo);
		return -1;
    }

    for (i = 0; i < NB_DRV; i++) {
		sprintf(sstring, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, i+1);
		str = GfParmGetStr(PrefHdle, sstring, HM_ATT_TRANS, HM_VAL_AUTO);
		if (strcmp(str, HM_VAL_AUTO) == 0) {
			PlayersInfo[i].gearchange = HM_VAL_AUTO;
		} else if (strcmp(str, HM_VAL_GRID) == 0) {
			PlayersInfo[i].gearchange = HM_VAL_GRID;
		} else {
			PlayersInfo[i].gearchange = HM_VAL_SEQ;
		} /* Note: Deprecated "manual" value (after R1.3.0) smoothly converted to "sequential" (backward compatibility) */
		PlayersInfo[i].nbpitstops = (int)GfParmGetNum(PrefHdle, sstring, HM_ATT_NBPITS, (char*)NULL, 0);
		if (!strcmp(GfParmGetStr(PrefHdle, sstring, HM_ATT_AUTOREVERSE, Yn[0]), Yn[0])) {
			PlayersInfo[i].autoreverse = 0;
		} else {
			PlayersInfo[i].autoreverse = 1;
		}
		if (!strcmp(GfParmGetStr(PrefHdle, sstring, HM_ATT_AUTOREVERSE, Yn[0]), Yn[0])) {
			PlayersInfo[i].autoreverse = 0;
		} else {
			PlayersInfo[i].autoreverse = 1;
		}
    }

    GfParmReleaseHandle(PrefHdle);
    GfParmReleaseHandle(drvinfo);

    return 0;
}

/* Save players info (from PlayersInfo array) to the human drivers and preferences XML files */
static void
SaveDrvList(void * /* dummy */)
{
    void	*drvinfo;
    char	str[32];
    int		i;

    sprintf(buf, "%s%s", GetLocalDir(), HM_DRV_FILE);
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
	    GfParmSetStr(drvinfo, str, ROB_ATTR_LEVEL, level_str[PlayersInfo[i].skilllevel]);
	}
    }
    GfParmWriteFile(NULL, drvinfo, dllname);

    sprintf(buf, "%s%s", GetLocalDir(), HM_PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    for (i = 0; i < NB_DRV; i++) {
	sprintf(str, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, i+1);
	GfParmSetStr(PrefHdle, str, HM_ATT_TRANS, PlayersInfo[i].gearchange);
	GfParmSetNum(PrefHdle, str, HM_ATT_NBPITS, (char*)NULL, (tdble)PlayersInfo[i].nbpitstops);
	GfParmSetStr(PrefHdle, str, HM_ATT_AUTOREVERSE, Yn[PlayersInfo[i].autoreverse]);

	/* Allow neutral gear in sequential mode if no reverse gear command defined */
	if (PlayersInfo[i].gearchange == HM_VAL_SEQ
	    && !strcmp(GfParmGetStr(PrefHdle, str, HM_ATT_GEAR_R, "-"), "-"))
	  GfParmSetStr(PrefHdle, str, HM_ATT_SEQSHFT_ALLOW_NEUTRAL, HM_VAL_YES);
	else
	  GfParmSetStr(PrefHdle, str, HM_ATT_SEQSHFT_ALLOW_NEUTRAL, HM_VAL_NO);

	/* Release gear lever goes neutral in grid mode if no neutral gear command defined */
	if (PlayersInfo[i].gearchange == HM_VAL_GRID
	    && !strcmp(GfParmGetStr(PrefHdle, str, HM_ATT_GEAR_N, "-"), "-"))
	  GfParmSetStr(PrefHdle, str, HM_ATT_REL_BUT_NEUTRAL, HM_VAL_YES);
	else
	  GfParmSetStr(PrefHdle, str, HM_ATT_REL_BUT_NEUTRAL, HM_VAL_NO);

    }
    GfParmWriteFile(NULL, PrefHdle, "preferences");
    GfParmReleaseHandle(PrefHdle);
    PrefHdle = NULL;
    GfuiScreenActivate(prevHandle);
    return;
}


static void
ChangeName(void * /* dummy */)
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
ChangeNum(void * /* dummy */)
{
    char	*val;
    
    val = GfuiEditboxGetString(scrHandle, RaceNumEditId);
    if (curPlayer != NULL) {
	curPlayer->racenumber = (int)strtol(val, (char **)NULL, 0);
	sprintf(buf, "%d", curPlayer->racenumber);
	GfuiEditboxSetString(scrHandle, RaceNumEditId, buf);
    }
}

static void
ChangePits(void * /* dummy */)
{
    char	*val;
    
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
	car = GF_TAILQ_PREV(curPlayer->carinfo, CarsInfoHead, link);
	if (car == NULL) {
	    car = GF_TAILQ_LAST(&(cat->CarsInfoList), CarsInfoHead);
	}
    } else {
	car = GF_TAILQ_NEXT(curPlayer->carinfo, link);
	if (car == NULL) {
	    car = GF_TAILQ_FIRST(&(cat->CarsInfoList));
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
	    cat = GF_TAILQ_PREV(cat, CatsInfoHead, link);
	    if (cat == NULL) {
		cat = GF_TAILQ_LAST(&CatsInfoList, CatsInfoHead);
	    }
	    car = GF_TAILQ_FIRST(&(cat->CarsInfoList));
	} while (car == NULL);	/* skip empty categories */
    } else {
	do {
	    cat = GF_TAILQ_NEXT(cat, link);
	    if (cat == NULL) {
		cat = GF_TAILQ_FIRST(&CatsInfoList);
	    }
	    car = GF_TAILQ_FIRST(&(cat->CarsInfoList));
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
	curPlayer->skilllevel--;
	if (curPlayer->skilllevel < 0) {
	    curPlayer->skilllevel = nbLevels - 1;
	}
    } else {
	curPlayer->skilllevel++;
	if (curPlayer->skilllevel == nbLevels) {
	    curPlayer->skilllevel = 0;
	}
    }
    refreshEditVal();
}

static void
ChangeReverse(void *vdelta)
{
    long delta = (long)vdelta;
    
    if (curPlayer == NULL) {
	return;
    }
    curPlayer->autoreverse += (int)delta;
    if (curPlayer->autoreverse < 0) {
	curPlayer->autoreverse = 1;
    } else if (curPlayer->autoreverse > 1) {
	curPlayer->autoreverse = 0;
    }

    refreshEditVal();
}


/* Gear change mode change callback */
static void
ChangeGearChange(void *vp)
{
    if (curPlayer == NULL) {
	return;
    }
    if (vp == 0) {
	if (curPlayer->gearchange == HM_VAL_AUTO) {
	    curPlayer->gearchange = HM_VAL_GRID;
	} else if (curPlayer->gearchange == HM_VAL_SEQ) {
	    curPlayer->gearchange = HM_VAL_AUTO;
	}
	else {
	    curPlayer->gearchange = HM_VAL_SEQ;
	}
    } else {
	if (curPlayer->gearchange == HM_VAL_AUTO) {
	    curPlayer->gearchange = HM_VAL_SEQ;
	} else if (curPlayer->gearchange == HM_VAL_SEQ) {
	    curPlayer->gearchange = HM_VAL_GRID;
	}
	else {
	    curPlayer->gearchange = HM_VAL_AUTO;
	}
    }

    if (curPlayer->gearchange == HM_VAL_AUTO) {
      GfuiVisibilitySet(scrHandle, AutoReverseLabelId, GFUI_VISIBLE);
      GfuiVisibilitySet(scrHandle, AutoReverseLeftId, GFUI_VISIBLE);
      GfuiVisibilitySet(scrHandle, AutoReverseEditId, GFUI_VISIBLE);
      GfuiVisibilitySet(scrHandle, AutoReverseRightId, GFUI_VISIBLE);
    } else {
      GfuiVisibilitySet(scrHandle, AutoReverseLabelId, GFUI_INVISIBLE);
      GfuiVisibilitySet(scrHandle, AutoReverseLeftId, GFUI_INVISIBLE);
      GfuiVisibilitySet(scrHandle, AutoReverseEditId, GFUI_INVISIBLE);
      GfuiVisibilitySet(scrHandle, AutoReverseRightId, GFUI_INVISIBLE);
    }
    

    refreshEditVal();
}

void *
TorcsDriverMenuInit(void *prevMenu)
{
    int		x, y, x2, x3, x4, dy;
    static int	firstTime = 1;

    if (firstTime) {
	firstTime = 0;
	GF_TAILQ_INIT(&CatsInfoList);
    }
    
    /* Screen already created : just update from human preferences and drivers params files */
    if (scrHandle) {
	GenCarsInfo();
	GenDrvList();
	return scrHandle;
    }

    prevHandle = prevMenu;

    scrHandle = GfuiScreenCreate();

    /* Title */
    GfuiTitleCreate(scrHandle, "Player Configuration", 0);

    /* Background image */
    GfuiScreenAddBgImg(scrHandle, "data/img/splash-qrdrv.png");

    /* Players label and associated scroll list just below */
    GfuiLabelCreate(scrHandle, "Players", GFUI_FONT_LARGE, 496, 400, GFUI_ALIGN_HC_VB, 0);

    scrollList = GfuiScrollListCreate(scrHandle, GFUI_FONT_MEDIUM_C,
				      396, 390 - NB_DRV * GfuiFontHeight(GFUI_FONT_MEDIUM_C),
				      GFUI_ALIGN_HL_VB, 200, NB_DRV * GfuiFontHeight(GFUI_FONT_MEDIUM_C), GFUI_SB_NONE,
				      NULL, onSelect);

    /* Delete player button */
    GfuiButtonCreate(scrHandle, "Delete", GFUI_FONT_LARGE, 496, 340 - NB_DRV * GfuiFontHeight(GFUI_FONT_MEDIUM_C),
		     140, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, DeletePlayer, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    /* Access to control screen button*/
    GfuiButtonCreate(scrHandle, "Controls", GFUI_FONT_LARGE, 496, 340 - NB_DRV * GfuiFontHeight(GFUI_FONT_MEDIUM_C) - 30,
		     140, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, ConfControls, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    /* Load cars and players infos, and return if something wrong with players */
    GenCarsInfo();
    if (GenDrvList()) {
	GfuiScreenRelease(scrHandle);
	return NULL;
    }

    /* Screen coordinates and deltas for labels, buttons, ... */
    x = 20;
    x2 = 170;
    x3 = x2 + 100;
    x4 = x2 + 200;
    y = 370;
    dy = 30;

    /* Player name label and associated editbox */
    GfuiLabelCreate(scrHandle, "Name:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    NameEditId = GfuiEditboxCreate(scrHandle, "", GFUI_FONT_MEDIUM_C,
				    x2+10, y, 180, 16, NULL, (tfuiCallback)NULL, ChangeName);

    /* Player skill level and associated "combobox" (left arrow, label, right arrow) */
    y -= dy;
    GfuiLabelCreate(scrHandle, "Level:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
		       "data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
		       x2, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)0, ChangeLevel,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);	    
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
		       "data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
		       x4, y, GFUI_ALIGN_HR_VB, 1,
		       (void*)1, ChangeLevel,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    SkillEditId = GfuiLabelCreate(scrHandle, "", GFUI_FONT_MEDIUM_C, x3, y, GFUI_ALIGN_HC_VB, 32);
    GfuiLabelSetColor(scrHandle, SkillEditId, LabelColor);

    /* Race number and associated editbox */
    y -= dy;
    GfuiLabelCreate(scrHandle, "Race Number:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    RaceNumEditId = GfuiEditboxCreate(scrHandle, "0", GFUI_FONT_MEDIUM_C,
				      x2+10, y, 0, 2, NULL, (tfuiCallback)NULL, ChangeNum);

    /* Number of pit stops and associated editbox */
    y -= dy;
    GfuiLabelCreate(scrHandle, "Pit Stops:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    PitsEditId = GfuiEditboxCreate(scrHandle, "", GFUI_FONT_MEDIUM_C,
				   x2+10, y, 0, 2, NULL, (tfuiCallback)NULL, ChangePits);

    /* Gear changing mode and associated "combobox" (left arrow, label, right arrow) */
    y -= dy;
    GfuiLabelCreate(scrHandle, "Gear change:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
		       "data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
		       x2, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)0, ChangeGearChange,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);	    
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
		       "data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
		       x4, y, GFUI_ALIGN_HR_VB, 1,
		       (void*)1, ChangeGearChange,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    GearChangeEditId = GfuiLabelCreate(scrHandle, "", GFUI_FONT_MEDIUM_C, x3, y, GFUI_ALIGN_HC_VB, 32);
    GfuiLabelSetColor(scrHandle, GearChangeEditId, LabelColor);

    /* Gear changing auto-reverse flag and associated "combobox" (left arrow, label, right arrow) */
    y -= dy;
    AutoReverseLabelId =
      GfuiLabelCreate(scrHandle, "Auto Reverse:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    AutoReverseLeftId =
      GfuiGrButtonCreate(scrHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
			 "data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
			 x2, y, GFUI_ALIGN_HL_VB, 1,
			 (void*)-1, ChangeReverse,
			 NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);	    
    AutoReverseRightId =
      GfuiGrButtonCreate(scrHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
		       "data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
		       x4, y, GFUI_ALIGN_HR_VB, 1,
		       (void*)1, ChangeReverse,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    AutoReverseEditId = 
      GfuiLabelCreate(scrHandle, "", GFUI_FONT_MEDIUM_C, x3, y, GFUI_ALIGN_HC_VB, 32);
    GfuiLabelSetColor(scrHandle, AutoReverseEditId, LabelColor);
    
    /* Car category and associated "combobox" (left arrow, label, right arrow) */
    y -= dy;
    y -= dy;
    GfuiLabelCreate(scrHandle, "Category:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
		       "data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
		       x2, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)0, ChangeCat,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);	    
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
		       "data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
		       x4, y, GFUI_ALIGN_HR_VB, 1,
		       (void*)1, ChangeCat,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    CatEditId = GfuiLabelCreate(scrHandle, "", GFUI_FONT_MEDIUM_C, x3, y, GFUI_ALIGN_HC_VB, 32);
    GfuiLabelSetColor(scrHandle, CatEditId, LabelColor);

    /* Car name and associated "combobox" (left arrow, label, right arrow) */
    y -= dy;
    GfuiLabelCreate(scrHandle, "Car:", GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
		       "data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
		       x2, y, GFUI_ALIGN_HL_VB, 1,
		       (void*)0, ChangeCar,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);	    
    GfuiGrButtonCreate(scrHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
		       "data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
		       x4, y, GFUI_ALIGN_HR_VB, 1,
		       (void*)1, ChangeCar,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    CarEditId = GfuiLabelCreate(scrHandle, "", GFUI_FONT_MEDIUM_C, x3, y, GFUI_ALIGN_HC_VB, 32);
    GfuiLabelSetColor(scrHandle, CarEditId, LabelColor);

    /* Screen validation button */
    GfuiButtonCreate(scrHandle, "Accept", GFUI_FONT_LARGE, 210, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
     NULL, SaveDrvList, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    /* Screen cancelation button */
    GfuiButtonCreate(scrHandle, "Cancel", GFUI_FONT_LARGE, 430, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
     prevMenu, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    /* Keybord shortcuts */
    GfuiAddKey(scrHandle, 13 /* Return */, "Save Drivers", NULL, SaveDrvList, NULL);
    GfuiAddKey(scrHandle, 27 /* Escape */, "Cancel Selection", prevMenu, GfuiScreenActivate, NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_F12, "Screen-Shot", NULL, GfuiScreenShot, NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_LEFT, "Previous Car", (void*)0, ChangeCar, NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_RIGHT, "Next Car", (void*)1, ChangeCar, NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_UP, "Previous Car Category", (void*)0, ChangeCat, NULL);
    GfuiAddSKey(scrHandle, GLUT_KEY_DOWN, "Next Car Category", (void*)1, ChangeCat, NULL);

    /* Load and display editable fields values */
    refreshEditVal();

    return scrHandle;
}

