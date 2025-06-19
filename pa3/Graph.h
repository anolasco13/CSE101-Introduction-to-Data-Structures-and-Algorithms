/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA3
 * Graph.h
 * Header file for Graph functions
***/

#ifndef GRAPH_H
#define GRAPH_H

#include "List.h"

#define NIL -1
#define INF -2
#define UNDEF -3

// Exported Graph type
typedef struct GraphObj* Graph;

// Constructors-Destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

// Manipulation procedures
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void DFS(Graph G, List S);

// Other operations
void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);

#endif

