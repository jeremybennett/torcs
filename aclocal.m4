dnl aclocal.m4 generated automatically by aclocal 1.4

dnl Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY, to the extent permitted by law; without
dnl even the implied warranty of MERCHANTABILITY or FITNESS FOR A
dnl PARTICULAR PURPOSE.





# CHECK FOR COMPILERS

AC_DEFUN(AC_CHECK_COMPILERS,
[
  AC_ARG_ENABLE(debug,[  --enable-debug          creates debugging code [default=no]],
  [
   if test $enableval = "no"; dnl
     then ac_use_debug_code="no"
     else ac_use_debug_code="yes"
   fi
  ], [ac_use_debug_code="no"])

  dnl this was AC_PROG_CC. I had to include it manualy, since I had to patch it
  AC_MSG_CHECKING(for a C-Compiler)
  dnl if there is one, print out. if not, don't matter
  AC_MSG_RESULT($CC)

  if test -z "$CC"; then AC_CHECK_PROG(CC, gcc, gcc) fi
  if test -z "$CC"; then AC_CHECK_PROG(CC, cc, cc, , , /usr/ucb/cc) fi
  if test -z "$CC"; then AC_CHECK_PROG(CC, xlc, xlc) fi
  test -z "$CC" && AC_MSG_ERROR([no acceptable cc found in \$PATH])

  AC_PROG_CC_WORKS
  AC_PROG_CC_GNU

  if test $ac_cv_prog_gcc = yes; then
    GCC=yes
  else
    GCC=
  fi

  if test -z "$CFLAGS2"; then
    if test "$ac_use_debug_code" = "yes"; then
      AC_PROG_CC_G
      if test $ac_cv_prog_cc_g = yes; then
        CFLAGS="-g -DDEBUG -DDEBUG_OUT"
      fi
    else
      if test "$GCC" = "yes"; then
        CFLAGS="-O3 -fstrength-reduce -ffast-math -fomit-frame-pointer"
      else
        CFLAGS=""
      fi
    fi

    if test "$GCC" = "yes"; then
     CFLAGS="$CFLAGS -ansi -Wall -Wstrict-prototypes"
    fi

  fi

  if test -z "$LDFLAGS" && test "$ac_use_debug_code" = "no" && test "$GCC" = "yes"; then
     LDFLAGS="-s"
  fi


dnl this is AC_PROG_CPP. I had to include it here, since autoconf checks
dnl dependecies between AC_PROG_CPP and AC_PROG_CC (or is it automake?)

  AC_MSG_CHECKING(how to run the C preprocessor)
  # On Suns, sometimes $CPP names a directory.
  if test -n "$CPP" && test -d "$CPP"; then
    CPP=
  fi
  if test -z "$CPP"; then
  AC_CACHE_VAL(ac_cv_prog_CPP,
  [  # This must be in double quotes, not single quotes, because CPP may get
    # substituted into the Makefile and "${CC-cc}" will confuse make.
    CPP="${CC-cc} -E"
    # On the NeXT, cc -E runs the code through the compiler's parser,
    # not just through cpp.
    dnl Use a header file that comes with gcc, so configuring glibc
    dnl with a fresh cross-compiler works.
    AC_TRY_CPP([#include <assert.h>
    Syntax Error], ,
    CPP="${CC-cc} -E -traditional-cpp"
    AC_TRY_CPP([#include <assert.h>
    Syntax Error], , CPP=/lib/cpp))
    ac_cv_prog_CPP="$CPP"])dnl
    CPP="$ac_cv_prog_CPP"
  else
    ac_cv_prog_CPP="$CPP"
  fi
  AC_MSG_RESULT($CPP)
  AC_SUBST(CPP)dnl


  AC_MSG_CHECKING(for a C++-Compiler)
  dnl if there is one, print out. if not, don't matter
  AC_MSG_RESULT($CXX)

  if test -z "$CXX"; then AC_CHECK_PROG(CXX, g++, g++) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, CC, CC) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, xlC, xlC) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, DCC, DCC) fi
  test -z "$CXX" && AC_MSG_ERROR([no acceptable C++-compiler found in \$PATH])

  AC_PROG_CXX_WORKS
  AC_PROG_CXX_GNU

  if test $ac_cv_prog_gxx = yes; then
    GXX=yes
  else
    AC_MSG_CHECKING(whether we are using SPARC CC)
    GXX=
    cat > conftest.C << EOF
