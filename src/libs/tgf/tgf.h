/***************************************************************************
                    tgf.h -- Interface file for The Gaming Framework                                    
                             -------------------                                         
    created              : Fri Aug 13 22:32:14 CEST 1999
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
    	The Gaming Framework API.
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/
/**
    @defgroup	module	Dynamic Modules
    This is the interface to load/unload the shared libraries (or DLLs).
    <br>Two modes are allowed, the access by filename, of the access by entire directory.
    <br>When the directory mode is used, the filenames are not known by advance, this
    <br>allow more flexibility at runtime.
    <br>
    <br>The generic information can be retrieved, without keeping the DLL loaded.
    <br>
    <br>The gfid parameter is use to differentiate the modules using different includes.
    <br>This functionality is not used yet.
    <br>
    <br>This API is not used for shared libraries linked staticaly at compilation time.
*/
/**
    @defgroup	gui	GUI Management.
    This is an interface to manage menus.

*/
/**
    @defgroup	img	Image Management.
    Load and store png images with easy interface.
*/
/**
    @defgroup	dir	Directory Management.
    This is used for directory manipulation.
*/
/**
    @defgroup	params Parameters file management.
    The parameters are stored in XML files and accessed only with this API.
    <br>The parameters are structured in:
    <br><b>section</b> - containing a familly of parameters on the same topic.
    <br><b>list</b> - containing <b>elements</b>
    of <b>numerical attributes</b> and <b>string attributes</b>.
*/
/**
    @defgroup	screen	Screen management.
*/
/** 
    @defgroup	ringlist	Ring Lists Management.
    The ring lists are linked lists without end, the tail is linked to the head.
    <br>The list pointer is on the tail, so the access to the head is list->next.
    <br>The first field of the elements is always next.
 */
/**
    @defgroup	trace	Trace management.
    Allow the trace in the file <tt>trace.txt</tt>
*/


#ifndef __TGF__H__
#define __TGF__H__

#include <stdio.h>
#ifndef WIN32
#include <sys/param.h>
#endif /* WIN32 */
#include <stdlib.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include <osspec.h>
#include <queue.h>

/* typedef double tdble; */
typedef float tdble;

#ifndef MAX
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#endif

#ifndef MIN
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#endif


/*********************************
 * Interface For Dynamic Modules *
 *********************************/

/** initialisation of the function table 
    @see	ModInfo
*/
typedef int (*tfModPrivInit)(int index, void *);

/** Maximum number of interface in one DLL
    @see	ModList
 */
#define MAX_MOD_ITF 10

/** Module information structure  */
typedef struct ModInfo {
    /** name of the module (short) (NULL if no module) */
    char		*name;
    /** description of the module (can be long) */
    char		*desc;
    /** init function */
    tfModPrivInit	fctInit;
    /** supported framework version */
    unsigned int	gfId;
    /** index if multiple interface in one dll */
    int			index;
    /** priority if needed */
    int			prio;
} tModInfo;

/* module init function interface */
typedef int (*tfModInfo)(tModInfo *);	/* first function called in the module */

/* module shutdown function interface */
typedef int (*tfModShut)(void);	/* last function called in the module */


/** list of module interfaces */
typedef struct ModList {
    /** module info list for this dll */
    tModInfo		modInfo[MAX_MOD_ITF];
    /** handle of loaded module */
#ifdef _WIN32
    HMODULE		handle;
#else
    void		*handle;
#endif
    /** path name of file */
    char		*sopath;
    /** next module in list */
    struct ModList	*next;
} tModList;


extern int GfModLoad(unsigned int gfid, char *dllname, tModList **modlist);
extern int GfModLoadDir(unsigned int gfid, char *dir, tModList **modlist);
extern int GfModUnloadList(tModList **modlist);
extern int GfModInfo(unsigned int gfid, char *filename, tModList **modlist);
extern int GfModInfoDir(unsigned int gfid, char *dir, int level, tModList **modlist);
extern int GfModFreeInfoList(tModList **modlist);

/************************
 * Directory management *
 ************************/

/** List of (DLL) files for a Directory 
    @see	GfDirGetList
*/
typedef struct FList 
{
    /** Next entry */
    struct FList	*next;
    /** Previous entry */
    struct FList	*prev;
    /** File name */
    char		*name;
    /** Name to display on screen */
    char		*dispName;
    /** User data */
    void		*userData;
} tFList;

extern tFList *GfDirGetList(char *dir);
/** Function to call for releasing the user data associated with file entry */
typedef void (*tfDirfreeUserData)(void*);
extern void GfDirFreeList(tFList *list, tfDirfreeUserData freeUserData);


