##############################################################################
#
#    file                 : Makefile
#    created              : Sun Feb 18 21:02:29 /etc/localtime 2001
#    copyright            : (C) 2000 by Eric Espié                        
#    email                : Eric.Espie@torcs.org   
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

CAR	  = clkdtm

DATADIR   = cars/$(CAR)

DATA      = $(CAR).xml \
            $(CAR).rgb shadow.rgb tex-wheel.rgb \
            $(shell find *.acc -maxdepth 0 -type f -print) \
	    readme.txt 

data-cars-extra_PKGFILES	= $(DATA) $(shell find *.xcf -maxdepth 0 -type f -print)

data-cars-extra_PKGDIR		= $(DATADIR)

include ${MAKE_DEFAULT}


