// -*- Mode: c++ -*-
// copyright (c) 2004 by Christos Dimitrakakis <dimitrak@idiap.ch>
// $Id$

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "policy.h"


DiscretePolicy::DiscretePolicy (int n_states, int n_actions, float alpha,
								float gamma, float lambda, bool softmax,
								float randomness, float init_eval)
{
	if (lambda<0.0) lambda = 0.0;
	if (lambda>0.99) lambda = 0.99;

	if (gamma<0.0) gamma = 0.0;
	if (gamma>0.99) gamma = 0.99;

	if (alpha<0.0) alpha = 0.0;
	if (alpha>0.2) alpha = 0.2;

	this->n_states = n_states;
	this->n_actions = n_actions;
	this->gamma = gamma;
	this->lambda = lambda;
	this->alpha = alpha;
	smax = softmax;
	temp = randomness;

	if (smax) {
		if (temp<0.1) 
			temp = 0.1;
	} else {
		if (temp<0.0) { 
			temp = 0.0;
		}
		if (temp>1.0) {
			temp = 1.0;
		}
	}
	printf ("Making Sarsa(lambda) ");
	if (smax) {
		printf ("softmax");
	} else {
		printf ("e-greedy");
	}	
	printf (" policy with Q:[%d x %d] -> R, a:%f g:%f, l:%f, t:%f\n",
			this->n_states, this->n_actions, this->alpha, this->gamma, this->lambda, this->temp);

	Q = new float*[n_states];
	e = new float*[n_states];
	for (int s=0; s<n_states; s++) {
		Q[s] = new float[n_actions];
		e[s] = new float[n_actions];
		for (int a=0; a<n_actions; a++) {
			Q[s][a] = init_eval;
			e[s][a] = 0.0;
		}
	}
	pQ = 0.0;
	ps = -1;
	pa = -1;
	min_el_state = 0;
	max_el_state = n_states -1;
	eval = new float[n_actions];
}

DiscretePolicy::~DiscretePolicy()
{
	float sum = 0.0;
	FILE* f = fopen ("/tmp/discrete","w");

	for (int s=0; s<n_states; s++) {
		sum += Q[s][argMax(Q[s])];
		if (f) {
			softMax(Q[s]);
			
			float sum2=0.0;
			for (int a=0; a<n_actions; a++) {
				sum2 += eval[a];
			}
			for (int a=0; a<n_actions; a++) {
				fprintf (f, "%f ", Q[s][a]);
			}
			fprintf (f, "\n");
		}
	}

	if (f) {
		fclose (f);
	}
	printf ("Expected return of greedy policy over random distribution of states: %f\n", sum/((float) n_states));
	delete [] Q;
	delete [] e;
	delete [] eval;
}

int DiscretePolicy::SelectAction (int s, float r)
{
	if ((s<0)||(s>=n_states)) {
		return 0;
	}

	int a;
	if (smax) {
		a = softMax (Q[s]);
	} else {
		a = eGreedy (Q[s]);
	}
	
	// do not update before we have selected any actions(!)
	// [a stricter implementation would solve this problem]
	if ((ps>=0)&&(pa>=0)) {
		float delta = r + gamma*Q[s][a] - Q[ps][pa];
		e[ps][pa] += 1.0;
		float ad = alpha*delta;
		float gl = gamma * lambda;
		
		//possible use for when we have too many states.. not
		//necessary at the moment
		/*
		  if (ps<min_el_state) min_el_state = ps;
		  if (ps>max_el_state) max_el_state = ps;
		*/
		for (int i=0; i<n_states; i++) {
			//for (int i=min_el_state; i<=max_el_state; i++) {
			bool el=true;
			for (int j=0; j<n_actions; j++) {
				if (e[i][j]>0.01) {
					Q[i][j] += ad * e[i][j];
					e[i][j] *= gl;
				} else {
					e[i][j] = 0.0;
					el = false;
				}
			}
			if (el==false) {
				if (min_el_state==i)
					min_el_state++;
			} else {
				max_el_state = i;
			}
		}
	}

	//printf ("%d %d #STATE\n", min_el_state, max_el_state);
	//	printf ("Q[%d,%d]=%f r=%f e=%f ad=%f gl=%f #QV\n",
	//			ps, pa, Q[ps][pa], r, e[ps][pa], ad, gl);
	ps = s;
	pa = a;

	return a;
}

void DiscretePolicy::loadFile (char* f) {
	FILE* fh = NULL;
	fh = fopen (f, "r");
	if (fh==NULL) return;

	for (int i=0; i<n_states; i++) {
		fread((void *) Q[i], sizeof(float), n_actions, fh);
	}
	fclose (fh);
}

void DiscretePolicy::saveFile (char* f) {
	FILE* fh = NULL;
	fh = fopen (f, "w");
	if (fh==NULL) return;

	for (int i=0; i<n_states; i++) {
		fwrite((void *) Q[i], sizeof(float), n_actions, fh);
	}
	fclose (fh);
}