/**********************************
 *  Interface For Parameter Files *
 **********************************/

/*
 *	This set of function is used to store and retrieve
 *	values in parameters files.
 */


/* parameters file type */
#define GFPARM_PARAMETER	0
#define GFPARM_TEMPLATE		1
#define GFPARM_PARAM_STR	"param"
#define GFPARM_TEMPL_STR	"template"

/* parameters access mode */
#define GFPARM_MODIFIABLE	1
#define GFPARM_WRITABLE		2

/* parameter file read */
#define GFPARM_RMODE_STD	0x01	/* if handle already openned return it */
#define GFPARM_RMODE_REREAD	0x02	/* reread the parameters from file and release the previous ones */
#define GFPARM_RMODE_CREAT	0x04	/* Create the file if doesn't exist */

extern void *GfParmReadFile(const char *file, int mode);
/* parameter file write */
extern int GfParmWriteFile(const char *file, void* handle, char *name, int type, const char *dtd);

extern char *GfParmGetName(void *handle);

/* get string parameter value */
extern char *GfParmGetStr(void *handle, char *path, char *key, char *deflt);
/* get string parameter value */
extern char *GfParmGetCurStr(void *handle, char *path, char *key, char *deflt);
/* set string parameter value */
extern int GfParmSetStr(void *handle, char *path, char *key, char *val);
/* set string parameter value */
extern int GfParmSetCurStr(void *handle, char *path, char *key, char *val);

/* get num parameter value */
extern tdble GfParmGetNum(void *handle, char *path, char *key, char *unit, tdble deflt);
/* get num parameter value */
extern tdble GfParmGetCurNum(void *handle, char *path, char *key, char *unit, tdble deflt);
/* set num parameter value */
extern int GfParmSetNum(void *handle, char *path, char *key, char *unit, tdble val);
/* set num parameter value */
extern int GfParmSetCurNum(void *handle, char *path, char *key, char *unit, tdble val);


/* clean all the parameters of a set */
extern int GfParmClean(void *handle);
/* clean the parms and release the handle without updating the file */
extern int GfParmReleaseHandle(void *handle);

/* Convert a value in "units" into SI */
extern tdble GfParmUnit2SI(char *unit, tdble val);
/* convert a value in SI to "units" */
extern tdble GfParmSI2Unit(char *unit, tdble val);

/* compare and merge different handles */
extern int GfParmCheckHandle(void *ref, void *tgt);
#define GFPARM_MMODE_SRC	1 /* use ref and modify existing parameters with tgt */
#define GFPARM_MMODE_DST	2 /* use tgt and verify ref parameters */
#define GFPARM_MMODE_RELSRC	4 /* release ref after the merge */
#define GFPARM_MMODE_RELDST	8 /* release tgt after the merge */
extern void *GfParmMergeHandles(void *ref, void *tgt, int mode);
extern int GfParmGetNumBoundaries(void *handle, char *path, char *key, tdble *min, tdble *max);


extern int GfParmGetEltNb(void *handle, char *path);
extern int GfParmListSeekFirst(void *handle, char *path);
extern int GfParmListSeekNext(void *handle, char *path);
extern char *GfParmListGetCurEltName(void *handle, char *path);
extern int GfParmListClean(void *handle, char *path);

/******************** 
 * Screen Interface *
 ********************/

#define GFSCR_CONF_FILE	"config/screen.xml"
#define GFSCR_SECT_PROP	"Screen Properties"
#define GFSCR_ATT_X	"x"
#define GFSCR_ATT_Y	"y"
#define GFSCR_ATT_WIN_X	"window width"
#define GFSCR_ATT_WIN_Y	"window height"
#define GFSCR_ATT_FSCR	"fullscreen"
#define GFSCR_VAL_YES	"yes"
#define GFSCR_VAL_NO	"no"
#define GFSCR_ATT_GAMMA	"gamma"

extern unsigned char *GfImgReadPng(const char *filename, int *widthp, int *heightp, float gamma);
extern int GfImgWritePng(unsigned char *img, const char *filename, int width, int height);
extern void GfImgFreeTex(GLuint tex);
extern GLuint GfImgReadTex(char *filename);

extern void GfScrInit(int argc, char *argv[]);
extern void *GfScrMenuInit(void *precMenu);
extern char *GfTime2Str(tdble sec, int sgn);
extern void GfScrGetSize(int *ScrW, int *ScrH, int *ViewW, int *ViewH);


