##############################################################################
#
#    file                 : Make-default.mk
#    created              : Sat Mar 18 23:53:11 CET 2000
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

ifndef TORCS_BASE

-include ${HOME}/.torcs

ifndef TORCS_BASE

error:
	@echo "TORCS_BASE should be defined"
	@exit 1

endif
endif

-include ${TORCS_BASE}/Make-config

SOURCEBASE  = ${TORCS_BASE}/src
EXPORTBASE  = ${TORCS_BASE}/export
DOCBASE     = ${TORCS_BASE}/doc
INSTBASE    = ${DESTDIR}${instdir}
INSTBINBASE = ${DESTDIR}${bindir}
INSTLIBBASE = ${DESTDIR}${prefix}/lib

PACKAGEBASE   = ${TORCS_BASE}/package
PACKAGESBASE  = ${TORCS_BASE}/RPM/SOURCES
SPECFILESBASE = ${TORCS_BASE}/RPM/SPECS

# win32
INIT_WIN32       = ${TORCS_BASE}/setup_win32.bat
INIT_WIN32_D     = ${TORCS_BASE}/setup_win32_debug.bat


define create_dir_win32
TotDir=`echo $$createdir | sed -e "s:${TORCS_BASE}/::g" ` ; \
CurDir='.' ; \
echo "" >> ${INIT_WIN32} ; \
for Dir in `echo $$TotDir | sed -e 's:/: :g' ` ; \
do CurDir=$$CurDir/$$Dir ; \
echo "call .\\create_dir $$CurDir" >> ${INIT_WIN32} ; \
done
endef


OB1 = $(SOURCES:.cpp=.o)
OBJECTS = $(OB1:.c=.o)

define recursedirs
for Dir in $$RecurseDirs ;\
do ${MAKE} -C $$Dir $$RecurseFlags TORCS_BASE=${TORCS_BASE} MAKE_DEFAULT=${MAKE_DEFAULT}; \
done
endef

COMPILATION=
ifdef LIBRARY
COMPILATION=true
endif
ifdef PROGRAM
COMPILATION=true
endif
ifdef MODULE
COMPILATION=true
endif
ifdef SOLIBRARY
COMPILATION=true
endif
ifdef TOOLS
COMPILATION=true
endif

ifdef COMPILATION

default: exports tools compil

ifeq (.depend,$(wildcard .depend))
include .depend
endif

.depend:
	$(CPP) $(INCFLAGS) $(CFLAGSD) $(COMPILFLAGS)  $(SOURCES) > .depend

dep:	.depend

compil: subdirs dep ${LIBRARY} ${SOLIBRARY} ${MODULE} ${PROGRAM}

else

default: exports tools subdirs

compil: subdirs ${LIBRARY} ${SOLIBRARY} ${MODULE} ${PROGRAM}

endif

win32start:
	@rm -f ${INIT_WIN32}
	@echo '@echo off' > ${INIT_WIN32}
	@echo 'echo Checking directories ...' >> ${INIT_WIN32}
	@echo '' >> ${INIT_WIN32}
	@echo 'call .\create_dir .\export' >> ${INIT_WIN32}
	@echo 'call .\create_dir .\export\lib' >> ${INIT_WIN32}
	@echo 'call .\create_dir .\export\libd' >> ${INIT_WIN32}


win32end:
	@sed -e "s:${TORCS_BASE}:\.:g" ${INIT_WIN32} > ${INIT_WIN32}.eee
	@mv ${INIT_WIN32}.eee ${INIT_WIN32}
	@sed -e "s:/src/linux/:/src/windows/:g" ${INIT_WIN32} > ${INIT_WIN32}.eee
	@mv ${INIT_WIN32}.eee ${INIT_WIN32}
	@sed -e "s:/:\\\:g" ${INIT_WIN32} > ${INIT_WIN32}.eee
	@mv ${INIT_WIN32}.eee ${INIT_WIN32}
	@sed -e "s:runtime:runtimed:g" ${INIT_WIN32} > ${INIT_WIN32_D}

win32setup: win32start exportswin32 installshipswin32 installwin32 win32end

.PHONY : clean tools toolsdirs subdirs expincdirs exports export compil cleantools cleancompil \
 datadirs shipdirs doc win32start win32end installship installships installshipdirs

# Recursive targets

exports: expincdirs export

installships: installshipdirs installship

exportswin32: expincwin32dirs exportwin32

installshipswin32: installshipwin32dirs installshipwin32

tools: toolsdirs ${TOOLS} toolsdata

clean: cleancompil cleantools
	-rm -f ${LIBRARY} ${OBJECTS} ${PROGRAM} .depend ${SOLIBRARY} ${MODULE} ${GARBAGE} *~

