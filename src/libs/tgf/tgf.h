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
#include <stdarg.h>
#include <GL/glut.h>
#include <osspec.h>
#include <queue.h>

/* typedef double tdble; */
/** Floating point type used in TORCS.
    @ingroup definitions
*/
typedef float tdble;

#ifndef MAX
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#endif

#ifndef MIN
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#endif

#define FREEZ(x) do {				\
    if (x) {					\
	free(x);				\
	x = 0;					\
    }						\
} while (0)

// <esppat>
#ifdef WIN32
#define malloc _tgf_win_malloc
#define calloc _tgf_win_calloc
#define realloc _tgf_win_realloc
#define free _tgf_win_free
#define strdup _tgf_win_strdup
#define _strdup _tgf_win_strdup
extern void * _tgf_win_malloc(size_t size);
extern void * _tgf_win_calloc(size_t num, size_t size);
extern void * _tgf_win_realloc(void * memblock, size_t size);
extern void _tgf_win_free(void * memblock);
extern char * _tgf_win_strdup(const char * str);
#endif // WIN32
// </esppat>

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
    char		*name;		/**< name of the module (short) (NULL if no module) */
    char		*desc;		/**< description of the module (can be long) */
    tfModPrivInit	fctInit;	/**< init function */
    unsigned int	gfId;		/**< supported framework version */
    int			index;		/**< index if multiple interface in one dll */
    int			prio;		/**< priority if needed */
    int			magic;		/**< magic number for integrity check */
} tModInfo;

/* module init function interface */
typedef int (*tfModInfo)(tModInfo *);	/* first function called in the module */

/* module shutdown function interface */
typedef int (*tfModShut)(void);	/* last function called in the module */


/** list of module interfaces */
typedef struct ModList {
    tModInfo		modInfo[MAX_MOD_ITF];	/**< module info list for this dll */
#ifdef _WIN32
    HMODULE		handle;			/**< handle of loaded module */
#else
    void		*handle;		/**< handle of loaded module */
#endif
    char		*sopath;		/**< path name of file */
    struct ModList	*next;			/**< next module in list */
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
    struct FList	*next;		/**< Next entry */
    struct FList	*prev;		/**< Previous entry */
    char		*name;		/**< File name */
    char		*dispName;	/**< Name to display on screen */
    void		*userData;	/**< User data */
} tFList;

extern tFList *GfDirGetList(char *dir);
typedef void (*tfDirfreeUserData)(void*);	/**< Function to call for releasing the user data associated with file entry */
extern void GfDirFreeList(tFList *list, tfDirfreeUserData freeUserData);


/**********************************
 *  Interface For Parameter Files *
 **********************************/

/*
 *	This set of function is used to store and retrieve
 *	values in parameters files.
 */


/* parameters file type */
#define GFPARM_PARAMETER	0	/**< Parameter file */
#define GFPARM_TEMPLATE		1	/**< Template file */
#define GFPARM_PARAM_STR	"param"
#define GFPARM_TEMPL_STR	"template"

/* parameters access mode */
#define GFPARM_MODIFIABLE	1	/**< Parameter file allowed to be modified */
#define GFPARM_WRITABLE		2	/**< Parameter file allowed to be saved on disk */

/* parameter file read */
#define GFPARM_RMODE_STD	0x01	/**< if handle already openned return it */
#define GFPARM_RMODE_REREAD	0x02	/**< reread the parameters from file and release the previous ones */
#define GFPARM_RMODE_CREAT	0x04	/**< Create the file if doesn't exist */

extern void *GfParmReadFile(const char *file, int mode);
/* parameter file write */
extern int GfParmWriteFile(const char *file, void* handle, char *name, int type, const char *dtd);

extern char *GfParmGetName(void *handle);
extern char *GfParmGetFileName(void *handle);

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
#define GFPARM_MMODE_SRC	1 /**< use ref and modify existing parameters with tgt */
#define GFPARM_MMODE_DST	2 /**< use tgt and verify ref parameters */
#define GFPARM_MMODE_RELSRC	4 /**< release ref after the merge */
#define GFPARM_MMODE_RELDST	8 /**< release tgt after the merge */
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
extern void GfScrReinit(void*);


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
    int		pos;		/**< Current scroll bar position */
    void	*userData;	/**< Associated user data */
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
extern int  GfuiScreenIsActive(void *screen);
extern void GfuiScreenReplace(void *screen);
extern void GfuiScreenDeactivate(void);
extern void *GfuiHookCreate(void *userDataOnActivate, tfuiCallback onActivate);
extern void GfuiHookRelease(void *hook);
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
#define	GFUI_VISIBLE	1	/**< Object visibility flag  */
#define	GFUI_INVISIBLE	0	/**< Object invisibility flag  */
extern int GfuiVisiblilitySet(void *scr, int id, int visible);
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

#ifdef WIN32
#define GfTrace	printf
#define GfFatal printf
#else

#define GfTrace printf

static inline void
GfFatal(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    exit(1);
}
#endif

#if !(_DEBUG || DEBUG)
#ifdef WIN32
#define GfOut printf
#else


/** Console output
    @param	s	string to display
    @param	args	printf args
    @fn	 GfOut(s, args...)
 */
static inline void
GfOut(char *fmt, ...)
{
}

#endif

#else /* _DEBUG || DEBUG */

#define GfOut printf

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
    struct tRingList *next;	/**< Next element in the list */
    struct tRingList *prev;	/**< Previous element in the list */
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


