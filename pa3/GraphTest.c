#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "Graph.h"
#include "List.h"

void printTestResults(Graph G, int vertex) {
    printf("Graph Order: %d\n", getOrder(G));
    printf("Graph Size: %d\n", getSize(G));
    printf("Source: %d\n", getSource(G));
    printf("Distance to vertex %d: %d\n", vertex, getDist(G, vertex));
    printf("Parent of vertex %d: %d\n", vertex, getParent(G, vertex));

    List path = newList();
    getPath(path, G, vertex);
    printf("Path to vertex %d: ", vertex);
    printList(stdout, path);
    printf("\n");
    freeList(&path);
}

int main() {
    printf("Testing Graph ADT\n");

    Graph G = newGraph(6);
    makeNull(G);
    printf("After makeNull:\n");
    printTestResults(G, 1);

    printf("\nAdding edges (1, 2), (2, 3), (1, 3), (3, 4), (4, 5), (5, 6)\n");
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 1, 3);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);

    printf("\nGraph structure:\n");
    printGraph(stdout, G);

    printf("\nPerforming BFS from vertex 1:\n");
    BFS(G, 1);

    for (int i = 1; i <= 6; i++) {
        printTestResults(G, i);
    }

    freeGraph(&G);
    return 0;
}

