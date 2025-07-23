#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Matrix.h"

void printTestResults(Matrix M) {
    printf("Matrix Order: %d\n", size(M));
    printf("Matrix NNZ (Non-zero entries): %d\n", NNZ(M));
    printf("Matrix:\n");
    printMatrix(stdout, M);
    printf("\n");
}

int main() {
    printf("Testing Matrix ADT\n");

    Matrix M = newMatrix(5);
    makeZero(M);
    printf("After makeZero:\n");
    printTestResults(M);

    printf("\nChanging some entries in the matrix:\n");
    changeEntry(M, 1, 1, 1.0);
    changeEntry(M, 2, 3, 3.0);
    changeEntry(M, 3, 5, 5.0);
    changeEntry(M, 4, 2, 2.0);
    changeEntry(M, 5, 4, 4.0);
    printTestResults(M);

    printf("\nPerforming scalar multiplication (multiply by 2):\n");
    Matrix M2 = scalarMult(2.0, M);
    printTestResults(M2);

    printf("\nPerforming transpose:\n");
    Matrix M3 = transpose(M);
    printTestResults(M3);

    printf("\nAdding matrix M and M2:\n");
    Matrix M4 = sum(M, M2);
    printTestResults(M4);

    printf("\nSubtracting M2 from M:\n");
    Matrix M5 = diff(M, M2);
    printTestResults(M5);

    printf("\nMultiplying M and M3:\n");
    Matrix M6 = product(M, M3);
    printTestResults(M6);

    freeMatrix(&M);
    freeMatrix(&M2);
    freeMatrix(&M3);
    freeMatrix(&M4);
    freeMatrix(&M5);
    freeMatrix(&M6);



    return 0;
}
