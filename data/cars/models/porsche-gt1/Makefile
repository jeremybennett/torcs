##############################################################################
#
#    file                 : Makefile
#    created              : Sun Mar 25 01:32:41 CET 2001
#    copyright            : (C) 2001 by Eric Espié                        
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




DATADIR   = cars/porsche-gt1

DATA      = $(shell find *.xml -maxdepth 0 -type f -print) \
            $(shell find *.rgb -maxdepth 0 -type f -print) \
            $(shell find *.acc -maxdepth 0 -type f -print)

data-cars-extra_PKGFILES	= $(DATA) porsche-gt1.xcf $(shell find *.ac -maxdepth 0 -type f -print)

data-cars-extra_PKGDIR	= $(DATADIR)

include ${MAKE_DEFAULT}