#ifdef __SUNPRO_CC
   yes;
#endif
EOF


    ac_try="$CXX -E conftest.C"
    if { (eval echo configure:__online__: \"$ac_try\") 1>&5; (eval $ac_try) 2>&5; } | egrep yes >/dev/null 2>&1; then
      ac_cv_prog_CC=yes
    else
      ac_cv_prog_CC=no
    fi
    AC_MSG_RESULT($ac_cv_prog_CC)
  fi

  if test -z "$CXXFLAGS"; then
    if test "$ac_use_debug_code" = "yes"; then
      AC_PROG_CXX_G
      if test $ac_cv_prog_cxx_g = yes; then
        CXXFLAGS="-g -DDEBUG -DDEBUG_OUT"
      fi
      if test "$ac_cv_prog_CC" = "yes"; then
        CXXFLAGS="$CXXFLAGS -pto"
      fi
    else
      if test "$GXX" = "yes"; then
         CXXFLAGS="-O3 -fstrength-reduce -ffast-math -fomit-frame-pointer"
      else
         if test "$ac_cv_prog_CC" = "yes"; then
            CXXFLAGS="-pto -O2"
         else
            CXXFLAGS=""
         fi
      fi
    fi

    if test "$GXX" = "yes"; then
       CXXFLAGS="$CXXFLAGS -ansi -Wall -Wstrict-prototypes"
    fi
  fi

])


AC_DEFUN(AC_FIND_FILE,
[
$3=NO
for i in $2;
do
  for j in $1;
  do
    if test -r "$i/$j"; then
      $3=$i
      break 2
    fi
  done
done
])

