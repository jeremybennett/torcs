##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:32:07 CET 2000
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


SOLIBRARY = libracemantools.so

SOLIBDIR  = .

SOURCES   = trackselect.cpp racemantools.cpp driverselect.cpp results.cpp pitmenu.cpp loadingscreen.cpp racemenu.cpp

EXPDIR    = include

EXPORTS   = racemantools.h

DATADIR   = results

DATA      = res.png

src_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


