#include <stdio.h>
#include <stdlib.h>

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

    // Create a new graph with 5 vertices
    Graph G = newGraph(5);

    // Test makeNull
    makeNull(G);
    printf("After makeNull:\n");
    printTestResults(G, 1);

    // Add edges
    printf("\nAdding edges (1, 2), (2, 3), (1, 3), (3, 4)\n");
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 1, 3);
    addEdge(G, 3, 4);

    // Check graph structure
    printGraph(stdout, G);

    // Perform BFS starting from vertex 1
    printf("\nPerforming BFS from vertex 1:\n");
    BFS(G, 1);

    // Print results for vertices
    for (int i = 1; i <= 4; i++) {
        printTestResults(G, i);
    }

    // Free the graph
    freeGraph(&G);
    return 0;
}
