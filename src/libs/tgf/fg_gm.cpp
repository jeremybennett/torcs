/***************************************************************************

    file        : fg_gm.cpp
    created     : Sat Mar  8 14:40:50 CET 2003
    copyright   : (C) 2003 by Eric Espié                        
    email       : eric.espie@torcs.org   
    version     : $Id$                                  

 ***************************************************************************/

/*
 * The freeglut library private include file.
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Thu Dec 2 1999
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/** @file   
    	Missing X11 gamemode in glut, taken from <a href="http://freeglut.sf.net">freeglut</a> 
    @version	$Id$
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <tgf.h>
#include "fg_gm.h"

#ifndef WIN32

#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

/*
 * This will generate errors, but I don't have any idea how to fix it (will autoconf help?)
 */
#include <X11/extensions/xf86vmode.h>

static int fgInitDone = 0;

typedef struct tagSFG_Display SFG_Display;
struct tagSFG_Display
{
    Display*        display;            /* The display we are being run in.  */
    int             Screen;             /* The screen we are about to use.   */
    Window          RootWindow;         /* The screen's root window.         */
    int             Connection;         /* The display's connection number   */
    Atom            DeleteWindow;       /* The window deletion atom          */

    XF86VidModeModeLine DisplayMode;    /* Current screen's display settings */
    int             DisplayModeClock;   /* The display mode's refresh rate   */

    int             ScreenWidth;        /* The screen's width in pixels      */
    int             ScreenHeight;       /* The screen's height in pixels     */
    int             ScreenWidthMM;      /* The screen's width in milimeters  */
    int             ScreenHeightMM;     /* The screen's height in milimeters */
};

/*
 * A helper structure holding two ints and a boolean
 */
typedef struct tagSFG_XYUse SFG_XYUse;
struct tagSFG_XYUse
{
    int         X, Y;               /* The two integers...               */
    int         Use;                /* ...and a single int.          */
};

/*
 * This structure holds different freeglut settings
 */
typedef struct tagSFG_State SFG_State;
struct tagSFG_State
{
    SFG_XYUse       Position;           /* The default windows' position     */
    SFG_XYUse       Size;               /* The default windows' size         */
    unsigned int    DisplayMode;        /* The display mode for new windows  */

    int     	    ForceDirectContext; /* Should we force direct contexts?  */
    int     	    TryDirectContext;   /* What about giving a try to?       */

    int   	    ForceIconic;        /* All new top windows are iconified */

    int    	    GLDebugSwitch;      /* OpenGL state debugging switch     */
    int     	    XSyncSwitch;        /* X11 sync protocol switch          */
    int     	    IgnoreKeyRepeat;	/* Whether to ignore key repeat...	 */

    SFG_XYUse       GameModeSize;       /* The game mode screen's dimensions */
    int             GameModeDepth;      /* The pixel depth for game mode     */
    int             GameModeRefresh;    /* The refresh rate for game mode    */
};

/*
 * A structure pointed by g_pDisplay holds all information
 * regarding the display, screen, root window etc.
 */
static SFG_Display fgDisplay;

/*
 * The settings for the current freeglut session
 */
static SFG_State fgState;

/*
 * A call to this function should initialize all the display stuff...
 */
static void fgInitialize(void)
{
    char* displayName;

    displayName = getenv("DISPLAY");
    if (!displayName)
    {
	displayName = ":0.0";
    }
    
    /*
     * Have the display created
     */
    fgDisplay.display = XOpenDisplay( displayName );

    if( fgDisplay.display == NULL )
    {
        /*
         * Failed to open a display. That's no good.
         */
        GfOut( "failed to open display '%s'", XDisplayName( displayName ) );
    }

    /*
     * Grab the default screen for the display we have just opened
     */
    fgDisplay.Screen = DefaultScreen( fgDisplay.display );

    /*
     * The same applying to the root window
     */
    fgDisplay.RootWindow = RootWindow(
        fgDisplay.display,
        fgDisplay.Screen
    );

    /*
     * Grab the logical screen's geometry
     */
    fgDisplay.ScreenWidth  = DisplayWidth(
        fgDisplay.display,
        fgDisplay.Screen
    );

    fgDisplay.ScreenHeight = DisplayHeight(
        fgDisplay.display,
        fgDisplay.Screen
    );

    /*
     * Grab the physical screen's geometry
     */
    fgDisplay.ScreenWidthMM = DisplayWidthMM(
        fgDisplay.display,
        fgDisplay.Screen
    );

    fgDisplay.ScreenHeightMM = DisplayHeightMM(
        fgDisplay.display,
        fgDisplay.Screen
    );

    /*
     * The display's connection number
     */
    fgDisplay.Connection = ConnectionNumber( fgDisplay.display );

    /*
     * Create the window deletion atom
     */
    fgDisplay.DeleteWindow = XInternAtom(
        fgDisplay.display,
        "WM_DELETE_WINDOW",
        FALSE
	);
}

/*
 * Remembers the current visual settings, so that
 * we can change them and restore later...
 */
static void fghRememberState( void )
{
    /*
     * This highly depends on the XFree86 extensions, not approved as X Consortium standards
     */
    if (!fgInitDone)
    {
	fgInitialize();
	fgInitDone = 1;
    }
    
    /*
     * Query the current display settings:
     */
    XF86VidModeGetModeLine(
        fgDisplay.display,
        fgDisplay.Screen,
        &fgDisplay.DisplayModeClock,
        &fgDisplay.DisplayMode
    );
}

/*
 * Restores the previously remembered visual settings
 */
