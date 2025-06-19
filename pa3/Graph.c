/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA3
 * Graph.c
 * Corresponding c file for Graph.h
***/

#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "List.h"

#define WHITE 0
#define GREY 1
#define BLACK 2

/*** Structs ***/

typedef struct GraphObj {
    List *adjacency;
    int *color;
    int *parent;
    int *discover;
    int *finish;
    int *distance;
    int order;
    int size;
    int source;
    int time;
} GraphObj;

/*** Constructors-Destructors ***/

// newGraph()
// Creates and returns a new Graph with n vertices.
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->adjacency = malloc((n + 1) * sizeof(List));
    G->color = malloc((n + 1) * sizeof(int));
    G->parent = malloc((n + 1) * sizeof(int));
    G->discover = malloc((n + 1) * sizeof(int));
    G->finish = malloc((n + 1) * sizeof(int));
    G->distance = malloc((n + 1) * sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    G->time = 0;

    for (int i = 1; i <= n; i++) {
        G->adjacency[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
        G->distance[i] = INF;
    }
    return G;
}

// freeGraph()
// Frees all dynamically allocated memory associated with Graph *pG.
void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= getOrder(*pG); i++) {
            freeList(&((*pG)->adjacency[i]));
        }
        free((*pG)->adjacency);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/

int getOrder(Graph G) {
    return G->order;
}

int getSize(Graph G) {
    return G->size;
}

int getSource(Graph G) {
    return G->source;
}

int getParent(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->parent[u];
    }
    return NIL;
}

int getDiscover(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->discover[u];
    }
    return UNDEF;
}

int getFinish(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->finish[u];
    }
    return UNDEF;
}

int getDist(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->distance[u];
    }
    return INF;
}

void getPath(List L, Graph G, int u) {
    if (getSource(G) == NIL) {
        append(L, NIL);
    } else if (u == getSource(G)) {
        append(L, u);
    } else if (getParent(G, u) == NIL) {
        append(L, NIL);
    } else {
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}

/*** Manipulation procedures ***/

void makeNull(Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->adjacency[i]);
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    G->size = 0;
    G->source = NIL;
}

void addEdge(Graph G, int u, int v) {
    if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)) {
        addArc(G, u, v);
        addArc(G, v, u);
        G->size--; // Adjust size because addArc increments it twice
    }
}

void addArc(Graph G, int u, int v) {
    if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)) {
        List L = G->adjacency[u];
        moveFront(L);
        while (index(L) != -1 && get(L) < v) {
            moveNext(L);
        }
        if (index(L) == -1) {
            append(L, v);
        } else {
            insertBefore(L, v);
        }
        G->size++;
    }
}

void BFS(Graph G, int s) {
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->source = s;
    G->color[s] = GREY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    append(Q, s);
    while (length(Q) > 0) {
        int u = front(Q);
        deleteFront(Q);
        List L = G->adjacency[u];
        moveFront(L);
        while (index(L) != -1) {
            int v = get(L);
            if (G->color[v] == WHITE) {
                G->color[v] = GREY;
                G->distance[v] = G->distance[u] + 1;
                G->parent[v] = u;
                append(Q, v);
            }
            moveNext(L);
        }
        G->color[u] = BLACK;
    }
    freeList(&Q);
}

void Visit(Graph G, List S, int u) {
    G->discover[u] = ++G->time;
    G->color[u] = GREY;
    List L = G->adjacency[u];
    moveFront(L);
    while (index(L) != -1) {
        int v = get(L);
        if (G->color[v] == WHITE) {
            G->parent[v] = u;
            Visit(G, S, v);
        }
        moveNext(L);
    }
    G->color[u] = BLACK;
    G->finish[u] = ++G->time;
    prepend(S, u);
}

void DFS(Graph G, List S) {
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "Error: DFS called with invalid list length\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    G->time = 0;
    moveFront(S);
    while (index(S) != -1) {
        int u = get(S);
        if (G->color[u] == WHITE) {
            Visit(G, S, u);
        }
        moveNext(S);
    }
    // Clear the remaining list and adjust it to contain the DFS finish order.
    for (int i = 0; i < getOrder(G); i++) {
        deleteBack(S);
    }
}

/*** Other operations ***/

void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjacency[i]);
        fprintf(out, "\n");
    }
}

Graph transpose(Graph G) {
    Graph T = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        List L = G->adjacency[i];
        moveFront(L);
        while (index(L) != -1) {
            addArc(T, get(L), i);
            moveNext(L);
        }
    }
    return T;
}

Graph copyGraph(Graph G) {
    Graph C = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        List L = G->adjacency[i];
        moveFront(L);
        while (index(L) != -1) {
            addArc(C, i, get(L));
            moveNext(L);
        }
    }
    return C;
}