/*****************************
 * GUI interface (low-level) *
 *****************************/

/* Widget type */
#define GFUI_LABEL	0
#define GFUI_BUTTON	1
#define GFUI_GRBUTTON	2
#define GFUI_SCROLLIST	3
#define GFUI_SCROLLBAR	4
#define GFUI_EDITBOX	5

/* Alignment */
#define GFUI_ALIGN_HL_VB	0x00
#define GFUI_ALIGN_HL_VC	0x01
#define GFUI_ALIGN_HL_VT	0x02
#define GFUI_ALIGN_HC_VB	0x10
#define GFUI_ALIGN_HC_VC	0x11
#define GFUI_ALIGN_HC_VT	0x12
#define GFUI_ALIGN_HR_VB	0x20
#define GFUI_ALIGN_HR_VC	0x21
#define GFUI_ALIGN_HR_VT	0x22

/* Mouse action */
#define GFUI_MOUSE_UP	0
#define GFUI_MOUSE_DOWN	1

/* Scroll Bar position */
#define GFUI_SB_NONE	0
#define GFUI_SB_RIGHT	1
#define GFUI_SB_LEFT	2
#define GFUI_SB_TOP	3
#define GFUI_SB_BOTTOM	4

/* Scroll bar orientation */
#define GFUI_HORI_SCROLLBAR	0
#define GFUI_VERT_SCROLLBAR	1

/** Scroll bar call-back information */
typedef struct ScrollBarInfo
{
    /** Current scroll bar position */
    int		pos;
    /** Associated user data */
    void	*userData;
} tScrollBarInfo;

typedef void (*tfuiCallback)(void * /* userdata */);
typedef void (*tfuiSBCallback)(tScrollBarInfo *);

/* GLUT Callback functions                  */
/* should be called explicitely if          */
/* the corresponding GLUT Func is overriden */
/* after a call to GfuiActivateScreen       */
extern void GfuiDisplay(void);
extern void GfuiDisplayNothing(void);
extern void GfuiIdle(void);

/* Screen management */
extern void *GfuiScreenCreate(void);
extern void *GfuiScreenCreateEx(float *bgColor, 
				void *userDataOnActivate, tfuiCallback onActivate, 
				void *userDataOnDeactivate, tfuiCallback onDeactivate, 
				int mouseAllowed);
extern void GfuiScreenRelease(void *screen);
extern void GfuiScreenActivate(void *screen);
extern void GfuiScreenDeactivate(void);
extern void GfuiAddKey(void *scr, unsigned char key, char *descr, void *userData, tfuiCallback onKeyPressed);
extern void GfuiRegisterKey(unsigned char key, char *descr, void *userData, tfuiCallback onKeyPressed);
extern void GfuiAddSKey(void *scr, int key, char *descr, void *userData, tfuiCallback onKeyPressed);
extern void GfuiHelpScreen(void *prevScreen);
extern void GfuiScreenShot(void *notused);
extern void GfuiScreenAddBgImg(void *scr, char *filename);

/* mouse */
typedef struct MouseInfo
{
    int	X;
    int	Y;
    int	button[3];
} tMouseInfo;

extern tMouseInfo *GfuiMouseInfo(void);

/* all widgets */
extern void GfuiVisiblilitySet(void *scr, int id, int visible);
#define	GFUI_DISABLE	1
#define	GFUI_ENABLE	0
extern int GfuiEnable(void *scr, int id, int flag);
extern void GfuiUnSelectCurrent(void);

/* labels */
#define GFUI_FONT_BIG		0
#define GFUI_FONT_LARGE		1
#define GFUI_FONT_MEDIUM	2
#define GFUI_FONT_SMALL		3
#define GFUI_FONT_BIG_C		4
#define GFUI_FONT_LARGE_C	5
#define GFUI_FONT_MEDIUM_C	6
#define GFUI_FONT_SMALL_C	7
#define GFUI_FONT_DIGIT		8
extern int GfuiLabelCreate(void *scr, char *text, 
			int font, int x, int y, int align, int maxlen);
extern int GfuiLabelCreateEx(void *scr, char *text, float *fgColor, int font, int x, int y, int align, int maxlen);

extern int GfuiTipCreate(void *scr, char *text, int maxlen);
extern int GfuiTitleCreate(void *scr, char *text, int maxlen);

extern void GfuiLabelSetText(void *scr, int id, char *text);
extern void GfuiLabelSetColor(void *scr, int id, float *color);

extern void GfuiPrintString(char *text, float *fgColor, int font, int x, int y, int align);
extern int  GfuiFontHeight(int font);
extern int  GfuiFontWidth(int font, char *text);


