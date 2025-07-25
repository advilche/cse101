#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Matrix.h"
#include "List.h"
#include "NeuralNetworks.h"

#define SIZE_OF_ARR(arr) sizeof(arr)/sizeof(arr[0]);

typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

int main(int argc, char *argv[]){
    srand(time(NULL));                     // random seed

    // Ensure proper number of arguments
    if (argc != 3) {
        printf("Usage: %s <inputfile> <outputfile>\n", argv[0]);
        return 1;
    }

    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");

    if (in == NULL || out == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int m, n, m1, n1, a, b;

    fscanf(in, "%d %d %d %d %d %d", &m, &n, &m1, &n1, &a, &b);
    printf("%d, %d, %d, %d, %d, %d\n", m, n, m1, n1, a, b);

    // Create matrices A & B
    Matrix I = newMatrix(m, n);
    Matrix W1 = newMatrix(m1, n1);

    for (int i = 0; i < a; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(I, row, col, value);
    }

    for (int i = 0; i < b; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(W1, row, col, value);
    }

    printMatrix(out, I);
    fprintf(out, "\n");

    printMatrix(out, W1);
    fprintf(out, "\n");

    Matrix H0 = product(I, W1);
    Matrix H1 = sigmoid(H0);

    printMatrix(out, H1);
    fprintf(out, "\n");

    int nn_arch[] = {2, 1, 2, 3};
    int num_layers = sizeof(nn_arch) / sizeof(nn_arch[0]);
    NeuralNetwork NN = newRandNeuralNetwork(num_layers, nn_arch, 0, 5);

    fprintf(stdout, "NN:\n");
    printNN(stdout, NN);
    fprintf(stdout, "\n");

    fprintf(stdout, "X:\n");
    Matrix X = newRandMatrix(2, 1, 0, 1);
    printMatrix(stdout, X);

    fprintf(stdout, "\n");
    fprintf(stdout, "W^1*X:\n");
    printMatrix(stdout, product(getWeight(NN, 0), X));
    
    return 0;
}

