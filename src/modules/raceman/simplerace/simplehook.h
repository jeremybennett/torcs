/***************************************************************************

    file        : simplehook.h
    created     : Tue Dec  3 22:58:45 CET 2002
    copyright   : (C) 2002 by Eric Espié                        
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

#ifndef _SIMPLEHOOK_H_
#define _SIMPLEHOOK_H_

extern void *SrConfigHookInit(void);
extern void  SrConfigHookShutdown(void);
extern void *SrErrorHookInit(void);
extern void  SrErrorHookShutdown(void);
extern void *SrBackToRaceHookInit(void);
extern void  SrBackToRaceHookShutdown(void);
extern void *SrConfigBackHookInit(void);
extern void  SrConfigBackHookShutdown(void);
extern void *SrRaceAgainHookInit(void);
extern void  SrRaceAgainHookShutdown(void);

#endif /* _SIMPLEHOOK_H_ */ 



