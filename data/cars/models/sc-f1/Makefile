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

CAR       = sc-f1

DATADIR   = cars/$(CAR)

DATA      = $(CAR).xml readme.txt \
            $(CAR).rgb tex-wheel.rgb shadow.rgb \
            $(shell find *.ac -maxdepth 0 -type f -print)

data-cars-extra_PKGFILES	= $(DATA)

data-cars-extra_PKGDIR		= $(DATADIR)

include ${MAKE_DEFAULT}


