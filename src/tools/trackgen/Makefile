##############################################################################
#
#    file                 : Makefile
#    created              : Sat Dec 23 09:19:01 CET 2000
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



PROGRAM      = trackgen

COMPILFLAGS  = -DINSTBASE="\"${INSTBASE}\""

DATADIR      = tools/trackgen

DATA         = trackgen.xml

SOURCES      = trackgen.cpp track.cpp easymesh.cpp linuxspec.cpp relief.cpp

SOLIBS       = -lplibssg -lplibsg -lplibul -lrobottools -ltgf -ltxml


include ${MAKE_DEFAULT}


