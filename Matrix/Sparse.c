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

    int nn_arch[] = {1, 1};
    int num_layers = sizeof(nn_arch) / sizeof(nn_arch[0]);
    NeuralNetwork NN = newRandNeuralNetwork(num_layers, nn_arch, 0, 5);

    fprintf(out, "NN:");
    printNN(out, NN);
    fprintf(out, "\n");

    fprintf(out, "X_in:\n");
    Matrix X_in = newRandMatrix(1, 1, -1, 1);
    changeEntry(X_in, 1, 1, 1);
    printMatrix(out, X_in);

    fprintf(out, "X_out:\n");
    Matrix X_out = newRandMatrix(1, 1, -1, 2);
    changeEntry(X_out, 1, 1, 2);
    printMatrix(out, X_out);

    fprintf(out, "\n");
    fprintf(out, "W^1*X:\n");       
    Matrix P = product(getWeight(NN, 0), X_in);
    printMatrix(out, P);

    fprintf(out, "\n");
    fprintf(out, "B:\n");
    Matrix B = newRandMatrix(1, 1, -1, 1);
    printMatrix(out, B);

    Matrix sum1 = sum(P, B); // WX+B = sum

    fprintf(out, "\n");
    fprintf(out, "Sig:\n");
    Matrix sig = sigmoid(sum1);
    printMatrix(out, sig); // o(WX+B)

    fprintf(out, "%f\n", meanSquaredError(sig, X_out));  
    fprintf(out, "Expected: %.8f\n", getEntry(X_out, 1, 1));
    fprintf(out, "Actual:   %.8f\n", getEntry(sig, 1, 1));

    return 0;
}

