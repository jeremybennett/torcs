/***************************************************************************

    file        : grscreen.h
    created     : Thu May 15 22:11:19 CEST 2003
    copyright   : (C) 2003 by Eric Espié                        
    email       : eric.espie@torcs.org   
    version     : $Id$                                  

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

    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/

#ifndef _GRSCREEN_H_
#define _GRSCREEN_H_

#include <car.h>
#include "grcam.h"
#include "grboard.h"

class cGrScreen
{
 protected:
    int			id;

    tCarElt		*curCar;		/* Current car viewed */
    tCarElt		**cars;			/* list of cars */ 


    int			curCamHead;		/* the current camera list */	
    tGrCamHead		cams[10];		/* from F2 to F11 */

    class cGrPerspCamera	*curCam;	/* the current camera */
    class cGrCarCamMirror	*mirrorCam;	/* the mirror camera */
    class cGrPerspCamera	*dispCam;	/* the display camera */
    class cGrOrthoCamera	*boardCam;	/* the board camera */
    class cGrBackgroundCam 	*bgCam;		/* the background camera */

    class cGrBoard		*board;		/* the board */

    int			drawCurrent;		/* Should the current car be drawn */

    int			scrx, scry, scrw, scrh;
    float		viewRatio;

    int			active;			/* Is the screen activated */

    int			selectNextFlag;
    int			selectPrevFlag;
    int			mirrorFlag;

    void loadParams(tSituation *s);		/* load from parameters files */

public:

    cGrScreen(int id);

    ~cGrScreen();

    void activate(int x, int y, int w, int h);
    void desactivate(void);

    void setZoom(int zoom);

    int  isInScreen(int x, int y);

    void update(tSituation *s, float Fps);

    void cGrScreen::camDraw(tSituation *s);

    void updateCurrent(tSituation *s);

    void selectCamera(int cam);

    void selectBoard(int brd);

	void selectTrackMap();

    void setCurrentCar(tCarElt *newCurCar);

    void initCams(tSituation *s);

    void initBoard(void);

    void selectNextCar(void);
    void selectPrevCar(void);
    void switchMirror(void);

    tCarElt *getCurrentCar(void) {
	return curCar;
    }
    cGrCamera* getCurCamera(void) {
	return curCam;
    }
    float getViewRatio(void) {
	return viewRatio;
    }

    int getCurCamHead(void) {
	return curCamHead;
    }

    int isActive(void) {
	return active;
    }

    int getId(void) {
	return id;
    }
    int getScrX (void) {
	return scrx;
    }
    int getScrY (void) {
	return scry;
    }
    int getScrW (void) {
	return scrw;
    }
    int getScrH (void) {
	return scrh;
    }
    
};


#endif /* _GRSCREEN_H_ */ 



