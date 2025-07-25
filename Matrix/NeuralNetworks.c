#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "NeuralNetworks.h"

struct NeuralNetworkObj {
    int num_layers;
    int input_size;
    int* hidden_archs;
    int output_size;

    Matrix* weights;
};

int* hidden_size(int* layer_sizes, int size) {
    int hidden_count = size - 2;
    if (hidden_count <= 0) return NULL;

    int* hidden_arch = malloc(hidden_count * sizeof(int));
    for (int i = 0; i < hidden_count; i++) {
        hidden_arch[i] = layer_sizes[i + 1];
    }

    return hidden_arch;
}

NeuralNetwork newRandNeuralNetwork(int num_layers, int* nn_arch, int min, int max){
    if (num_layers < 2) {
        fprintf(stderr, "newNeuralNetwork: invalid shape (%d)\n", num_layers);
        exit(EXIT_FAILURE);
    }

    NeuralNetwork NN    = malloc(sizeof(NeuralNetwork));
    if (NN == NULL) return NULL;

    NN->num_layers = num_layers;
    NN->input_size = nn_arch[0];
    NN->output_size = nn_arch[num_layers - 1];

    NN->hidden_archs = hidden_size(nn_arch, num_layers); // # nodes in each hidden layer

    NN->weights = calloc(num_layers - 1, sizeof(Matrix));
    if (NN->weights == NULL) {
        fprintf(stderr, "Failed to allocate weights array\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_layers - 1; ++i){
        NN->weights[i] = newRandMatrix(nn_arch[i + 1], nn_arch[i], min, max);
    }

    return NN;
}

Matrix getWeight(NeuralNetwork NN, int i) {
    return NN->weights[i];
}

void freeNeuralNetwork(NeuralNetwork* pNN);

void randomizeWeights(NeuralNetwork NN, float min, float max);

Matrix forward(NeuralNetwork NN, Matrix input);

void printNN(FILE* out, NeuralNetwork NN){
    for (int i = 0; i < NN->num_layers - 1; i++){
        fprintf(out, "\n");
        printMatrix(out, NN->weights[i]);
    }
}

double meanSquaredError(Matrix output, Matrix target);

