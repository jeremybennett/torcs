##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:53:52 CET 2000
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


PROGRAM = torcs

SOURCES = main.cpp linuxspec.cpp

LDFLAGS  = -rdynamic

SOLIBS   = ${INSTBASE}/lib/libracemantools.so \
	   ${INSTBASE}/lib/librobottools.so   \
	   ${INSTBASE}/lib/libtorcs.so        \
	   ${INSTBASE}/lib/libtgf.so          \
	   ${INSTBASE}/lib/libtxml.so	      \
	   -lplibul

EXPDIR  = include

EXPORTS = osspec.h

include ${MAKE_DEFAULT}




