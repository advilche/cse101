#include <stdio.h>
#include <stdlib.h>


#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {
    FILE* inFile = fopen(argv[1], "r");
    FILE* outFile = fopen(argv[2], "w");
    int n, u, v;
    fscanf(inFile, "%d", &n);
    Graph GraphOne = newGraph(n);
    for (; fscanf(inFile, "%d %d", &u, &v) == 2 && (u != 0 || v != 0); ) {
        addArc(GraphOne, u, v);
    }
    fprintf(outFile, "Adjacency list representation of G:\n");
    printGraph(outFile, GraphOne);
    List Stack = newList();
    int i = 1;
    while (i <= n) {
        append(Stack, i);
        i++;
    }
    DFS(GraphOne, Stack); // first call for DFS
    Graph GraphTransposeOne = transpose(GraphOne);
    DFS(GraphTransposeOne, Stack); // second call on transpose
    int componentCount = 0;
    moveBack(Stack);
    List componentList = newList();
    for (; index(Stack) >= 0; movePrev(Stack)) {
        int vertex = get(Stack);
        prepend(componentList, vertex);
        if (getParent(GraphTransposeOne, vertex) == -1) {
            componentCount += 1;
            moveFront(componentList);
            for (; index(componentList) >= 0; moveNext(componentList)) {
                // Do nothing; just move through the list
            }
            clear(componentList);
        }
    }
    fprintf(outFile, "\nG contains %d strongly connected components:\n", componentCount);
    List NewList = newList();
    i = 1;
    while (i <= n) {
        append(NewList, i);
        i++;
    }
    DFS(GraphOne, NewList);
    Graph GraphTransposeTwo = transpose(GraphOne);
    DFS(GraphTransposeTwo, NewList);
    componentCount = 0;
    moveBack(NewList);
    List componentList2 = newList();
    for (; index(NewList) >= 0; movePrev(NewList)) {
        int vertex = get(NewList);
        prepend(componentList2, vertex);
        if (getParent(GraphTransposeOne, vertex) == NIL) {
            componentCount++;
            fprintf(outFile, "Component %d:", componentCount);
            moveFront(componentList2);
            for (; index(componentList2) >= 0; moveNext(componentList2)) {
                fprintf(outFile, " %d", get(componentList2));
            }
            fprintf(outFile, "\n");
            clear(componentList2);
        }
    }
    fclose(inFile);
    fclose(outFile);
    return 0;
}