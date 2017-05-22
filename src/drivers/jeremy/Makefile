# Main make file for the robot

# Copyright (C) 2017 Jeremy Bennett
# Contributor: Jeremy Bennett <jeremy@jeremybennett.com>

# This file is part of the jeremy robot for TORCS

# The jeremy robot for TORCS is free software: you can redistribute
# it and/or modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation, either
# version 3 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

ROBOT       = jeremy
MODULE      = ${ROBOT}.so
MODULEDIR   = drivers/${ROBOT}
SOURCES     = ${ROBOT}.cpp \
              Driver.cpp

SHIPDIR     = drivers/${ROBOT}
SHIP        = ${ROBOT}.xml car1-trb1.rgb logo.rgb
SHIPSUBDIRS =

PKGSUBDIRS  = ${SHIPSUBDIRS}
src-robots-jeremy_PKGFILES = $(shell find * -maxdepth 0 -type f -print)
src-robots-jeremy_PKGDIR   = ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}
