/* -*- Mode: C++; -*- */
// VER: $Id$
// copyright (c) 2004 by Christos Dimitrakakis <dimitrak@idiap.ch>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef ANN_H
#define ANN_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "learn_debug.h"
#include "string_utils.h"
#include "List.h"
#include "real.h"

/** \file ANN.h
    \brief A neural network implementation.
    
    A neural network is a parametric function composed of a number of
    'layers'. Each layer can be expressed as a function \f$g(y)
    =g(\sum_i w_i f_i (x))\f$, where the \f$w\f$ are a set of weights
    and \f$f(\cdot)\f$ is a set of basis functions. The basis
    functions can be fixed or they can be another layer. The neural
    network can be adapted to minimise some cost criterion \f$C\f$
    (defined on some data) via gradient descent. The gradient of the
    cost with respect to the data is \f$\partial C/\partial x\f$. By
    expanding this with the chain rule, we have: \f$\partial
    C/\partial x = \partial g/\partial y \partial y/\partial w
    \partial w/\partial x\f$.
*/

/** \brief A linear connection between two neural elements.

It is used to express the sum weights in 
\f$y = \sum_i w_i f_i (x)\f$.
This type of connection currently also supports eligibility traces
gradient descent updates, batch updates and variance estimates.
*/
typedef struct Connection_ {
	int c; ///< connected?
	real w; ///< weight
	real dw; ///< Weight-change
	real e; ///< eligibility;
	real v; ///<variance estimate
} Connection;

/** \brief An RBF connection between two neural elements.
    
It is used to express:
\f$y = \sum_i \big((m_i-f_i(x)) w_i\big)^2\f$.
This type of connection has no extra features. When an RBF connection is created through the standard high-level function AddRBFHiddenLayer, then the layer output is \f$g(y) = e^y\f$.
*/
typedef struct RBFConnection_ {
	real w; ///< weight (=\f$1/\sigma\f$)
	real m; ///< mean
} RBFConnection;

/// \brief A collection of connections from one layer to another, plus
/// management functions and data.
typedef struct Layer_ {
	int n_inputs; ///< number of inputs
	int n_outputs; ///< number of outputs
	real* x; ///< inputs;
	real* y; ///< outputs
	real* z; ///< activation
	real* d; ///< derivatives
	Connection* c; ///< connections
	RBFConnection* rbf; ///< rbf connections (if any)
	real a; ///< learning rate
	real lambda; ///< eligibility decay
	real zeta; ///< variance update smoothness.
	bool batch_mode; ///< do not update weights immediately
	void (*forward) (struct Layer_* current_layer, bool stochastic); ///< forward calculation
	real (*backward) (LISTITEM* p, real* d, bool use_eligibility, real TD); ///< partial derivative calculation
	real (*f) (real x); ///< activation function
	real (*f_d) (real x); ///< derivative of activation function
} Layer;

/// \brief ANN management structure.
typedef struct ANN_ {
	int n_inputs; ///< number of inputs
	int n_outputs; ///< number of outputs
	LIST* c; ///< connection layers
	real* x; ///< unit inputs
	real* y; ///< unit activations
	real* t; ///< targets
	real* d; ///< delta vector
	real a; ///< learning rate
	real lambda; ///< eligibility trace decay
	real zeta; ///< variance update smoothness
	real* error; ///< errors
	bool batch_mode; ///< use batch mode
	bool eligibility_traces; ///< use eligibility
} ANN;


/**************** User-level API ******************/
/* Object Management Interface */
ANN* NewANN(int n_inputs, int n_outputs);
int DeleteANN(ANN* ann);
ANN* LoadANN(char* filename);
ANN* LoadANN(FILE* f);
int SaveANN(ANN* ann, char* filename);
int SaveANN(ANN* ann, FILE* f);

/* Setup Inteface */
int ANN_AddHiddenLayer(ANN* ann, int n_nodes);
int ANN_AddRBFHiddenLayer (ANN* ann, int n_nodes);
int ANN_Init(ANN* ann);
void ANN_SetOutputsToTanH(ANN* ann);
void ANN_SetOutputsToLinear(ANN* ann);
void ANN_SetLearningRate(ANN* ann, real a);
void ANN_SetLambda(ANN * ann, real lambda);
void ANN_SetZeta(ANN * ann, real lambda);
void ANN_Reset(ANN* ann);

/* Functionality Interface */
real ANN_Input(ANN* ann, real* x);
real ANN_StochasticInput(ANN * ann, real * x);
real ANN_Train(ANN* ann, real* x, real* t);
real ANN_Delta_Train(ANN * ann, real* delta, real TD = 0.0);
void ANN_SetBatchMode(ANN* ann, bool batch);
void ANN_BatchAdapt(ANN* ann);
real ANN_Test(ANN* ann, real* x, real* t);
real* ANN_GetOutput(ANN* ann);
real ANN_GetError(ANN* ann);
real* ANN_GetErrorVector(ANN* ann);

/********* Low-level code **********/

/* Sub-object management functions */
Layer* ANN_AddLayer (ANN* ann, int n_inputs, int n_outputs, real* x);
Layer* ANN_AddRBFLayer (ANN* ann, int n_inputs, int n_outputs, real* x);
void ANN_FreeLayer (void* l);
void ANN_FreeLayer (Layer* l);

/* Calculations */
void ANN_CalculateLayerOutputs (Layer* current_layer, bool stochastic=false);
real ANN_Backpropagate (LISTITEM* p, real* d, bool use_eligibility=false, real TD = 0.0);
void ANN_RBFCalculateLayerOutputs (Layer* current_layer, bool stochastic=false);
real ANN_RBFBackpropagate (LISTITEM* p, real* d, bool use_eligibility=false, real TD = 0.0);
void ANN_LayerBatchAdapt (Layer* l);

/* Output functions and derivatives */
real Exp (real x);
real Exp_d (real x);
real htan (real x);
real htan_d (real x);
real dtan (real x);
real dtan_d (real x);
real linear (real x);
real linear_d (real x);

/* Debugging functions */
real ANN_LayerShowWeights (Layer* l);
real ANN_ShowWeights(ANN* ann);
void ANN_ShowOutputs(ANN* ann);
real ANN_ShowInputs(ANN* ann);
real ANN_LayerShowInputs(Layer* l);
#endif /* ANN_H */
