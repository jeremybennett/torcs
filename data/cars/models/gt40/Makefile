##############################################################################
#
#    file        : Makefile
#    created     : Sun Nov 10 19:52:39 CET 2002
#    copyright   : (C) 2002 by Eric Espié                        
#    email       : Eric.Espie@torcs.org   
#    version     : $Id$                                  
#
##############################################################################
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
##############################################################################

CAR       = gt40

DATADIR   = cars/$(CAR)

DATA      = $(CAR).xml readme.txt \
            $(CAR).rgb tex-wheel.rgb shadow.rgb \
            $(shell find *.acc -maxdepth 0 -type f -print) \
        $(shell find *.png -maxdepth 0 -type f -print)

data-cars-extra_PKGFILES	= $(DATA) $(shell find *.xcf -maxdepth 0 -type f -print)

data-cars-extra_PKGDIR		= $(DATADIR)

include ${MAKE_DEFAULT}