static void fghRestoreState( void )
{
    /*
     * This highly depends on the XFree86 extensions, not approved as X Consortium standards
     */
    XF86VidModeModeInfo** displayModes;
    int i, displayModesCount;

    /*
     * Query for all the display available...
     */
    XF86VidModeGetAllModeLines(
        fgDisplay.display,
        fgDisplay.Screen,
        &displayModesCount,
        &displayModes
    );

    /*
     * Check every of the modes looking for one that matches our demands
     */
    for( i=0; i<displayModesCount; i++ )
    {
        if( displayModes[ i ]->hdisplay == fgDisplay.DisplayMode.hdisplay &&
            displayModes[ i ]->vdisplay == fgDisplay.DisplayMode.vdisplay &&
            displayModes[ i ]->dotclock == (unsigned int)fgDisplay.DisplayModeClock )
        {
            /*
             * OKi, this is the display mode we have been looking for...
             */
            XF86VidModeSwitchToMode(
                fgDisplay.display,
                fgDisplay.Screen,
                displayModes[ i ]
            );

	    /* apply the modifs */
	    XF86VidModeGetAllModeLines(
		fgDisplay.display,
		fgDisplay.Screen,
		&displayModesCount,
		&displayModes
	    );

            return;
        }
    }
}

/*
 * Checks the display mode settings against user's preferences
 */
static int fghCheckDisplayMode( int width, int height, int depth, int refresh )
{
    /*
     * The desired values should be stored in fgState structure...
     */
    return( (width == fgState.GameModeSize.X) && (height == fgState.GameModeSize.Y) &&
            (depth == fgState.GameModeDepth)  && (refresh == fgState.GameModeRefresh) );
}

/*
 * Changes the current display mode to match user's settings
 */
static int fghChangeDisplayMode( int haveToTest )
{
    /*
     * This highly depends on the XFree86 extensions, not approved as X Consortium standards
     */
    XF86VidModeModeInfo** displayModes;
    int i, displayModesCount;

    /*
     * Query for all the display available...
     */
    XF86VidModeGetAllModeLines(
        fgDisplay.display,
        fgDisplay.Screen,
        &displayModesCount,
        &displayModes
    );
    
    /*
     * Check every of the modes looking for one that matches our demands
     */
    for( i=0; i<displayModesCount; i++ )
    {
        if( fghCheckDisplayMode( displayModes[ i ]->hdisplay, displayModes[ i ]->vdisplay,
                                 fgState.GameModeDepth, fgState.GameModeRefresh ) )
        {
            /*
             * OKi, this is the display mode we have been looking for...
             */
            XF86VidModeSwitchToMode(
                fgDisplay.display,
                fgDisplay.Screen,
                displayModes[ i ]
            );

            /*
             * Set the viewport's origin to (0,0) (the game mode window's top-left corner)
             */
            XF86VidModeSetViewPort(
                fgDisplay.display,
                fgDisplay.Screen,
                (fgDisplay.ScreenWidth - fgState.GameModeSize.X) / 2,
                (fgDisplay.ScreenHeight - fgState.GameModeSize.Y) / 2
            );

	    /* apply the modifs */
	    XF86VidModeGetAllModeLines(
		fgDisplay.display,
		fgDisplay.Screen,
		&displayModesCount,
		&displayModes
	    );

	    /*
             * Return successfull...
             */
            return( TRUE );
        }
    }

    /*
     * Something must have went wrong
     */
    return( FALSE );
}

#endif /* WIN32 */

/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

/*
 * Sets the game mode display string
 */
void fglutGameModeString( const char* string )
{
#ifndef WIN32
    int width = 640, height = 480, depth = 16, refresh = 72;

    /*
     * This one seems a bit easier than glutInitDisplayString. The bad thing
     * about it that I was unable to find the game mode string definition, so
     * that I assumed it is: "[width]x[height]:[depth]@[refresh rate]", which
     * appears in all GLUT game mode programs I have seen to date.
     */
    if( sscanf( string, "%ix%i:%i@%i", &width, &height, &depth, &refresh ) != 4 )
        if( sscanf( string, "%ix%i:%i", &width, &height, &depth ) != 3 )
            if( sscanf( string, "%ix%i@%i", &width, &height, &refresh ) != 3 )
                if( sscanf( string, "%ix%i", &width, &height ) != 2 )
                    if( sscanf( string, ":%i@%i", &depth, &refresh ) != 2 )
                        if( sscanf( string, ":%i", &depth ) != 1 )
                            if( sscanf( string, "@%i", &refresh ) != 1 )
                                GfOut( "unable to parse game mode string `%s'", string );

    /*
     * Hopefully it worked, and if not, we still have the default values
     */
    fgState.GameModeSize.X  = width;
    fgState.GameModeSize.Y  = height;
    fgState.GameModeDepth   = depth;
    fgState.GameModeRefresh = refresh;
#endif /* WIN32 */
}

/*
 * Enters the game mode
 */
int fglutEnterGameMode( void )
{
#ifndef WIN32
    /*
     * Remember the current resolution, etc.
     */
    fghRememberState();

    /*
     * We are ready to change the current screen's resolution now
     */
    if( fghChangeDisplayMode( FALSE ) == FALSE )
    {
        GfOut( "failed to change screen settings" );
        return( FALSE );
    }
    
    /*
     * Return successfull
     */
    return( TRUE );
#else /* WIN32 */
    return( FALSE );
#endif /* WIN32 */
}

/*
 * Leaves the game mode
 */
void fglutLeaveGameMode( void )
{
#ifndef WIN32
    /*
     * Then, have the desktop visual settings restored
     */
    fghRestoreState();
#endif /* WIN32 */
}