cleantools: cleantoolsdirs
	-rm -f  ${TOOLS} .depend ${GARBAGE} *~

cleancompil: cleansubdirs
	-rm -f ${LIBRARY} ${OBJECTS} ${PROGRAM} .depend ${SOLIBRARY} ${MODULE} ${GARBAGE} *~

install: installdirs installship installsolibrary installmodule installprogram installtools installtoolsdata

installwin32: installwin32dirs installsolibrarywin32 installmodulewin32

datainstall: installdatadirs installdata

packages: specfiles packagelist

onepackage: packagedirs packagefiles

specfiles: installspecfiles specfilesdirs

.SUFFIXES: .cpp

.cpp.o:
	${CXX} $(INCFLAGS) $(CXXFLAGS) $(COMPILFLAGS) -c $<

.SUFFIXES: .c

.c.o:
	${CC} $(INCFLAGS) $(CFLAGS) $(COMPILFLAGS) -c $<


ifdef LIBRARY

${LIBRARY}: ${OBJECTS}
	${AR} ${ARFLAGS} ${LIBRARY} ${OBJECTS}
	${RANLIB} ${LIBRARY}
	@D=`pwd` ; \
	createdir="${EXPORTBASE}/${LIBDIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${LIBRARY}" ; \
	echo " Exporting $$X to $$createdir/$$X"; \
	ln -sf $$D/$$X $$createdir/$$X

endif

ifdef DATA

installdata: $(DATA)
	@D=`pwd` ; \
	createdir="runtime/${DATADIR}" ; \
	createdir="${INSTBASE}/${DATADIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	for X in $? ; \
	do echo " $(INSTALL_DATA) $$X $$createdir/$$X"; \
	$(INSTALL_DATA) $$X $$createdir/$$X ; \
	done

else

installdata: ;

endif

ifdef SHIP

installship: $(SHIP)
	@D=`pwd` ; \
	createdir="${INSTBASE}/${SHIPDIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	for X in $? ; \
	do echo " $(INSTALL_DATA) $$X $$createdir/$$X"; \
	$(INSTALL_DATA) $$X $$createdir/$$X ; \
	done

installshipwin32: $(SHIP)
	@D=`pwd` ; \
	createdir="runtime/${SHIPDIR}" ; \
	${create_dir_win32} ; \
	for X in $? ; \
	do echo "copy $$D/$$X ./runtime/${SHIPDIR}/$$X" ; \
	echo "copy $$D/$$X ./runtime/${SHIPDIR}/$$X" >> ${INIT_WIN32} ; \
	done

else

installship: ;

installshipwin32: ;

endif

ifdef EXPORTS

export: $(EXPORTS)
	@D=`pwd` ; \
	createdir="${EXPORTBASE}/${EXPDIR}" ;\
	$(mkinstalldirs) $$createdir ; \
	for X in $? ; \
	do echo " Exporting $$X to $$createdir/$$X"; \
	ln -sf $$D/$$X $$createdir/$$X ; \
	done

exportwin32: $(EXPORTS)
	@D=`pwd` ; \
	createdir="${EXPORTBASE}/${EXPDIR}" ;\
	${create_dir_win32} ; \
	for X in $? ; \
	do echo "copy $$D/$$X $$createdir/$$X" ; \
	echo "copy $$D/$$X $$createdir/$$X" >> ${INIT_WIN32} ; \
	done

else

export: ;

exportwin32: ;

endif



ifdef PROGRAM

${PROGRAM}: ${OBJECTS} $(subst -l,${EXPORTBASE}/lib/lib, ${LIBS:=.a})
	${CXX} ${OBJECTS} ${LDFLAGS} ${LIBS} ${EXT_LIBS} ${SOLIBS} -o $@

installprogram: ${PROGRAM}
	@ createdir="${INSTBASE}" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${PROGRAM}" ; \
	echo " $(INSTALL_PROGRAM) $$X $$createdir/$$X"; \
	$(INSTALL_PROGRAM) $$X $$createdir/$$X

else

installprogram: ;

endif

ifdef TOOLS

${TOOLS}: ${OBJECTS} $(subst -l,${EXPORTBASE}/lib/lib, ${LIBS:=.a})
	${CXX} ${OBJECTS} ${LDFLAGS} ${LIBS} ${EXT_LIBS} ${SOLIBS} -o $@

installtools: ${TOOLS}
	@createdir="${INSTBINBASE}/${TOOLSDIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${TOOLS}" ; \
	echo " $(INSTALL_PROGRAM) $$X $$createdir/$$X"; \
	$(INSTALL_PROGRAM) $$X $$createdir/$$X

else

