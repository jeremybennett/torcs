##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:38:24 CET 2000
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


SOLIBRARY = libtgf.so

SOLIBDIR  = .

SOURCES   = 	guimenu.cpp \
		module.cpp \
		os.cpp \
		params.cpp \
		tgf.cpp \
		trace.cpp \
		screen.cpp \
		gui.cpp \
		guifont.cpp \
		guiobject.cpp \
		guilabel.cpp \
		guibutton.cpp \
		guiedit.cpp \
		guihelp.cpp \
		directory.cpp \
		img.cpp \
		guiscrollist.cpp \
		guiscrollbar.cpp \
		guiimage.cpp \
		control.cpp \
		ringlist.cpp


EXPDIR  = include

EXPORTS = tgf.h os.h queue.h

SHIPDIR = config

SHIP    = screen.xml params.dtd

CONFIGCREATEDIRS = config

CONFIG    = screen.xml

src_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}



