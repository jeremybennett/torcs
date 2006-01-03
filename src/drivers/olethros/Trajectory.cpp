// -*- Mode: c++ -*-
// copyright (c) 2006 by Christos Dimitrakakis <dimitrak@idiap.ch>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <list>
#include <vector>
#include "Trajectory.h"


Point Trajectory::GetPoint (Segment& s, float w)
{
    float v = 1.0f - w;
    return Point (w*s.left.x + v*s.right.x,
                  w*s.left.y + v*s.right.y,
                  w*s.left.z + v*s.right.z);
}

void Trajectory::Optimise(SegmentList track, int max_iter, float alpha)
{
    int N = track.size();
    w.resize(N);
    dw.resize(N);
    dw2.resize(N);
    indices.resize(N);

    // initialise vectors
    for (int i=0; i<N; ++i) {
        w[i] = 0.5f;
        dw2[i] = 1.0f;
        indices[i] = i;
    }

    // Shuffle thoroughly
    for (int i=0; i<N-1; ++i) {
        int z = rand()%(N-i);
        int tmp = indices[i];
        indices[i] = indices[z+i];
        indices[z+i] = tmp;
    }

    float prevC = 0.0;
    float Z = 10.0f;
    float lambda = 0.9;

    for (int iter=0; iter<max_iter; iter++) {
        float C = 0.0f;
        float P = 0.0f;
        float dCdw2 = 0.0f;
        float EdCdw = 0.0f;

        float direction = 0.0;
        for (int j=0; j<N-1; ++j) {
            int i = indices[j];//rand()%(N-3) + 3;
            int i_p3 = i - 3;
            if (i_p3 < 0) i_p3 +=N;
            int i_p2 = i - 2;
            if (i_p2 < 0) i_p2 +=N;
            int i_p1 = i - 1;
            if (i_p1 < 0) i_p1 +=N;
            int i_n3 = (i + 3)%N;
            int i_n2 = (i + 2)%N;
            int i_n1 = (i + 1)%N;
            Segment s_prv3 = track[i_p3];
            Segment s_prv2 = track[i_p2];
            Segment s_prv = track[i_p1];
            Segment s_cur = track[i];
            Segment s_nxt = track[i_n1];
            Segment s_nxt2 = track[i_n2];
            Point prv3 = GetPoint(track[i_p3], w[i_p3]);
            Point prv2 = GetPoint(track[i_p2], w[i_p2]);
            Point prv = GetPoint(track[i_p1], w[i_p1]);
            Point cur = GetPoint(track[i], w[i]);
            Point nxt = GetPoint(track[i_n1], w[i_n1]);
            Point nxt2 = GetPoint(track[i_n2], w[i_n2]);
            Point u_prv2 = prv2 - prv3;
            Point u_prv = prv - prv2;
            Point u_cur = cur - prv;
            Point u_nxt = nxt - cur;
            Point u_nxt2 = nxt2 - nxt;
            u_prv.Normalise();
            u_cur.Normalise();
            u_nxt.Normalise();
            u_nxt2.Normalise();
            float l_prv2 = (prv2 - prv3).Length();
            float l_prv = (prv - prv2).Length();
            float l_cur = (cur - prv).Length();
            float l_nxt = (nxt - cur).Length();
#if 1
            Point a_prv = (u_cur - u_prv)/l_prv;
            Point a_cur = (u_nxt - u_cur)/l_cur;
            Point a_nxt = (u_nxt2 - u_nxt)/l_nxt;
#else
            Point a_prv = (u_prv - u_prv2)/l_prv2;
            Point a_cur = (u_cur - u_prv)/l_prv;
            Point a_nxt = (u_nxt - u_cur)/l_cur;
#endif

            C += a_prv.Length()*a_prv.Length()
                + a_cur.Length()*a_cur.Length()
                + a_nxt.Length()*a_nxt.Length();
            float dCdw = 0.0;

            if (1) {
                // Done only for a_cur, ignoring other costs.
                {
                    Point lr = s_cur.left - s_cur.right;
                    Point d = cur - prv;
                    float dnorm2 = d.x*d.x + d.y*d.y;
                    float dnorm = sqrt(dnorm2);
                    float dxdynorm = d.x * d.y / dnorm;
                    dCdw += a_cur.x * lr.x * (dnorm + d.x/dnorm + dxdynorm);
                    dCdw += a_cur.y * lr.y * (dnorm + d.y/dnorm + dxdynorm);
                }
                {
                    Point lr = s_cur.left - s_cur.right;
                    Point d = nxt - cur;
                    float dnorm2 = d.x*d.x + d.y*d.y;
                    float dnorm = sqrt(dnorm2);
                    float dxdynorm = d.x * d.y / dnorm;
                    dCdw += a_cur.x * lr.x * (dnorm + d.x/dnorm + dxdynorm);
                    dCdw += a_cur.y * lr.y * (dnorm + d.y/dnorm + dxdynorm);
                }
            }

            if (1) {
                {
                    Point lr = s_cur.left - s_cur.right;
                    Point d = nxt - cur;
                    float dnorm2 = d.x*d.x + d.y*d.y;
                    float dnorm = sqrt(dnorm2);
                    float dxdynorm = d.x * d.y / dnorm;
                    dCdw -= a_nxt.x * lr.x * (dnorm + d.x/dnorm + dxdynorm);
                    dCdw -= a_nxt.y * lr.y * (dnorm + d.y/dnorm + dxdynorm);
                }
            }

            if (1) {
                {
                    Point lr = s_cur.left - s_cur.right;
                    Point d = cur - prv;
                    float dnorm2 = d.x*d.x + d.y*d.y;
                    float dnorm = sqrt(dnorm2);
                    float dxdynorm = d.x * d.y / dnorm;
                    dCdw -= a_prv.x * lr.x * (dnorm + d.x/dnorm + dxdynorm);
                    dCdw -= a_prv.y * lr.y * (dnorm + d.y/dnorm + dxdynorm);
                }
            }
            float K = 10.0;
            float penalty = 0.0;//K*(0.5f - w[i])*(exp(fabs(0.5-w[i]))-1);
            if (1) {
                float b = 0.05;
                if (w[i] < b) {
                    penalty += K*(b - w[i]);
                } else if (w[i] > 1.0 -b) {
                    penalty += K*((1.0-b) - w[i]);
                }
            }
            P+= K*penalty*penalty;
            dCdw += K*penalty;
            dw2[i] = lambda*dw2[i] + (1.0-lambda)*dCdw*dCdw;
            direction += dCdw * dw[i];
            dw[i] = dCdw/(dw2[i] + 1.0);
            w[i] += alpha * dw[i];
            
            if (0) {
                float b = 0.0;
                if (w[i] < b) {
                    w[i] = b;
                } else if (w[i] > 1.0 -b) {
                    w[i] = 1.0 - b;
                }
            }
            
            dCdw2 += dCdw*dCdw;
            EdCdw += dCdw;
        } // indices

        if (direction<0) {
            alpha *= 0.9;
            fprintf (stderr, "# Reducing alpha to %f\n", alpha);
        }
        Z = (dCdw2);
        if (Z<0.01) {
            Z = 0.01;
        }



        fprintf (stderr, "%d %f %f %f %f\n", iter, C, P, dCdw2, EdCdw);
        if (iter>10000 && C>prevC) {
            fprintf (stderr, "# Time to break\n");
            fflush (stderr);
            break;
        }
        prevC = C;
    }
    FILE* f = fopen ("/tmp/result", "w");
    for (int i=0; i<N; ++i) {
        Point p = GetPoint(track[i], w[i]);
        fprintf (f, "%f %f\n", p.x, p.y);
    }
    fclose(f);
}


#if 0
// example
int main (int argc, char** argv)
{
    if (argc!=3) {
        fprintf (stderr, "usage: optimise_road iterations learning_rate\n");
        exit(-1);
    }
    int iter = atoi(argv[1]);
    float alpha = atof(argv[2]);
    TrackData track_data;
    SegmentList track;

    track_data.setStep(10.0f);

    float width_l = 9.0f;
    float width_r = 9.0f;
    track_data.setWidth(19.0f);

    track_data.AddStraight (track, 50.0, width_l, width_r); //1
    track_data.AddCurve (track, 90.0, 100, width_l, width_r); //2

    Optimise (track, iter, alpha);

    return 0;
}
#endif
