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
    Matrix* biases;
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

NeuralNetwork newNeuralNetwork(int num_layers, int* layer_sizes) {
    if (num_layers < 2) {
        fprintf(stderr, "newNeuralNetwork: invalid shape (%d)\n", num_layers);
        exit(EXIT_FAILURE);
    }

    NeuralNetwork NN = malloc(sizeof(struct NeuralNetworkObj));
    if (NN == NULL) return NULL;

    NN->num_layers = num_layers;
    NN->input_size = layer_sizes[0];
    NN->output_size = layer_sizes[num_layers - 1];
    NN->hidden_archs = hidden_size(layer_sizes, num_layers);

    // Allocate weights array
    NN->weights = calloc(num_layers - 1, sizeof(Matrix));
    if (NN->weights == NULL) {
        fprintf(stderr, "Failed to allocate weights array\n");
        exit(EXIT_FAILURE);
    }

    // Allocate biases array
    NN->biases = calloc(num_layers - 1, sizeof(Matrix));
    if (NN->biases == NULL) {
        fprintf(stderr, "Failed to allocate biases array\n");
        exit(EXIT_FAILURE);
    }

    // Initialize weights and biases to zero
    for (int i = 0; i < num_layers - 1; ++i) {
        NN->weights[i] = newMatrix(layer_sizes[i + 1], layer_sizes[i]);
        NN->biases[i] = newMatrix(layer_sizes[i + 1], 1); // Bias is a column vector
    }

    return NN;
}

NeuralNetwork newRandNeuralNetwork(int num_layers, int* nn_arch, int min, int max) {
    if (num_layers < 2) {
        fprintf(stderr, "newNeuralNetwork: invalid shape (%d)\n", num_layers);
        exit(EXIT_FAILURE);
    }

    NeuralNetwork NN = malloc(sizeof(struct NeuralNetworkObj));
    if (NN == NULL) return NULL;

    NN->num_layers = num_layers;
    NN->input_size = nn_arch[0];
    NN->output_size = nn_arch[num_layers - 1];
    NN->hidden_archs = hidden_size(nn_arch, num_layers);

    // Allocate weights array
    NN->weights = calloc(num_layers - 1, sizeof(Matrix));
    if (NN->weights == NULL) {
        fprintf(stderr, "Failed to allocate weights array\n");
        exit(EXIT_FAILURE);
    }

    // Allocate biases array
    NN->biases = calloc(num_layers - 1, sizeof(Matrix));
    if (NN->biases == NULL) {
        fprintf(stderr, "Failed to allocate biases array\n");
        exit(EXIT_FAILURE);
    }

    // Initialize weights and biases with random values
    for (int i = 0; i < num_layers - 1; ++i) {
        NN->weights[i] = newRandMatrix(nn_arch[i + 1], nn_arch[i], min, max);
        NN->biases[i] = newRandMatrix(nn_arch[i + 1], 1, min, max);
    }

    return NN;
}

Matrix getWeight(NeuralNetwork NN, int i) { // weight of layer i
    return NN->weights[i];
}

Matrix getBias(NeuralNetwork NN, int layer_index) {
    if (layer_index < 0 || layer_index >= NN->num_layers - 1) {
        fprintf(stderr, "getBias: invalid layer index %d\n", layer_index);
        exit(EXIT_FAILURE);
    }
    return NN->biases[layer_index];
}

void freeNeuralNetwork(NeuralNetwork* pNN) {
    if (pNN != NULL && *pNN != NULL) {
        NeuralNetwork NN = *pNN;
        
        // Free weights
        for (int i = 0; i < NN->num_layers - 1; i++) {
            freeMatrix(&NN->weights[i]);
        }
        free(NN->weights);
        
        // Free biases
        for (int i = 0; i < NN->num_layers - 1; i++) {
            freeMatrix(&NN->biases[i]);
        }
        free(NN->biases);
        
        // Free hidden architecture array
        free(NN->hidden_archs);
        
        // Free the neural network itself
        free(NN);
        *pNN = NULL;
    }
}

void randomizeWeights(NeuralNetwork NN, float min, float max) {
    for (int i = 0; i < NN->num_layers - 1; i++) {
        // Free existing matrices
        freeMatrix(&NN->weights[i]);
        freeMatrix(&NN->biases[i]);
        
        // Create new random matrices
        NN->weights[i] = newRandMatrix(getNumRows(NN->weights[i]), 
                                      getNumCols(NN->weights[i]), min, max);
        NN->biases[i] = newRandMatrix(getNumRows(NN->biases[i]), 1, min, max);
    }
}

Matrix forward(NeuralNetwork NN, Matrix input) {
    if (getNumRows(input) != NN->input_size) {
        fprintf(stderr, "forward: input size mismatch\n");
        exit(EXIT_FAILURE);
    }

    Matrix current = copy(input);
    
    for (int i = 0; i < NN->num_layers - 1; i++) {
        // Compute: current = sigmoid(weights[i] * current + biases[i])
        Matrix weighted = product(NN->weights[i], current);
        Matrix with_bias = sum(weighted, NN->biases[i]);
        Matrix activated = sigmoid(with_bias);
        
        // Clean up intermediate matrices
        freeMatrix(&weighted);
        freeMatrix(&with_bias);
        freeMatrix(&current);
        
        current = activated;
    }
    
    return current;
}

void printNN(FILE* out, NeuralNetwork NN) {
    fprintf(out, "Neural Network with %d layers\n", NN->num_layers);
    fprintf(out, "Input size: %d, Output size: %d\n", NN->input_size, NN->output_size);
    
    for (int i = 0; i < NN->num_layers - 1; i++) {
        fprintf(out, "\nLayer %d:\n", i);
        fprintf(out, "\nWeights:");
        printMatrix(out, NN->weights[i]);
        fprintf(out, "\nBiases:");
        printMatrix(out, NN->biases[i]);
    }
}

void add_by_epsilon(Matrix input, double eps){
    for (int i = 1; i <= getNumRows(input); i++){
        for (int j = 1; j <= getNumCols(input); j++) {
            double w = getEntry(input, i, j);
            changeEntry(input, i, j, w + eps);
        }
    }
}

void mult_by_epsilon(Matrix input, double eps){
    for (int i = 1; i <= getNumRows(input); i++){
        for (int j = 1; j <= getNumCols(input); j++) {
            double w = getEntry(input, i, j);
            changeEntry(input, i, j, w * eps);
        }
    }
}

double meanSquaredError(Matrix target, Matrix output){
    if (getNumCols(output) != getNumCols(target) || getNumRows(output) != getNumRows(target)){
        fprintf(stderr, "outputCols: %d, targerCols: %d, outputRows: %d, targetRows: %d, ", getNumCols(output), getNumCols(target), getNumRows(output), getNumRows(target));
        exit(EXIT_FAILURE);
    }

    double cost = 0;

    for (int i = 1; i <= getNumRows(output); i++){
        for (int j = 1; j <= getNumCols(target); j++){
            double expected = getEntry(target, i, j);
            double actual   = getEntry(output, i, j);
            double diff = expected - actual;
            cost += diff * diff;
        }
    }

    cost /= (getNumRows(target) * getNumCols(target));

    return cost;
}