AC_DEFUN(TORCS_PATH_X,
[
AC_MSG_CHECKING(for X)
AC_CACHE_VAL(ac_cv_have_x,
[# One or both of the vars are not set, and there is no cached value.
ac_x_includes=NO ac_x_libraries=NO
AC_PATH_X_DIRECT
AC_PATH_X_XMKMF
if test "$ac_x_includes" = NO || test "$ac_x_libraries" = NO; then
  AC_MSG_ERROR([Can't find X includes. Please check your installation and add the correct paths!])
else
  # Record where we found X for the cache.
  ac_cv_have_x="have_x=yes \
                ac_x_includes=$ac_x_includes ac_x_libraries=$ac_x_libraries"
fi])dnl
eval "$ac_cv_have_x"

if test "$have_x" != yes; then
  AC_MSG_RESULT($have_x)
  no_x=yes
else
  # If each of the values was on the command line, it overrides each guess.
  test "x$x_includes" = xNONE && x_includes=$ac_x_includes
  test "x$x_libraries" = xNONE && x_libraries=$ac_x_libraries

  # don't set -I/usr/X11R6/include please. It's boring. /S.Rehel
  # IRIX test doesn't support -ef ! Aaah GNU ... Aah linux!
  #
  xdir1=`cd $x_includes/X11 && /bin/pwd`
  xdir2=`cd /usr/include/X11 && /bin/pwd`
  if test "$xdir1" = "$xdir2" ; then
    x_includes=/usr/include
  fi

  # Update the cache value to reflect the command line values.
  ac_cv_have_x="have_x=yes \
                ac_x_includes=$x_includes ac_x_libraries=$x_libraries"
  AC_MSG_RESULT([libraries $x_libraries, headers $x_includes])

  CPPFLAGS="$CPPFLAGS -L$x_libraries"
fi

if test -z "$x_includes" || \
   test "$x_includes" = "/usr/include" || \
   test "x$x_includes" = xNONE; then
  X_INCLUDES=""
  x_includes="."; dnl better than nothing :-
 else
  X_INCLUDES="-I$x_includes"
fi

if test -z "$x_libraries" || test "$x_libraries" = xNONE; then
  X_LDFLAGS=""
  x_libraries="/usr/lib"; dnl better than nothing :-
  all_libraries=""
 else
  X_LDFLAGS="-L$x_libraries"
  all_libraries=$X_LDFLAGS
fi

AC_SUBST(X_INCLUDES)
AC_SUBST(X_LDFLAGS)
all_includes=$X_INCLUDES
])



AC_DEFUN(AC_PATH_GLUT,
[
AC_MSG_CHECKING([for glut])
ac_glut_includes=NO ac_glut_libraries=NO
glut_libraries=""
glut_includes=""
AC_ARG_WITH(glut-dir,
    [  --with-glut-dir         where the root of glut is installed ],
    [  ac_glut_includes="$withval"/include
       ac_glut_libraries="$withval"/lib/glut
    ])

AC_ARG_WITH(glut-includes,
    [  --with-glut-includes    where the glut includes are. ],
    [
       ac_glut_includes="$withval"
    ])

AC_ARG_WITH(glut-libraries,
    [  --with-glut-libraries   where the glut library is installed.],
    [
       ac_glut_libraries="$withval"
    ])

if test "$ac_glut_includes" = NO || test "$ac_glut_libraries" = NO; then

AC_CACHE_VAL(ac_cv_have_glut,
[#try to guess glut locations


glut_incdirs="$ac_glut_includes /usr/include /usr/local/include /usr/include/Mesa /usr/local/include/Mesa /usr/glut/include /usr/local/glut/include $HOME/glut/include $HOME/Mesa/include $GLUT_INC $gl_includes /usr/X11R6/include"
test -n "$GLUTDIR" && glut_incdirs="$GLUTDIR/include $GLUTDIR $glut_incdirs"
AC_FIND_FILE(GL/glut.h, $glut_incdirs, glut_incdir)
ac_glut_includes=$glut_incdir

glut_libdirs="$ac_glut_libraries /usr/lib /usr/local/lib /usr/lib/Mesa /usr/local/lib/Mesa /usr/lib/Mesa-3.0 /usr/local/lib/Mesa-3.0 /usr/glut/lib/glut /usr/local/glut/lib/glut $HOME/glut/lib/glut $HOME/Mesa/lib $GLUTLIB $gl_libraries /usr/X11R6/lib/"
test -n "$GLUTDIR" && glut_libdirs="$GLUTDIR/lib/glut $GLUTDIR $glut_libdirs"
AC_FIND_FILE(libglut.so libglut.so.3 libglut.a libglut.sl, $glut_libdirs, glut_libdir)
ac_glut_libraries=$glut_libdir

ac_cxxflags_safe=$CXXFLAGS
ac_ldflags_safe=$LDFLAGS
ac_libs_safe=$LIBS

CXXFLAGS="$CXXFLAGS -I$glut_incdir -I$gl_includes"
LDFLAGS="-L$glut_libdir"
LIBS="-lglut -L$gl_libraries -l${GL_LIBNAME}GL -l${GL_LIBNAME}GLU $LIBSOCKET $LIBS"

AC_LANG_CPLUSPLUS
cat > conftest.$ac_ext <<EOF
#include "confdefs.h"
#include "GL/glut.h"
int main( int argc, char** argv ) {
  glutInit(&argc, argv);
  return 0;
}
EOF

if AC_TRY_EVAL(ac_link) && test -s conftest; then
  rm -f conftest*
else
  echo "configure: failed program was:" >&AC_FD_CC
  cat conftest.$ac_ext >&AC_FD_CC
  ac_glut_libraries="NO"
fi
rm -f conftest*
CXXFLAGS=$ac_cxxflags_safe
LDFLAGS=$ac_ldflags_safe
LIBS=$ac_libs_safe

if test "$ac_glut_includes" = NO || test "$ac_glut_libraries" = NO; then
  ac_cv_have_glut="have_glut=no"
  ac_glut_notfound=""
  if test "$ac_glut_includes" = NO; then
    if test "$ac_glut_libraries" = NO; then
      ac_glut_notfound="(headers and libraries)";
    else
      ac_glut_notfound="(headers)";
    fi
  else
    ac_glut_notfound="(libraries)";
  fi

  AC_MSG_ERROR([glut $ac_glut_notfound not found.]);
else
  have_glut="yes"
fi
])
else
  have_glut="yes"
fi

eval "$ac_cv_have_glut"

if test "$have_glut" != yes; then
  AC_MSG_ERROR([$have_glut]);
else
  ac_cv_have_glut="have_glut=yes \
    ac_glut_includes=$ac_glut_includes ac_glut_libraries=$ac_glut_libraries"
  AC_MSG_RESULT([libraries $ac_glut_libraries, headers $ac_glut_includes])

  glut_libraries=$ac_glut_libraries
  glut_includes=$ac_glut_includes
fi

AC_SUBST(glut_libraries)
AC_SUBST(glut_includes)

if test "$glut_includes" = "$x_includes" || \
   test "$glut_includes" = "/usr/include" || \
   test "$glut_includes" = "/usr/local/include" || \
   test -z "$glut_includes"; then
 GLUT_INCLUDES="";
else
 GLUT_INCLUDES="-I$glut_includes"
 all_includes="$GLUT_INCLUDES $all_includes"
fi

if test "$glut_libraries" = "$x_libraries" || \
   test "$glut_libraries" = "/usr/lib" || \
   test "$glut_libraries" = "/usr/local/lib" || \
   test -z "$glut_libraries"; then
 GLUT_LDFLAGS=""
else
 GLUT_LDFLAGS="-L$glut_libraries"
 all_libraries="$GLUT_LDFLAGS $all_libraries"
fi

AC_SUBST(GLUT_INCLUDES)
AC_SUBST(GLUT_LDFLAGS)
])


AC_DEFUN(AC_HAVE_GL,
[
AC_MSG_CHECKING([for GL])
ac_gl_includes=NO
ac_gl_libraries=NO
gl_libraries=""
gl_includes=""
AC_ARG_WITH(gl-dir,
    [  --with-gl-dir           where the root of OpenGL is installed ],
    [  ac_gl_includes="$withval"/include
       ac_gl_libraries="$withval"/lib
    ])

AC_ARG_WITH(gl-includes,
    [  --with-gl-includes      where the OpenGL includes are. ],
    [
       ac_gl_includes="$withval"
    ])

AC_ARG_WITH(gl-libraries,
    [  --with-gl-libraries     where the OpenGL library is installed.],
    [  ac_gl_libraries="$withval"
    ])

if test "$ac_gl_includes" = NO || test "$ac_gl_libraries" = NO; then

AC_CACHE_VAL(ac_cv_have_gl,
[#try to guess gl locations

gl_incdirs="$ac_gl_includes \
            /usr/include \
            /usr/local/include \
            /usr/local/Mesa/include \
            $HOME/Mesa/include \
	    /usr/X11R6/include \
            $GL_INC"
test -n "$GLDIR" && gl_incdirs="$GLDIR/include $GLDIR $gl_incdirs"
AC_FIND_FILE(GL/gl.h, $gl_incdirs, gl_incdir)
ac_gl_includes=$gl_incdir

gl_libdirs="$ac_gl_libraries \
            /usr/lib \
            /usr/local/lib \
            /usr/lib/Mesa \
            /usr/local/Mesa/lib \
            /usr/local/lib/Mesa \
            $HOME/Mesa/lib \
            /usr/X11R6/lib/ \
            $GLLIB"
test -n "$GLDIR" && gl_libdirs="$GLDIR/lib $GLDIR $gl_libdirs"

GL_LIBNAME=""
AC_FIND_FILE(libGL.so libGL.a, $gl_libdirs, gl_libdir)
if test "$gl_libdir" = NO ; then
  AC_FIND_FILE(libMesaGL.so libMesaGL.a, $gl_libdirs, gl_libdir)
  ac_gl_libraries=$gl_libdir
  GL_LIBNAME="Mesa"
else
  ac_gl_libraries=$gl_libdir
  GL_LIBNAME=""
fi

AC_FIND_FILE(libGL.so libMesaGL.so libGL.a libMesaGL.a, $gl_libdirs, gl_libdir)
ac_gl_libraries=$gl_libdir

ac_cxxflags_safe=$CXXFLAGS
ac_ldflags_safe=$LDFLAGS
ac_libs_safe=$LIBS

CXXFLAGS="$CXXFLAGS -I$gl_incdir"
LDFLAGS="-L$gl_libdir"
LIBS="-lGL $X_LDFLAGS $LIBS"

AC_LANG_CPLUSPLUS
cat > conftest.$ac_ext <<EOF
#include "confdefs.h"
#include "GL/gl.h"
int main() {
  glEnd();
  return 0;
}
EOF

if AC_TRY_EVAL(ac_link) && test -s conftest; then
  rm -f conftest*
else
  rm -f conftest*
  LIBS="$ac_libs_safe -lMesaGL $X_LDFLAGS -lX11 -lXext -lm"

cat > conftest.$ac_ext <<EOF
#include "confdefs.h"
#include "GL/gl.h"
int main() {
  glEnd();
  return 0;
}
EOF

  if AC_TRY_EVAL(ac_link) && test -s conftest; then
    rm -f conftest*
   else
    echo "configure: failed program was:" >&AC_FD_CC
    cat conftest.$ac_ext >&AC_FD_CC
    ac_gl_libraries="NO"
   fi
fi

rm -f conftest*
CXXFLAGS=$ac_cxxflags_safe
LDFLAGS=$ac_ldflags_safe
LIBS=$ac_libs_safe

if test "$ac_gl_includes" = NO || test "$ac_gl_libraries" = NO; then
  ac_cv_have_gl="have_gl=no"
  ac_gl_notfound=""
  if test "$ac_gl_includes" = NO; then
    if test "$ac_gl_libraries" = NO; then
      ac_gl_notfound="(headers and libraries)";
    else
      ac_gl_notfound="(headers)";
    fi
  else
    ac_gl_notfound="(libraries)";
  fi

  AC_MSG_ERROR([OpenGL $ac_gl_notfound not found. Please check your installation! ]);
else
  have_gl="yes"
fi
])
else
  have_gl="yes"
fi

eval "$ac_cv_have_gl"

if test "$have_gl" != yes; then
  AC_MSG_RESULT([$have_gl]);
else
  ac_cv_have_gl="have_gl=yes \
    ac_gl_includes=$ac_gl_includes ac_gl_libraries=$ac_gl_libraries"
  AC_MSG_RESULT([libraries $ac_gl_libraries/lib${GL_LIBNAME}GL*, headers $ac_gl_includes/GL])

  gl_libraries=$ac_gl_libraries
  gl_includes=$ac_gl_includes
fi

AC_SUBST(gl_libraries)
AC_SUBST(gl_includes)

if test "$gl_includes" = "$x_includes" || \
   test "$gl_includes" = "/usr/include" || \
   test "$gl_includes" = "/usr/local/include" || \
   test -z "$gl_includes"; then
 GL_INCLUDES="";
else
 GL_INCLUDES="-I$gl_includes"
 all_includes="$GL_INCLUDES $all_includes"
fi

if test "$gl_libraries" = "$x_libraries" || \
   test "$gl_libraries" = "/usr/lib" || \
   test "$gl_libraries" = "/usr/local/lib" || \
   test -z "$gl_libraries"; then
 GL_LDFLAGS=""
else
 GL_LDFLAGS="-L$gl_libraries"
 all_libraries="$GL_LDFLAGS $all_libraries"
fi

AC_SUBST(GL_INCLUDES)
AC_SUBST(GL_LDFLAGS)
AC_SUBST(GL_LIBNAME)
])


# Do all the work for Automake.  This macro actually does too much --
# some checks are only needed if your package does certain things.
# But this isn't really a big deal.

# serial 1

dnl Usage:
dnl AM_INIT_AUTOMAKE(package,version, [no-define])

AC_DEFUN(AM_INIT_AUTOMAKE,
[AC_REQUIRE([AC_PROG_INSTALL])
PACKAGE=[$1]
AC_SUBST(PACKAGE)
VERSION=[$2]
AC_SUBST(VERSION)
dnl test to see if srcdir already configured
if test "`cd $srcdir && pwd`" != "`pwd`" && test -f $srcdir/config.status; then
  AC_MSG_ERROR([source directory already configured; run "make distclean" there first])
fi
ifelse([$3],,
AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [Name of package])
AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [Version number of package]))
AC_REQUIRE([AM_SANITY_CHECK])
AC_REQUIRE([AC_ARG_PROGRAM])
dnl FIXME This is truly gross.
missing_dir=`cd $ac_aux_dir && pwd`
AM_MISSING_PROG(ACLOCAL, aclocal, $missing_dir)
AM_MISSING_PROG(AUTOCONF, autoconf, $missing_dir)
AM_MISSING_PROG(AUTOMAKE, automake, $missing_dir)
AM_MISSING_PROG(AUTOHEADER, autoheader, $missing_dir)
AM_MISSING_PROG(MAKEINFO, makeinfo, $missing_dir)
AC_REQUIRE([AC_PROG_MAKE_SET])])

