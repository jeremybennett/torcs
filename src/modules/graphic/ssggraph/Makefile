##############################################################################
#
#    file                 : Makefile
#    created              : Mon Aug 30 21:40:19 CEST 1999
#    copyright            : (C) 1999 by Eric Espie                         
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


SOURCES   = grmain.cpp grboard.cpp grsound.cpp ssggraph.cpp grcam.cpp grcar.cpp \
	    grscene.cpp grutil.cpp grshadow.cpp grsmoke.cpp grskidmarks.cpp grloadac.cpp

MODULE    = ssggraph.so

MODULEDIR = modules/graphic

LIBS      = -lplibsl -lplibsm -lplibsg -lplibssg -lplibul

DATADIR   = config

DATA      = graph.xml

src_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


