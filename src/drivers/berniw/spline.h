/***************************************************************************

    file                 : spline.h
    created              : Mon Apr 17 13:51:00 CET 2000
    copyright            : (C) 2000 by Bernhard Wymann
    email                : berniw@bluewin.ch
    version              : $Id$

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _SPLINE_H_
#define _SPLINE_H_

#include <tgf.h>

/* solves tridiagonal matrix in linear time O(n) with Given's Rotations */
extern void tridiagonal(int dim, tdble * c, tdble * a, tdble * b, tdble * x);

/* compute the slopes of the spline points with periodic constraints */
extern void slopesp(int dim, tdble * x, tdble * y, tdble * ys);

/* compute the slopes of the spline points with natural constraints */
extern void slopesn(int dim, tdble * x, tdble * y, tdble * ys);

/* compute the slopes for 2-dim curve, sums euclidian distances as parameter, periodic */
extern void parametricslopesp(int dim, tdble * x, tdble * y, tdble * xs, tdble * ys, tdble * s);

/* compute the slopes for 2-dim curve, sums euclidian distances as parameter, natural */
extern void parametricslopesn(int dim, tdble * x, tdble * y, tdble * xs, tdble * ys, tdble * s);

/* compute the y value for a given z */
extern tdble spline(int dim, tdble z, tdble * x, tdble * y, tdble * ys);

#endif // _SPLINE_H_

