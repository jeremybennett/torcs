##############################################################################
#
#    file                 : Makefile
#    created              : Wed Jan 19 19:07:05 CET 2000
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


DATADIR   = tracks/road/g-track-3

DATA      = g-track-3.xml g-track-3.acc $(shell find * -maxdepth 0 -type f -name '*.png') $(shell find * -maxdepth 0 -type f -name '*.rgb')

data-tracks-base_PKGFILES	= $(DATA)

data-tracks-base_PKGDIR	= $(DATADIR)

include ${MAKE_DEFAULT}


