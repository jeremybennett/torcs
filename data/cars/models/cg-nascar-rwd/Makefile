##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:03:41 CET 2000
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

CAR       = cg-nascar-rwd

DATADIR   = cars/$(CAR)

DATA      = $(CAR).xml \
            $(CAR).rgb tex-wheel.rgb \
            $(shell find *.acc -maxdepth 0 -type f -print)

data-cars-nascar_PKGFILES = $(DATA)

data-cars-nascar_PKGDIR	= $(DATADIR)

include ${MAKE_DEFAULT}