/* buttons */
#define GFUI_BTNSZ	300
extern int GfuiButtonCreate(void *scr, char *text, int font,
			    int x, int y, int width, int align, int mouse,
			    void *userDataOnPush, tfuiCallback onPush, 
			    void *userDataOnFocus, tfuiCallback onFocus, tfuiCallback onFocusLost);
extern int GfuiButtonStateCreate(void *scr, char *text, int font, int x, int y, int width, int align, int mouse,
				 void *userDataOnPush, tfuiCallback onPush, 
				 void *userDataOnFocus, tfuiCallback onFocus, tfuiCallback onFocusLost);
extern int GfuiGrButtonCreate(void *scr, char *disabled, char *enabled, char *focused, char *pushed,
			      int x, int y, int align, int mouse,
			      void *userDataOnPush, tfuiCallback onPush, 
			      void *userDataOnFocus, tfuiCallback onFocus, tfuiCallback onFocusLost);

extern void GfuiButtonSetText(void *scr, int id, char *text);
extern int GfuiButtonGetFocused(void);

/* Edit Box */
extern int GfuiEditboxCreate(void *scr, char *text, int font, int x, int y, int width, int maxlen,
			     void *userDataOnFocus, tfuiCallback onFocus, tfuiCallback onFocusLost);
extern int GfuiEditboxGetFocused(void);
extern char *GfuiEditboxGetString(void *scr, int id);
extern void GfuiEditboxSetString(void *scr, int id, char *text);

/* Scrolling lists */
extern int GfuiScrollListCreate(void *scr, int font, int x, int y, int align,
				int width, int height, int scrollbar, void *userDataOnSelect, tfuiCallback onSelect);
extern int GfuiScrollListInsertElement(void *scr, int Id, char *element, int index, void *userData);
extern int GfuiScrollListMoveSelectedElement(void *scr, int Id, int delta);
extern char *GfuiScrollListExtractSelectedElement(void *scr, int Id, void **userData);
extern char *GfuiScrollListExtractElement(void *scr, int Id, int index, void **userData);
extern char *GfuiScrollListGetSelectedElement(void *scr, int Id, void **userData);
extern char *GfuiScrollListGetElement(void *scr, int Id, int index, void **userData);

/* scroll bars */
extern int GfuiScrollBarCreate(void *scr, int x, int y, int align, int width, int orientation,
			       int min, int max, int len, int start, 
			       void *userData, tfuiSBCallback onScroll);
extern void GfuiScrollBarPosSet(void *scr, int id, int min, int max, int len, int start);
extern int GfuiScrollBarPosGet(void *scr, int id);

/* Images */
extern int GfuiStaticImageCreate(void *scr, int x, int y, int w, int h, char *name);
extern void GfuiStaticImageSet(void *scr, int id, char *name);

/*****************************
 * Menu Management Interface *
 *****************************/

extern void *GfuiMenuScreenCreate(char *title);
extern void  GfuiMenuDefaultKeysAdd(void *scr);
extern int   GfuiMenuButtonCreate(void *menu, char *text, char *tip, void *userdata, tfuiCallback onpush);
extern int   GfuiMenuBackQuitButtonCreate(void *menu, char *text, char *tip, void *userdata, tfuiCallback onpush);

#define GFSCR_SECT_MENUCOL	"Menu Colors"
#define GFSCR_LIST_COLORS	"colors"
#define GFSCR_ELT_BGCOLOR	"background"
#define GFSCR_ELT_TITLECOLOR	"title"
#define GFSCR_ELT_BGBTNFOCUS	"background focused button"
#define GFSCR_ELT_BGBTNCLICK	"background pushed button"
#define GFSCR_ELT_BGBTNENABLED	"background enabled button"
#define GFSCR_ELT_BGBTNDISABLED	"background disabled button"
#define GFSCR_ELT_BTNFOCUS	"focused button"
#define GFSCR_ELT_BTNCLICK	"pushed button"
#define GFSCR_ELT_BTNENABLED	"enabled button"
#define GFSCR_ELT_BTNDISABLED	"disabled button"
#define GFSCR_ELT_LABELCOLOR	"label"
#define GFSCR_ELT_TIPCOLOR	"tip"
#define GFSCR_ELT_MOUSECOLOR1	"mouse 1"
#define GFSCR_ELT_MOUSECOLOR2	"mouse 2"
#define GFSCR_ELT_HELPCOLOR1	"help key"
#define GFSCR_ELT_HELPCOLOR2	"help description"
#define GFSCR_ELT_BGSCROLLIST	"background scroll list"
#define GFSCR_ELT_SCROLLIST	"scroll list"
#define GFSCR_ELT_BGSELSCROLLIST "background selected scroll list"
#define GFSCR_ELT_SELSCROLLIST	"selected scroll list"
#define GFSCR_ELT_EDITCURSORCLR	"edit box cursor color"