#
# Check to make sure that the build environment is sane.
#

AC_DEFUN(AM_SANITY_CHECK,
[AC_MSG_CHECKING([whether build environment is sane])
# Just in case
sleep 1
echo timestamp > conftestfile
# Do `set' in a subshell so we don't clobber the current shell's
# arguments.  Must try -L first in case configure is actually a
# symlink; some systems play weird games with the mod time of symlinks
# (eg FreeBSD returns the mod time of the symlink's containing
# directory).
if (
   set X `ls -Lt $srcdir/configure conftestfile 2> /dev/null`
   if test "[$]*" = "X"; then
      # -L didn't work.
      set X `ls -t $srcdir/configure conftestfile`
   fi
   if test "[$]*" != "X $srcdir/configure conftestfile" \
      && test "[$]*" != "X conftestfile $srcdir/configure"; then

      # If neither matched, then we have a broken ls.  This can happen
      # if, for instance, CONFIG_SHELL is bash and it inherits a
      # broken ls alias from the environment.  This has actually
      # happened.  Such a system could not be considered "sane".
      AC_MSG_ERROR([ls -t appears to fail.  Make sure there is not a broken
alias in your environment])
   fi

   test "[$]2" = conftestfile
   )
then
   # Ok.
   :
else
   AC_MSG_ERROR([newly created file is older than distributed files!
Check your system clock])
fi
rm -f conftest*
AC_MSG_RESULT(yes)])

dnl AM_MISSING_PROG(NAME, PROGRAM, DIRECTORY)
dnl The program must properly implement --version.
AC_DEFUN(AM_MISSING_PROG,
[AC_MSG_CHECKING(for working $2)
# Run test in a subshell; some versions of sh will print an error if
# an executable is not found, even if stderr is redirected.
# Redirect stdin to placate older versions of autoconf.  Sigh.
if ($2 --version) < /dev/null > /dev/null 2>&1; then
   $1=$2
   AC_MSG_RESULT(found)
else
   $1="$3/missing $2"
   AC_MSG_RESULT(missing)
fi
AC_SUBST($1)])

