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
    @defgroup params Parameter handling API
    @brief With this API you can handle parameter sets in TORCS, this includes
    manipulation of data in memory, and writing into/reading from XML files.
    
    The parameters are structured in:
    <br><b>section</b> - containing a familly of parameters on the same topic.
    <br><b>list</b> (subsections) - containing <b>elements</b>
    of <b>numerical attributes</b> and <b>string attributes</b>.
    <br>
    <br>The API is not thread safe, because parameter sets and handles carry internal
    state regarding iteration and XML parsing. The parameter sets are reference counted,
	so usually multiple handles can refer to the same parameter set.
*/
/**
   @defgroup paramsfile Parameter file handling API
   Create, read and write parameter files
   @ingroup params
*/
/**
   @defgroup conf		Test.
   TESTRead, write, merge parameters files.
   @ingroup params
*/
/**
   @defgroup paramsdata Parameter data handling API
   Handling of data in parameter sets 
   @ingroup params
*/
/**
   @defgroup paramslist Parameter list manipulation API
   Handling of multiple sections or subsections and the elements in parameter sets
   @ingroup params
*/
/**
   @defgroup paramshelper Parameter helper functions
   Internal (not exported) helper functions, not part of the API
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

    @section archlist Architecture
    
    - [Architecture Overview](@ref architecture)
    
    @section robotlist Robots API
    
    - [Robots functions interface](@ref robotmodint)
    - [Tools for robots](@ref robottools)
    - [Parameter handling API](@ref params)
    - [Tracks structure](@ref trackstruct)
    - [Cars structure](@ref carstruct)

    @section racemanlist Race Manager API

    - [Tools for race managers](@ref racemantools)
    - [Parameter handling API](@ref params)
    - [Tracks structure](@ref trackstruct)

*/

#endif /* _TORCSDOC_H_ */ 



