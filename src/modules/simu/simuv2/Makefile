##############################################################################
#
#    file                 : Makefile
#    created              : Sun Mar 19 00:04:32 CET 2000
#    copyright            : (C) 2000 by Eric Espie                         
#    email                : torcs@free.fr   
#    version              : $Id$                                  
#
##############################################################################
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
##############################################################################


MODULE		= simuv2.so

MODULEDIR	= modules/simu

SOURCES		= simu.cpp \
	   	  simuitf.cpp \
	  	  car.cpp \
	  	  aero.cpp \
	  	  engine.cpp \
	  	  axle.cpp \
	  	  steer.cpp \
	  	  susp.cpp \
	  	  brake.cpp \
	  	  wheel.cpp \
	  	  transmission.cpp \
	  	  differential.cpp \
	  	  collide.cpp

LIBS		=  -lplibsg -lplibul -L${EXPORTBASE}/lib -lsolid

SUBDIRS		= SOLID-2.0

EXPINCDIRS	= SOLID-2.0

include ${MAKE_DEFAULT}

