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


/*NeuralNetwork newNeuralNetwork(int num_layers, int* nn_arch){
    if (num_layers < 2) {
        fprintf(stderr, "newNeuralNetwork: invalid shape (%d)\n", num_layers);
        exit(EXIT_FAILURE);
    }

    NeuralNetwork NN    = malloc(sizeof(NeuralNetwork));
    if (NN == NULL) return NULL;

    NN->input_size      = nn_arch[0];
    NN->hidden_archs    = hidden_size(nn_arch, num_layers - 2); // # nodes in each hidden layer
    NN->output_size     = nn_arch[num_layers - 1];
    NN->num_layers      = num_layers;
    
    NN->input_layer     = newMatrix(nn_arch[0], 1);

    NN->hidden_layers   = calloc(num_layers - 2, sizeof(Matrix));
    for (int i = 1; i <= num_layers; i++) {
            NN->hidden_layers[i] = newMatrix(i, 1);
    }

    NN->output_layer     = newMatrix(nn_arch[num_layers - 1], 1);

    return NN;
}*/