/***************************************************************************

    file                 : spline.cpp
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

#include <tgf.h>
#include <math.h>
#include "spline.h"

/*	solving tridiagonal nxn matrix with Givens-Rotations in linear time O(n)
	[ a1 b1 0   0   0 .......... ]
	[ c1 a2 b2  0   0 ...........]
	[ 0  c2 a3 b3   0 ...........]
	[ ...........................]
	[ ................... b(n-1) ]
	[ ................ c(n-1) an ]
*/

void tridiagonal(int dim, tdble * c, tdble * a, tdble * b, tdble * x)
{
	tdble co, si, h, t;

	dim--;
	b[dim] = 0;
	for (int i = 0; i < dim; i++) {
		if (c[i] != 0) {
			t = a[i] / c[i]; si = 1 / sqrt(1 + t*t); co = t * si;
			a[i] = a[i]*co + c[i]*si; h = b[i];
			b[i] = h*co + a[i+1]*si; a[i+1] = -h*si + a[i+1]*co;
			c[i] = b[i+1]*si; b[i+1] = b[i+1]*co;
			h = x[i]; x[i] = h*co + x[i+1]*si;
			x[i+1] = -h*si + x[i+1]*co;
		}
	}
	x[dim] = x[dim] / a[dim]; x[dim-1] = (x[dim-1] - b[dim-1]*x[dim]) / a[dim-1];
	for (int i = dim - 2; i >= 0; i--) {
		x[i] = (x[i] - b[i]*x[i+1] - c[i]*x[i+2]) / a[i];
	}
}

/* compute the slopes of the spline points with periodic constraints */
void slopesp(int dim, tdble * x, tdble * y, tdble * ys)
{
	tdble * a, * b, * c, * d, * h, * u, * v, factor;

	a = (tdble *) malloc(sizeof(tdble)*dim);
	b = (tdble *) malloc(sizeof(tdble)*dim);
	c = (tdble *) malloc(sizeof(tdble)*dim);
	d = (tdble *) malloc(sizeof(tdble)*dim);
	h = (tdble *) malloc(sizeof(tdble)*dim);
	u = (tdble *) malloc(sizeof(tdble)*dim);
	v = (tdble *) malloc(sizeof(tdble)*dim);

	dim--;
	for (int i = 0; i < dim; i++) {
		h[i] = x[i+1] - x[i];
		d[i] = (y[i+1] - y[i]) / (h[i]*h[i]);
	}
	for (int i = 1; i < dim; i++) {
		a[i] = 2 / h[i-1] + 2 / h[i];
		b[i] = 1 / h[i];
		c[i] = b[i];
		ys[i] = 3 * (d[i] + d[i-1]); 		
	}
	b[0] = 1 / h[0]; c[0] = b[0]; a[0] = (2*b[0] + 1/h[dim-1]);
	a[dim-1] = 2/h[dim-2] + 1/h[dim-1];
	for (int i = 1;  i < dim; i++) {
		u[i] = 0; v[i] = 3 * (d[i] - d[i-1]);
	}
	u[0] = 1; u[dim-1] = 1; v[0] = 3 * (d[0] - d[dim-1]);
	tridiagonal(dim, c, a, b, u);
	tridiagonal(dim, c, a, b, v);
	factor = (v[0]+v[dim-1]) / (u[0]+u[dim-1]+h[dim-1]);
	for (int i = 0; i < dim; i++) {
		ys[i] = v[i] - factor*u[i];
	}
	ys[dim] = ys[0];
	free(a); free(b); free(c); free(d); free(h); free(u); free(v);
}

/* compute the slopes of the spline points with natural constraints */
void slopesn(int dim, tdble * x, tdble * y, tdble * ys)
{
	tdble * a, * b, * c, * d, * h;

	a = (tdble *) malloc(sizeof(tdble)*dim);
	b = (tdble *) malloc(sizeof(tdble)*dim);
	c = (tdble *) malloc(sizeof(tdble)*dim);
	d = (tdble *) malloc(sizeof(tdble)*dim);
	h = (tdble *) malloc(sizeof(tdble)*dim);
	
	dim--;
	for (int i = 0; i < dim; i++) {
		h[i] = x[i+1] - x[i];
		d[i] = (y[i+1] - y[i]) / (h[i]*h[i]);
	}
	for (int i = 1; i < dim; i++) {
		a[i] = 2 / h[i-1] + 2 / h[i];
		b[i] = 1 / h[i];
		c[i] = b[i];
		ys[i] = 3 * (d[i] + d[i-1]); 		
	}
	b[0] = 1 / h[0]; c[0] = b[0]; a[0] = 2*b[0];
	a[dim] = 2/h[dim-1]; ys[0] = 3*d[0]; ys[dim] = 3*d[dim-1];
	tridiagonal(dim, c, a, b, ys);
	free(a); free(b); free(c); free(d); free(h);
}

/* compute the slopes for 2-dim curve, sums euclidian distances as parameter, periodic */	
void parametricslopesp(int dim, tdble * x, tdble * y, tdble * xs, tdble * ys, tdble * s)
{
	s[0] = 0;
	for (int i = 1; i < dim; i++) {
		s[i] = s[i-1] + sqrt((x[i]-x[i-1])*(x[i]-x[i-1]) + (y[i]-y[i-1])*(y[i]-y[i-1]));
	}
	slopesp(dim, s, x, xs);
	slopesp(dim, s, y, ys);
}

void parametricslopesn(int dim, tdble * x, tdble * y, tdble * xs, tdble * ys, tdble * s)
{
	s[0] = 0;
	for (int i = 1; i < dim; i++) {
		s[i] = s[i-1] + sqrt((x[i]-x[i-1])*(x[i]-x[i-1]) + (y[i]-y[i-1])*(y[i]-y[i-1]));
	}
	slopesn(dim, s, x, xs);
	slopesn(dim, s, y, ys);
}

/* compute the y value for a given z */
tdble spline(int dim, tdble z, tdble * x, tdble * y, tdble * ys)
{
	int i, a, b;
	tdble t, a0, a1, a2, a3, h;

	a = 0; b = dim-1;
	do {
		i = (a + b) / 2;
		if (x[i] <= z) a = i; else b = i;
	} while ((a + 1) != b);
    i = a; h = x[i+1] - x[i]; t = (z-x[i]) / h;
	a0 = y[i]; a1 = y[i+1] - a0; a2 = a1 - h*ys[i];
	a3 = h * ys[i+1] - a1; a3 -= a2;
	return a0 + (a1 + (a2 + a3*t) * (t-1))*t;
}
