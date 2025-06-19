#include <stdio.h>
#include <stdlib.h>


#include "Matrix.h"
#include "List.h"

int main(int argc, char* argv[]) {
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

    int n, a, b;
    fscanf(in, "%d %d %d", &n, &a, &b);

    // Create matrices A and B
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // Read matrix A
    for (int i = 0; i < a; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(A, row, col, value);
    }

    // Read matrix B
    for (int i = 0; i < b; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    // Print matrix A and B
    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);

    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);

    // Perform and print matrix operations
    Matrix C;

    // (1.5) * A
    C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);
    freeMatrix(&C);

    // A + B
    C = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, C);
    freeMatrix(&C);

    // A + A
    C = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, C);
    freeMatrix(&C);

    // B - A
    C = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, C);
    freeMatrix(&C);

    // A - A
    C = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, C);
    freeMatrix(&C);

    // Transpose of A
    C = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, C);
    freeMatrix(&C);

    // A * B
    C = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, C);
    freeMatrix(&C);

    // B * B
    C = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, C);
    freeMatrix(&C);

    // Clean up
    freeMatrix(&A);
    freeMatrix(&B);

    fclose(in);
    fclose(out);

    return 0;
}