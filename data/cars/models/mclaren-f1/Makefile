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




DATADIR   = cars/mclaren-f1

DATA      = $(shell find *.xml -maxdepth 0 -type f -print) \
            $(shell find *.rgb -maxdepth 0 -type f -print) \
            $(shell find *.acc -maxdepth 0 -type f -print)

data-cars-extra_PKGFILES	= $(DATA) mclaren-f1-512.xcf $(shell find *.ac -maxdepth 0 -type f -print)

data-cars-extra_PKGDIR	= $(DATADIR)

include ${MAKE_DEFAULT}



