#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Matrix.h"
#include "List.h"
#include "NeuralNetworks.h"

#define SIZE_OF_ARR(arr) sizeof(arr)/sizeof(arr[0]);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <inputfile> <outputfile>\n", argv[0]);
        return 1;
    }

    FILE* out = fopen(argv[2], "w");
    if (!out) {
        perror("Error opening output file");
        return 1;
    }

    srand(time(NULL)); // Seed for reproducibility

    // Architecture: 1 input, 1 output
    int nn_arch[] = {1, 1};
    int num_layers = sizeof(nn_arch) / sizeof(nn_arch[0]);
    NeuralNetwork NN = newRandNeuralNetwork(num_layers, nn_arch, -5, 5);

    printNN(out, NN);

    fclose(out);
    return 0;
}

//what
