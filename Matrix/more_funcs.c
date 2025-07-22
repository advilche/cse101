#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "List.h"

typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

int main(int argc, char *argv[]){
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
    Matrix A = newMatrix(m, n);
    Matrix B = newMatrix(m1, n1);

    for (int i = 0; i < a; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(A, row, col, value);
    }

    for (int i = 0; i < b; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    printMatrix(out, A);
    fprintf(out, "\n");
    printMatrix(out, B);

    double val = getEntry(B, 2, 2);

    List tempListA = getRow(A, 1);
    List tempListB = getRow(B, 1);
    
    List tempListBx1 = getColRow(B, 3);
    moveFront(tempListBx1);
    
    fprintf(out, "\n");

    fprintf(out, "%.1f", vectorDot(tempListBx1, tempListA));

    return 0;
}

