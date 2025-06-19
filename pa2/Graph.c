#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

//typedef struct GraphObj* Graph;

typedef struct GraphObj{
	int size;
	int order;
	int label;
	List* adjList;
	int* color;
	int* parent;
	int* distance;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	assert(G!= NULL);

	G->order = n;
	G->size = 0;
	G->label = NIL;

	G->color = malloc((n+1)*sizeof(int));
       	G->distance = malloc((n+1)*sizeof(int));
	G->parent = malloc((n+1)*sizeof(int));
	G->adjList = malloc((n+1)*sizeof(List));
	
	for (int i = 1; i <= n; ++i) {
		G->color[i] = NIL;
		G->distance[i] = INF;
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
		free(G->distance);
		free(G->parent);

		free(G);
		free(pG);
		*pG = NULL;
	}

}

/*** Access functions ***/
int getOrder(Graph G){
	return G->order;
}

int getSize(Graph G){
	return G->size;
}

int getSource(Graph G){
	return G->label;
}

int getParent(Graph G, int u){
	return G->parent[u];
}

int getDist(Graph G, int u){
	return G->distance[u];
}

void getPath(List L, Graph G, int u){
	if(getSource(G) == NIL){
		append(L, NIL);
		return;
	}
	
	if(u == getSource(G)){
                append(L, u);
        }

	else if(G->parent[u] == NIL) {
        	append(L, NIL);
	}

	else{
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
	if(G == NULL){
		fprintf(stderr, "Error calling makeNull on an already null graph\n");
		exit(EXIT_FAILURE);
	}

	for(int i = 1; i <= G->order; i++){
		clear(G->adjList[i]);
	}
	G->size = 0;
}

void addEdge(Graph G, int u, int v){
	if (G->order <= u && G->order <= v && v < 1 && u < 1){
		fprintf(stderr, "Graph Error: calling addEdge on vertices that do not exist");
		exit(EXIT_FAILURE);
	}

	addArc(G, u, v);
	addArc(G, v, u);

	G->size -= 1; // since add arc x2 makes size 2x too big
}

void addArc(Graph G, int u, int v){
	if (u < 1 || v < 1 || u > G->order || v > G->order) {
        fprintf(stderr, "Graph Error: calling addArc on invalid vertices\n");
        exit(EXIT_FAILURE);
    }
    moveFront(G->adjList[u]);

    while (index(G->adjList[u]) >= 0) {
        int current = get(G->adjList[u]);

        if (current == v) {
            return;
        } else if (current > v) {
            insertBefore(G->adjList[u], v);
            G->size += 1;
            return;
        }

        // Move to the next element in the list
        moveNext(G->adjList[u]);
    }

    // If we reach the end of the list, append `v`
    append(G->adjList[u], v);
    G->size += 1;
} 

void BFS(Graph G, int s){
	for(int x = 1; x <= G->order; x++){
		G->color[x] = 0;
                G->distance[x] = INF;
                G->parent[x] = NIL;
	}

	G->color[s] = 1;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	G->label = s;

	List Q = newList();

	append(Q, s);

	while(length(Q) > 0){
		int x = front(Q);
		deleteFront(Q);
		List adjListX = G->adjList[x];
		for(moveFront(adjListX); index(adjListX) >= 0; moveNext(adjListX)){
			int y = get(adjListX);
			if(G->color[y] == 0){
				G->color[y] = 1;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(Q, y);
			}
		}
		G->color[x] = 2;	
	}
	
	freeList(&Q);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	for (int i = 1; i <= G->order; i++) {
        	fprintf(out, "%d:", i);
		printList(out, G->adjList[i]);
		fprintf(out, "\n");
	}	
}
