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
#ifndef POLICY_H
#define POLICY_H

#include <cmath>
#include <cstdlib>
#include <cstdio>

/*
  This class implements a discrete policy using the Sarsa(\lambda)
  Reinforcement Learning algorithm. After creating an instance of the
  algorithm were the number of actions and states are specified, you
  can call the SelectAction() method at every time step to
  dynamically select an action according to the given state. At the
  same time you must provide a reinforcement, which should be large
  (or positive) for when the algorithm is doing well, and small (or
  negative) when it is not. The algorithm will try and maximise the
  total reward received. 

  Parameters:
  
  n_states: The number of discrete states, or situations, that the
  agent is in. You should create states that are relevant to the task.
  
  n_actions: The number of different things the agent can do at every
  state. Currently we assume that all actions are usable at all
  states. However if an action a_i is not usable in some state s, then
  you can make the client side of the code for state s map state a_i
  to some usable state a_j, meaning that when the agent selects action
  a_i in state s, the result would be that of taking one of the usable
  actions. This will make the two actions equivalent. Alternatively
  when the agent selects an unusable action at a particular state, you
  could have a random outcome of actions. The algorithm can take care
  of that, since it assumes no relationship between the same action at
  different states.


  alpha: Learning rate. Controls how fast the evaluation is changed at
  every time step. Good values are between 0.01 and 0.1. Lower than
  0.01 makes learning too slow, higher than 0.1 makes learning
  unstable, particularly for high gamma and lambda.

  gamma: The algorithm will maximise the exponentially
  decaying sum of all future rewards, were the base of the exponent is
  gamma. If gamma=0, then the algorithm will always favour short-term
  rewards over long-term ones. Setting gamma close to 1 will make
  long-term rewards more important.

  lambda: This controls how much the expected value of reinforcement
  is close to the observed value of reinforcement. Another view is
  that of it controlling the eligibility traces e. Eligibility traces
  perform temporal credit assignment to previous actions/states. High
  values of lambda (near 1) can speed up learning. With lambda=0, only
  the currently selected action/state pair evaluation is updated. With
  lambda>0 all state/action pair evaluations taken in the past are
  updated, with most recent pairs updated more than pairs further in
  the past. Ultimately the optimal value of lambda will depend on the
  task.

  softmax, randomness: If this is false, then the algorithm selects
  the best possible action all the time, but with probability
  'randomness' selects a completely random action at each timestep. If
  this is true, then the algorithm selects actions stochastically,
  with probability of selecting each action proportional to how better
  it seems to be than the others. A high randomness (>10.0) will create more
  or less equal probabilities for actions, while a low randomness
  (<0.1) will make the system almost deterministic.
  
  init_eval: This is the initial evaluation for actions. It pays to
  set this to optimistic values (i.e. higher than the reinforcement to
  be given), so that the algorithm becomes always 'disappointed' and
  tries to explore as much of the possible combinations as it can.


*/ 
class DiscretePolicy 
{
protected:
	int n_states;
	int n_actions;
	float** Q;
	float** e;
	float* eval;
	float pQ;
	int ps, pa;
	float r;
	float temp;
	bool smax;
	float gamma;
	float lambda;
	float alpha;
	int min_el_state;
	int max_el_state;
	int softMax(float* Qs)
	{
		float sum=0.0;
		float beta = 1.0/temp;
		for (int a=0; a<n_actions; a++) {
			eval[a] = exp(beta * Qs[a]);
			sum += eval[a];
		}
		float X = drand48()*sum;
		float dsum = 0.0;
		for (int a=0; a<n_actions; a++) {
			dsum += eval[a];
			if (X<=dsum) 
				return a;

		}
		fprintf (stderr, "No action selected!\n");
		return -1;
	}
	int eGreedy(float* Qs)
	{
		float X = drand48();
		if (X<temp) {
			return rand()%n_actions;
		}
		return argMax(Qs);
	}
	int argMax(float* Qs)
	{
		float max = Qs[0];
		int arg_max = 0;
		for (int a=1; a<n_actions; a++) {
			if (max<Qs[a]) {
				max = Qs[a];
				arg_max = a;
			}
		}
		return arg_max;
	}
public:
	DiscretePolicy (int n_states, int n_actions, float alpha=0.1, float gamma=0.8, float lambda=0.8, bool softmax = false, float randomness=0.1, float init_eval=0.0);
	~DiscretePolicy();
	int SelectAction(int s, float r);
	void loadFile (char* f);
	void saveFile (char* f);
};

#endif