#define GFSCR_ATTR_RED		"red"
#define GFSCR_ATTR_GREEN	"green"
#define GFSCR_ATTR_BLUE		"blue"
#define GFSCR_ATTR_ALPHA	"alpha"


/******************* 
 * Trace Interface *
 *******************/

extern void GfTrace(char *szTrc);

/** Output Trace with one parameter
    @param	s	string to display
    @param	p1	parameter (ala printf)
    @fn	GfTrace1(s, p1)
 */
#define GfTrace1(s, p1)		\
{				\
    char _trc_buff[256];	\
    sprintf(_trc_buff, s, p1);	\
    GfTrace(_trc_buff);		\
}

/** Output Trace with two parameters
    @param	s	string to display
    @param	p1	parameter (ala printf)
    @param	p2	parameter (ala printf)
    @fn	GfTrace2(s, p1, p2)
 */
#define GfTrace2(s, p1, p2)		\
{					\
    char _trc_buff[256];		\
    sprintf(_trc_buff, s, p1, p2);	\
    GfTrace(_trc_buff);			\
}

/** Output Trace with three parameters
    @param	s	string to display
    @param	p1	parameter (ala printf)
    @param	p2	parameter (ala printf)
    @param	p3	parameter (ala printf)
    @fn	 GfTrace3(s, p1, p2, p3)
 */
#define GfTrace3(s, p1, p2, p3)		\
{					\
    char _trc_buff[256];		\
    sprintf(_trc_buff, s, p1, p2, p3);	\
    GfTrace(_trc_buff);			\
}

/** Output Trace with n parameters
    @param	s	string to display
    @param	args	parameter (ala printf)
    @fn	 GfTracen(s, args...)
 */
#ifdef WIN32
#define GfTracen printf
#else
#define GfTracen(s, args...)		\
{					\
    char _trc_buff[256];		\
    sprintf(_trc_buff, s, ## args);	\
    GfTrace(_trc_buff);			\
}
#endif

#if !(_DEBUG || DEBUG)
#ifdef WIN32
#define GfOut printf
#else
#define GfOut(a, args...)
#endif

#else /* _DEBUG || DEBUG */

/** Console output
    @param	s	string to display
    @param	args	printf args
    @fn	 GfOut(s, args...)
 */
#ifdef WIN32
#define GfOut printf
#else
#define GfOut(s, args...)		printf(s, ## args)
#endif

#endif /* _DEBUG || DEBUG */

/******************* 
 * Time  Interface *
 *******************/
extern double GfTimeClock(void);
extern char *GfGetTimeStr(void);


/************************
 * Ring Lists Interface *
 ************************/

/** Ring List structure */
typedef struct tRingList
{
    /** Next element in the list */
    struct tRingList *next;
    struct tRingList *prev;
} tRingList;

typedef struct tRingListHead
{
    tRingList *next;
    tRingList *prev;
} tRingListHead;


extern void GfRlstInit(tRingListHead *head);
extern void GfRlstAddFirst(tRingListHead *head, tRingList *elt);
extern void GfRlstAddLast(tRingListHead *head, tRingList *elt);
extern tRingList *GfRlstUnlinkFirst(tRingListHead *head);
extern tRingList *GfRlstUnlinkLast(tRingListHead *head);
extern tRingList *GfRlstUnlinkElt(tRingList *elt);
extern tRingList *GfRlstGetFirst(tRingListHead *head);
extern tRingList *GfRlstGetNext(tRingListHead *head, tRingList *elt);
extern tRingList *GfRlstGetLast(tRingListHead *head);
extern tRingList *GfRlstGetPrev(tRingListHead *head, tRingList *elt);
extern void GfRlstSeekElt(tRingListHead *head, tRingList *elt);

extern void GfInit(void);

/* Mean values */
#define GF_MEAN_MAX_VAL	5

typedef struct 
{
    int		curNum;
    tdble	val[GF_MEAN_MAX_VAL+1];
} tMeanVal;

extern tdble gfMean(tdble v, tMeanVal *pvt, int n, int w);
extern void gfMeanReset(tdble v, tMeanVal *pvt);

#endif /* __TGF__H__ */


