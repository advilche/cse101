// -------------------------------------------------------------------
// Lex.c
// Author: Your Name
// CruzID: Your CruzID
// CSE 101 - Programming Assignment 1
// -------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LINE_LENGTH 1024

// Function prototypes
void usage(const char* progName);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    const char* inputFileName = argv[1];
    const char* outputFileName = argv[2];
    FILE* inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        fprintf(stderr, "Error: Unable to open input file %s\n", inputFileName);
        return EXIT_FAILURE;
    }

    // Step 2: Count the number of lines in the input file
    char line[MAX_LINE_LENGTH];
    int n = 0;

    // First pass to count lines
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        n++;
    }
    rewind(inputFile);  // Reset file pointer to the beginning

    // Allocate memory for the string array
    char** lines = malloc(n * sizeof(char*));
    if (!lines) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    // Step 2: Read lines into the array
    for (int i = 0; i < n; i++) {
        lines[i] = malloc((MAX_LINE_LENGTH) * sizeof(char));
        if (!lines[i]) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            fclose(inputFile);
            return EXIT_FAILURE;
        }
        fgets(lines[i], MAX_LINE_LENGTH, inputFile);
        // Remove newline character if present
        lines[i][strcspn(lines[i], "\n")] = '\0';
    }

    fclose(inputFile);

    // Step 3: Create a new List and insert indices in sorted order
    List indexList = newList();

    for (int i = 0; i < n; i++) {
        int insertIndex = 0;
        moveFront(indexList);
        
        while (getIndex(indexList) >= 0) {
            int currentIndex = get(indexList);
            if (strcmp(lines[i], lines[currentIndex]) < 0) {
                break;
            }
            insertIndex++;
            moveNext(indexList);
        }

        if (insertIndex == length(indexList)) {
            append(indexList, i);
        } else {
            insertBefore(indexList, i);
        }
    }

    // Step 4: Write sorted lines to the output file
    FILE* outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        fprintf(stderr, "Error: Unable to open output file %s\n", outputFileName);
        return EXIT_FAILURE;
    }

    moveFront(indexList);
    while (getIndex(indexList) >= 0) {
        int lineIndex = get(indexList);
        fprintf(outputFile, "%s\n", lines[lineIndex]);
        moveNext(indexList);
    }

    fclose(outputFile);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);
    freeList(&indexList);

    return EXIT_SUCCESS;
}

void usage(const char* progName) {
    fprintf(stderr, "Usage: %s <input file> <output file>\n", progName);
}