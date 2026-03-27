##############################################################################
#
#    file                 : Makefile
#    created              : 2024
#    copyright            : (C) 2024
#
##############################################################################
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
##############################################################################

SOURCES   = oglgraph.cpp OGLRenderer.cpp Shader.cpp Mesh.cpp Texture.cpp Camera.cpp ShadowMap.cpp PostProcess.cpp Particles.cpp SkidMarks.cpp AC3DLoader.cpp

MODULE    = oglgraph.so

MODULEDIR = modules/graphic

LIBS      = -lGL -lGLU -lglut

SHIPDIR   = config

SHIP      = oglgraph.xml

CONFIGCREATEDIRS = ${SHIPDIR}

CONFIG    = $(SHIP)

src_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}
