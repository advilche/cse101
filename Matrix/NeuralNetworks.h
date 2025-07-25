#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "Matrix.h"

typedef struct NeuralNetworkObj* NeuralNetwork;

int* hidden_size(int* layer_sizes, int size);
Matrix getWeight(NeuralNetwork NN, int layer_index);

// Constructor / Destructor
NeuralNetwork newNeuralNetwork(int num_layers, int* layer_sizes);
NeuralNetwork newRandNeuralNetwork(int num_layers, int* layer_sizes, int min, int max);

void freeNeuralNetwork(NeuralNetwork* pNN);

// Initialization
void randomizeWeights(NeuralNetwork NN, float min, float max);

// Forward propagation
Matrix forward(NeuralNetwork NN, Matrix input);

// (Optional) Activation and utility
double meanSquaredError(Matrix output, Matrix target);
void printNN(FILE* out, NeuralNetwork NN);


#endif // NEURAL_NETWORK_H