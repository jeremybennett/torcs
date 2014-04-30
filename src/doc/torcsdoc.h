/***************************************************************************

    file                 : torcsdoc.h
    created              : Sat Jul 27 14:24:31 CEST 2002
    copyright            : (C) 2001-2014 by Eric Espie, Bernhard Wymann
    email                : Eric.Espie@torcs.org
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
    		
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/

#ifndef _TORCSDOC_H_
#define _TORCSDOC_H_

/**
   @defgroup module		Dynamic Modules
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
   @defgroup gui		GUI Management.
   This is an interface to manage menus.
   @note	The screen size is fiwed to 640x480 and the origin is in the lower-left corner.
*/
/**
   @defgroup img		Image Management.
   Load and store png images with easy interface.
*/
/**
   @defgroup dir		Directory Management.
   This is used for directory manipulation.
*/
/**
    @defgroup params	 	Parameters file management.
    The parameters are stored in XML files and accessed only with this API.
    <br>The parameters are structured in:
    <br><b>section</b> - containing a familly of parameters on the same topic.
    <br><b>list</b> - containing <b>elements</b>
    of <b>numerical attributes</b> and <b>string attributes</b>.
*/
/**
   @defgroup paramsfile		Parameters File manipulation.
   Read, write, merge parameters files.
   @ingroup params
*/
/**
   @defgroup paramsdata		Parameters Data manipulation.
   Read, write, merge parameters files.
   @ingroup params
*/
/**
   @defgroup paramslist		Parameters List manipulation.
   Read, write, merge parameters files.
   @ingroup params
*/
/**
   @defgroup screen		Screen management.
*/
/**
   @defgroup trace		Trace management.
   Allow the trace in the file <tt>trace.txt</tt>
*/
/** 
    @defgroup OS		OS dependant functions
    OS specific function table
*/
/**
   @defgroup definitions	Global definitions
   This is the global definitions used in TORCS.
*/
/**
   @defgroup trackstruct	Tracks Structure
   This is the tracks structure definition.
   <br><b>tTrack</b> is the main track structure.
   <br><b>trackSeg</b> is the segment structure.
   @ingroup definitions
*/
/**
   @defgroup carstruct		Cars Structure
   This is the cars structure definition.
   <br><b>CarElt</b> is the main car structure.
   @ingroup definitions
*/
/**
   @defgroup raceinfo	Race Information
   This is the race information structures definition.
   @ingroup definitions
*/
/**
   @defgroup robottools		Tools for robots.
   This is a collection of useful functions for programming a robot.

*/
/**
   @defgroup modint	Modules interfaces
   This is the interfaces for the dynamic modules.
*/
/**
   @defgroup tailq	Tail Queue Management
   This is the management of tail queues.
*/
/**
   @defgroup hash	Hash tables Management
   This is the hash computation API.
*/
/**
   @defgroup ctrl	Control Device Management
   This is the API to use control devices (Keyboard, mouse and joysticks).
*/

/**
    @mainpage	Welcome to the TORCS Documentation

    @section archlist Architecture Documentation
    
    - [Architecture Overview](@ref architecture)
    
    @section robotlist Robot Related Documentation
    
    - [Robots functions interface](@ref robotmodint)
    - [Tools for robots](@ref robottools)
    - [Parameters file management](@ref params)
    - [Tracks structure](@ref trackstruct)
    - [Cars structure](@ref carstruct)

    @section racemanlist Race Managers Related Documentation

    - [Tools for race managers](@ref racemantools)
    - [Parameters file management](@ref params)
    - [Tracks structure](@ref trackstruct)

*/

#endif /* _TORCSDOC_H_ */ 



