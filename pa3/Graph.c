#include <stdio.h> //
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "Graph.h"
#include "List.h"

typedef struct GraphObj{
        int order;
        int size;
        int label;
        int time;

        int* parent;
        int* discover;
        int* finish;
        int* color;

        List* adjList;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
        Graph G = malloc(sizeof(GraphObj));
        assert(G!= NULL);

        G->order = n;
        G->size = 0;
        G->time = 0;

        G->color = malloc((n+1)*sizeof(int));
        G->parent = malloc((n+1)*sizeof(int));
        G->discover = malloc((n+1)*sizeof(int));
        G->finish = malloc((n+1)*sizeof(int));
        G->adjList = malloc((n+1)*sizeof(List));

        for (int i = 1; i <= n; ++i) {
                G->discover[i] = UNDEF;
                G->finish[i] = UNDEF;
                G->color[i] = NIL;
                G->parent[i] = NIL;
                G->adjList[i] = newList();
        }

        return G;
}

void freeGraph(Graph* pG){
        if( (pG != NULL) && (*pG != NULL)){
                Graph G = *pG;

                for (int i = 1; i <= G->order; i++) {
                        free(G->adjList);
                }

                freeList(G->adjList);
                free(G->color);
                free(G->parent);
                free(G->finish);
                free(G->discover);

                free(G);
                free(pG);
                *pG = NULL;
        }

}

/*** Access functions ***/
int getOrder(Graph graph) {
    return graph->order;
}

int getSize(Graph graph) {
    return graph->size;
}

//CHANGE THIS FUNCTION
int getParent(Graph graph, int vertex) {
    if(!(1 <= vertex && vertex <= getOrder(graph))) {
        fprintf(stderr, "Graph Error: calling getParent() on size order 0 Graph");
        exit(EXIT_FAILURE);
    }

    return graph->parent[vertex];
}

int getDiscover(Graph graph, int vertex) {
    if(!(1 <= vertex && vertex <= getOrder(graph))) {
        fprintf(stderr, "Graph Error: calling getDiscover() on size order 0 Graph");
        exit(EXIT_FAILURE);
    }

    return graph->discover[vertex];
}

int getFinish(Graph graph, int vertex) {
    if(!(1 <= vertex && vertex <= getOrder(graph))) {
        fprintf(stderr, "Graph Error: calling getFinish() on size order 0 Graph");
        exit(EXIT_FAILURE);
    }

    return graph->finish[vertex];
}


/*** Manipulation functions ***/
void addEdge(Graph graph, int vertexA, int vertexB) {
    if(!(1 <= vertexA && vertexA <= getOrder(graph))) {
        fprintf(stderr, "Graph Error: calling addEdge() on size order 0 Graph");
        exit(EXIT_FAILURE);
    }

    if (graph->order <= vertexA && graph->order <= vertexB && vertexB < 1 && vertexA < 1) {
        fprintf(stderr, "Graph Error: calling addEdge on vertices that do not exist");
        exit(EXIT_FAILURE);
    }

    addArc(graph, vertexA, vertexB);
    addArc(graph, vertexB, vertexA);

    graph->size -= 1; // bc addArc is called 2x makes size 2x big
}

void addArc(Graph graph, int vertexA, int vertexB) {
    if(!((1 <= vertexA) && (vertexA <= getOrder(graph)))) {
        fprintf(stderr, "Graph Error: calling addArc() on size order 0 Graph");
        exit(EXIT_FAILURE);
    }

    if (vertexA < 1 || vertexB < 1 || vertexA > graph->order || vertexB > graph->order) {
        fprintf(stderr, "Graph Error: calling addArc on invalid vertices\n");
        exit(EXIT_FAILURE);
    }

    moveFront(graph->adjList[vertexA]);

    while (index(graph->adjList[vertexA]) >= 0) {
        int current = get(graph->adjList[vertexA]);
        
        if (current == vertexB) {
            return;
        } else if (current > vertexB) {
            insertBefore(graph->adjList[vertexA], vertexB);
            graph->size += 1;
            return;
        }

        // Move to next 
        moveNext(graph->adjList[vertexA]);
    }

    // If reach append
    append(graph->adjList[vertexA], vertexB);
    graph->size += 1;
}

void makeNull(Graph graph) { 
    if(graph == NULL) {
        fprintf(stderr, "Error calling makeNull on an already null graph\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i <= graph->order; i++) {
        clear(graph->adjList[i]);
    }
    graph->size = 0;
}


static void Visit(Graph graph, List stack, int vertex, int* time) {
    graph->color[vertex] = 1;
    graph->discover[vertex] = ++(*time);

    moveFront(graph->adjList[vertex]);
    while (index(graph->adjList[vertex]) >= 0) {
        int adjacentVertex = get(graph->adjList[vertex]);
        if (graph->color[adjacentVertex] == 0) {
            graph->parent[adjacentVertex] = vertex;
            Visit(graph, stack, adjacentVertex, time);
        }
        moveNext(graph->adjList[vertex]);
    }
    graph->color[vertex] = 2;
    graph->finish[vertex] = ++(*time);
    prepend(stack, vertex);
}

void DFS(Graph graph, List stack) {
    if (length(stack) != getOrder(graph)) return;

    for (int i = 1; i <= graph->order; i++) {
        graph->color[i] = 0;
        graph->parent[i] = NIL;
    }

    int time = 0;
    List temp = copyList(stack);
    clear(stack);

    moveFront(temp);
    while (index(temp) >= 0) {
        int vertex = get(temp);
        if (graph->color[vertex] == 0) {
            Visit(graph, stack, vertex, &time);
        }
        moveNext(temp);
    }
    freeList(&temp);
}

Graph transpose(Graph graph) {
    Graph transposedGraph = newGraph(graph->order);
    for (int i = 1; i <= graph->order; i++) {
        moveFront(graph->adjList[i]);
        while (index(graph->adjList[i]) >= 0) {
            int adjacentVertex = get(graph->adjList[i]);
            addArc(transposedGraph, adjacentVertex, i);
            moveNext(graph->adjList[i]);
        }
    }
    return transposedGraph;
}

Graph copyGraph(Graph graph) {
    Graph newGraphInstance = newGraph(getOrder(graph));

    newGraphInstance->size = graph->size;
    newGraphInstance->order = graph->order;
    newGraphInstance->label = graph->label;

    for (int i = 1; i <= getOrder(graph); i++) {
        newGraphInstance->adjList[i] = copyList(graph->adjList[i]);
        newGraphInstance->color[i] = graph->color[i];
        newGraphInstance->parent[i] = graph->parent[i];
        newGraphInstance->discover[i] = graph->discover[i];
        newGraphInstance->finish[i] = graph->finish[i];
    }

    return newGraphInstance;
}

void printGraph(FILE* out, Graph graph) {
    for (int i = 1; i <= graph->order; i++) {
        fprintf(out, "%d: ", i);
        printList(out, graph->adjList[i]);
    }
}


