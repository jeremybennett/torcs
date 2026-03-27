/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#pragma once
#ifdef WIN32
  #include <windows.h>
  #include <GL/gl.h>
  #define GL_GLEXT_PROTOTYPES
  #include <GL/glext.h>
#else
  #define GL_GLEXT_PROTOTYPES
  #include <GL/gl.h>
  #include <GL/glext.h>
#endif
