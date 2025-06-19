/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA2
 * Graph.c
 * Corresponding c file for Graph.h
***/

#include "Graph.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct GraphObj {
    List* adjacency;	// array of lists
    int* color;		// array of colors
    int* parent;	// array of parents
    int* distance;	// array of distances
    int order;	 	// number of vertices
    int size;	 	// number of edges
    int source;	 	// source vertex for BFS
} GraphObj;

/*** Constructors-Destructors ***/
// returns a graph pointing to a newly created GraphObj
// representing a graph having n vertices and no edges
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->adjacency = malloc((n + 1) * sizeof(List));
    G->color = malloc((n + 1) * sizeof(int));
    G->parent = malloc((n + 1) * sizeof(int));
    G->distance = malloc((n + 1) * sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;

    for (int i = 1; i <= n; i++) {
        G->adjacency[i] = newList();
        G->color[i] = 0; // 0 represents white color
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }

    return G;
}

// frees all heap memory associated with the Graph *pG
// sets *pG to NULL
void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= (*pG)->order; i++) {
            freeList(&((*pG)->adjacency[i]));
        }
        free((*pG)->adjacency);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}


/*** Access functions ***/
// returns number of vertices in the graph
int getOrder(Graph G) {
    return G->order;
}

// returns number of edges in the graph
int getSize(Graph G) {
    return G->size;
}

// returns the source vertex most recently used in BFS(), 
// or NIL if BFS() has not yet been called
int getSource(Graph G) {
    return G->source;
}

// returns the parent of vertex u in the BFS tree created by BFS(),
// or NIL if BFS() has not yet been called
int getParent(Graph G, int u) {
        if (1 <= u && u <= getOrder(G)) {
        return G->parent[u];
    }
    return NIL;
}

// returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called
int getDist(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->distance[u];
    }
    return INF;
}

// appends to the List L the verticecs of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exists
void getPath(List L, Graph G, int u) {
    if (getSource(G) != NIL && 1 <= u && u <= getOrder(G)) {
        if (u == getSource(G)) {
            append(L, u);
        } else if (getParent(G, u) == NIL) {
            append(L, NIL);
        } else {
            getPath(L, G, getParent(G, u));
            append(L, u);
        }
    }
}


/*** Manipulation procedures ***/
// deletes all edges of G,
// restoring to its original (no edge) state
void makeNull(Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->adjacency[i]);
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->size = 0;
    G->source = NIL;
}

// inserts a new edge joining u to v
void addEdge(Graph G, int u, int v) {
    if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)) {
        addArc(G, u, v);
        addArc(G, v, u);
        G->size--; // since addArc increments size twice
    }
}

// inserts a new directed edge from u to v
void addArc(Graph G, int u, int v) {
    if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)) {
        List adjList = G->adjacency[u];
        moveFront(adjList);
	
	// find the correct position to insert v in sorted order
        while (index(adjList) >= 0 && v > get(adjList)) {
            moveNext(adjList);
        }

        if (index(adjList) == -1) {
            append(adjList, v);
        } else {
            insertBefore(adjList, v);
        }

        G->size++;
    }
}

// runs the BFS algorithm on the Graph G with source s
void BFS(Graph G, int s) {
    if (1 <= s && s <= getOrder(G)) {
        G->source = s;
	
	// initialize colors, parents, and distances
        for (int i = 1; i <= getOrder(G); i++) {
            G->color[i] = 0; // 0 represents white color
            G->parent[i] = NIL;
            G->distance[i] = INF;
        }

        G->color[s] = 1; // 1 represents gray color
        G->parent[s] = NIL;
        G->distance[s] = 0;

        List queue = newList();
        append(queue, s);

	// BFS traversal
        while (length(queue) > 0) {
            int u = front(queue);
            deleteFront(queue);

            moveFront(G->adjacency[u]);
            while (index(G->adjacency[u]) >= 0) {
                int v = get(G->adjacency[u]);
                if (G->color[v] == 0) { // If the vertex is white
                    G->color[v] = 1;
                    G->parent[v] = u;
                    G->distance[v] = G->distance[u] + 1;
                    append(queue, v);
                }
                moveNext(G->adjacency[u]);
            }

            G->color[u] = 2; // 2 represents black color
        }

        freeList(&queue);
    }
}

/*** Other operations ***/
// prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjacency[i]);
        fprintf(out, "\n");
    }
}