ifdef TOOLSCRIPT

installtools: ${TOOLSCRIPT}
	@createdir="${INSTBINBASE}/${TOOLSDIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${TOOLSCRIPT}" ; \
	echo " $(INSTALL_PROGRAM) $$X $$createdir/$$X"; \
	$(INSTALL_PROGRAM) $$X $$createdir/$$X

else

installtools: ;

endif
endif

ifdef TOOLSDATA

toolsdata: ;

installtoolsdata: $(TOOLSDATA)
	@createdir="${INSTBASE}/${TOOLSDATADIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	for X in $? ; \
	do echo " $(INSTALL_DATA) $$X $$createdir/$$X"; \
	$(INSTALL_DATA) $$X $$createdir/$$X ; \
	done


else 

toolsdata: ;
installtoolsdata: ;

endif


ifdef SOLIBRARY

${SOLIBRARY}: ${OBJECTS}
	${CXX} -shared -o ${SOLIBRARY} ${OBJECTS} ${LIBSPATH} ${LIBS} ${DEBUG_LIBS}
	@D=`pwd` ; \
	createdir="${EXPORTBASE}/lib" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${SOLIBRARY}" ; \
	echo " Exporting $$X to $$createdir/$$X"; \
	ln -sf $$D/$$X $$createdir/$$X


installsolibrary: ${SOLIBRARY}
	@createdir="${INSTLIBBASE}" ; \
	X="${SOLIBRARY}" ;\
	$(mkinstalldirs) $$createdir ; \
	echo " $(INSTALL_DATA) $$X $$createdir/$$X"; \
	$(INSTALL_DATA) $$X $$createdir/$$X

installsolibrarywin32:
	@createdir="runtime/${SOLIBDIR}" ; \
	${create_dir_win32}

else

installsolibrary: ;

installsolibrarywin32: ;

endif

ifdef MODULE

${MODULE}: ${OBJECTS}
	${CXX} -shared -o ${MODULE} ${OBJECTS} ${LIBSPATH} ${LIBS} 
	@D=`pwd` ; \
	createdir="${EXPORTBASE}/${MODULEDIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${MODULE}" ; \
	echo " Exporting $$X to $$createdir/$$X"; \
	ln -sf $$D/$$X $$createdir/$$X


installmodule: ${MODULE}
	@createdir="${INSTBASE}/${MODULEDIR}" ; \
	X="${MODULE}" ;\
	$(mkinstalldirs) $$createdir ; \
	echo " $(INSTALL_DATA) $$X $$createdir/$$X"; \
	$(INSTALL_DATA) $$X $$createdir/$$X

installmodulewin32:
	@createdir="runtime/${MODULEDIR}" ; \
	${create_dir_win32}


else

installmodule: ;

installmodulewin32: ;

endif

ifdef PKGLIST

packagelist:
	@for Pkg in ${PKGLIST} ;\
	do ${MAKE} onepackage PKG=$$Pkg  TORCS_BASE=${TORCS_BASE} MAKE_DEFAULT=${MAKE_DEFAULT};\
	createdir="${PACKAGESBASE}" ;\
	$(mkinstalldirs) $$createdir ; \
	archive="TORCS-${VERSION}-$$Pkg".tgz ;\
	echo "Creating Package $$archive" ;\
	tar -C ${PACKAGEBASE} -co . | gzip -9 > "${PACKAGESBASE}/$$archive" ;\
	rm -rf ${PACKAGEBASE} ;\
	done

else

packagelist: ;

endif

ifdef PKG

PKGFILES = $($(PKG)_PKGFILES)
PKGDIR = $($(PKG)_PKGDIR)

ifeq ($(strip $(PKGFILES)),)
PKGFILES = ""
endif

packagefiles:
	@if [ -n "${PKGFILES}" ];\
	then createdir="${PACKAGEBASE}/${PKGDIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	for Pkg in ${PKGFILES} ; \
	do cp $$Pkg $$createdir/$$Pkg ; \
	echo " Package $$Pkg to $$createdir/$$Pkg"; \
	done ;\
	fi

else

packagefiles: ;

endif

ifdef SPECFILES

installspecfiles:
	@createdir="$(SPECFILESBASE)" ; \
	$(mkinstalldirs) $$createdir ; \
	for spec in $(SPECFILES) ; \
	do cp $$spec $$createdir/$$spec ; \
	echo " Specfile $$spec copied to $$createdir/$$spec" ; \
	done ;

else

installspecfiles: ;

endif

ifdef PKGSUBDIRS

packagedirs:
	@RecurseDirs="${PKGSUBDIRS}" ; \
	RecurseFlags="onepackage PKG=${PKG}" ; \
	${recursedirs}

