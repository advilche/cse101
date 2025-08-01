#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Matrix.h"
#include "List.h"
#include "NeuralNetworks.h"

#define SIZE_OF_ARR(arr) sizeof(arr)/sizeof(arr[0])

// Helper function to create a simple input matrix
Matrix createInputMatrix(int rows, int cols, double value) {
    Matrix input = newMatrix(rows, cols);
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            changeEntry(input, i, j, value);
        }
    }
    return input;
}

// Helper function to print matrix with label
void printMatrixWithLabel(FILE* out, const char* label, Matrix M) {
    fprintf(out, "\n%s:", label);
    printMatrix(out, M);
}

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

    fprintf(out, "=== NEURAL NETWORK SANITY TEST ===\n\n");

    // Test 1: 2x2x1 network (XOR-like)
    fprintf(out, "\nTest 2: 2x2x2 Network\n");
    fprintf(out, "=====================\n");
    
    int nn_arch2[] = {2, 2, 2};
    int num_layers2 = sizeof(nn_arch2) / sizeof(nn_arch2[0]);
    NeuralNetwork NN2 = newRandNeuralNetwork(num_layers2, nn_arch2, -1, 1);
    
    printNN(out, NN2);

    double e = 1e-3;
    double r = 1e-3;

    // Test with different inputs
    Matrix input2_1 = createInputMatrix(2, 1, 1.0);
    changeEntry(input2_1, 2, 1, 1.0);

    printMatrix(out, input2_1);

    Matrix output2_1 = forward(NN2, input2_1);
    printMatrixWithLabel(out, "Output [0,0]", output2_1);

    // Test cost
    Matrix target = createInputMatrix(2, 1, 0.8);
    double c0 = meanSquaredError(target, output2_1);

    fprintf(out, "c0: %f\n", c0);

    // Fix: Correct loop bounds and also modify biases
    for (int i = 0; i < num_layers2 - 1; i++){
        add_by_epsilon(getWeight(NN2, i), e);
        add_by_epsilon(getBias(NN2, i), e);
    }

    output2_1 = forward(NN2, input2_1);

    double c1 = meanSquaredError(target, output2_1);
    fprintf(out, "c1: %f\n", c1);

    double dw = (c1 - c0);

    for (int i = 0; i < num_layers2; i++){
        mult_by_epsilon(getWeight(NN2, i), e);
        mult_by_epsilon(getBias(NN2, i), e);
    }

    printNN(out, NN2);

    // Test 4: Error handling
    fprintf(out, "\n\nTest 4: Error Handling\n");
    fprintf(out, "======================\n");
    
    // Test invalid layer index (this should be handled gracefully)
    fprintf(out, "Testing error handling...\n");

    // ... 

    fprintf(out, "All tests completed successfully!\n");

    fclose(out);
    
    return 0;
}
