##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:49:57 CET 2000
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


TOOLSUBDIRS = gennmtab

SOLIBRARY   = libtxml.so

SOLIBDIR    = lib

SOURCES   = xmltok.c xmlrole.c xmlparse.c hashtable.c xml.cpp

EXPDIR  = include

EXPORTS = xml.h xmlparse.h

include ${MAKE_DEFAULT}

nametab.h:
	rm -f $@
	${TOOLSDIR}/gennmtab >$@

xmltok.o: nametab.h

