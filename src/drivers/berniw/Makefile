ROBOT = berniw

MODULE = ${ROBOT}.so

MODULEDIR = drivers/${ROBOT}

SOURCES   = ${ROBOT}.cpp spline.cpp trackdesc.cpp pathfinder.cpp mycar.cpp

SHIPDIR   = drivers/${ROBOT}

SHIP      = ${ROBOT}.xml logo.rgb parameter.dat intsinsqr.dat intcossqr.dat

SHIPSUBDIRS = 1 2 3 4 5 6 7 8 9 10

PKGSUBDIRS	= $(SHIPSUBDIRS)

berniw-robots_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

berniw-robots_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

# Mandatory Line Do Not Remove 
include ${MAKE_DEFAULT}




