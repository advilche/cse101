#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "Matrix.h"

typedef struct NeuralNetworkObj {
    int* input_size;
    int* hidden_size;
    int* output_size;

    int layers;
} NeuralNetworkObj;

typedef struct NeuralNetworkObj* NeuralNetwork;

// Constructor / Destructor
NeuralNetwork newNeuralNetwork(int num_layers, int* layer_sizes);

void freeNeuralNetwork(NeuralNetwork* pNN);

// Initialization
void randomizeWeights(NeuralNetwork NN, float min, float max);

// Forward propagation
Matrix forward(NeuralNetwork NN, Matrix input);

// (Optional) Activation and utility
Matrix sigmoid(Matrix M);
double sigmoidf(double x);
double meanSquaredError(Matrix output, Matrix target);

#endif // NEURAL_NETWORK_H