else

packagedirs: ;

endif

ifdef DATASUBDIRS

instdatadirs:
	@RecurseDirs="${DATASUBDIRS}" ; \
	RecurseFlags="install" ; \
	${recursedirs}

else

instdatadirs: ;

endif

ifdef SHIPSUBDIRS

instshipdirs:
	@RecurseDirs="${SHIPSUBDIRS}" ; \
	RecurseFlags="install" ; \
	${recursedirs}

else

instshipdirs: ;

endif


ifdef EXPINCDIRS

expincdirs: 
	@RecurseDirs="${EXPINCDIRS}" ; \
	RecurseFlags="exports" ; \
	${recursedirs}

expincwin32dirs: 
	@RecurseDirs="${EXPINCDIRS}" ; \
	RecurseFlags="exportswin32" ; \
	${recursedirs}

else

expincdirs: ;

expincwin32dirs: ;

endif



ifdef SUBDIRS

subdirs: 
	@RecurseDirs="${SUBDIRS}" ; \
	RecurseFlags="compil" ; \
	${recursedirs}

cleansubdirs:
	@RecurseDirs="${SUBDIRS}" ; \
	RecurseFlags="cleancompil" ; \
	${recursedirs}

instsubdirs:
	@RecurseDirs="${SUBDIRS}" ; \
	RecurseFlags="install" ; \
	${recursedirs}

specfilesdirs:
	@RecurseDirs="${SUBDIRS}" ; \
	RecurseFlags="specfiles" ; \
	${recursedirs}


else

subdirs: ;
cleansubdirs: ;
instsubdirs: ;
specfilesdirs: ;

endif



ifdef TOOLSUBDIRS

toolsdirs: 
	@RecurseDirs="${TOOLSUBDIRS}" ; \
	RecurseFlags="tools" ; \
	${recursedirs}

cleantoolsdirs:
	@RecurseDirs="${TOOLSUBDIRS}" ; \
	RecurseFlags="cleantools" ; \
	${recursedirs}

insttoolsdirs:
	@RecurseDirs="${TOOLSUBDIRS}" ; \
	RecurseFlags="install" ; \
	${recursedirs}

else

toolsdirs: ;
cleantoolsdirs: ;
insttoolsdirs: ;

endif

ifdef INITSUBDIRS

initsubdirs:
	@RecurseDirs="${INITSUBDIRS}" ; \
	RecurseFlags="init" ; \
	${recursedirs}

endif

#to be done in a better way...
ifdef SRCDOC

info:
	mkdir -p ${DOCBASE}/manual/api
	doxygen ${SOURCEBASE}/doc/torcsdoc.conf

endif


installdirs:
	@if [ -n "${SHIPSUBDIRS}" ] || [ -n "${SUBDIRS}" ] || [ -n "${TOOLSUBDIRS}" ] ; \
	then R=`for I in ${SHIPSUBDIRS} ${SUBDIRS} ${TOOLSUBDIRS} ; \
	do echo $$I ;\
	done | sort -u` ; \
	RecurseDirs="$$R" ; \
	RecurseFlags="install" ; \
	${recursedirs} ; \
	fi

installwin32dirs:
	@if [ -n "${SHIPSUBDIRS}" ] || [ -n "${SUBDIRS}" ] || [ -n "${TOOLSUBDIRS}" ] ; \
	then R=`for I in ${SHIPSUBDIRS} ${SUBDIRS} ${TOOLSUBDIRS} ; \
	do echo $$I ;\
	done | sort -u` ; \
	RecurseDirs="$$R" ; \
	RecurseFlags="installwin32" ; \
	${recursedirs} ; \
	fi

installdatadirs:
	@if [ -n "${DATASUBDIRS}" ] ; \
	then R=`for I in ${DATASUBDIRS} ; \
	do echo $$I ;\
	done | sort -u` ; \
	RecurseDirs="$$R" ; \
	RecurseFlags="datainstall" ; \
	${recursedirs} ; \
	fi

installshipdirs:
	@if [ -n "${SHIPSUBDIRS}" ] ; \
	then R=`for I in ${SHIPSUBDIRS} ; \
	do echo $$I ;\
	done | sort -u` ; \
	RecurseDirs="$$R" ; \
	RecurseFlags="installships" ; \
	${recursedirs} ; \
	fi

installshipwin32dirs:
	@if [ -n "${SHIPSUBDIRS}" ] ; \
	then R=`for I in ${SHIPSUBDIRS} ; \
	do echo $$I ;\
	done | sort -u` ; \
	RecurseDirs="$$R" ; \
	RecurseFlags="installshipswin32" ; \
	${recursedirs} ; \
	fi

