/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA3
 * GraphTest.c
 * Test client for Graph ADT
***/

#include <stdio.h>
#include "Graph.h"

int main() {
    // Test newGraph and printGraph
    int n = 5;
    Graph G = newGraph(n);
    printf("Original Graph:\n");
    printGraph(stdout, G);

    // Test addEdge and addArc
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addArc(G, 3, 4);
    addArc(G, 4, 5);
    printf("\nGraph after adding edges and arcs:\n");
    printGraph(stdout, G);

    // Test getOrder, getSize, and getParent
    printf("\nOrder: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));
    printf("Parent of vertex 2: %d\n", getParent(G, 2));

    // Test DFS
    List S = newList();
    for (int i = 1; i <= n; i++) {
        append(S, i);
    }
    printf("running dfs\n");    
    DFS(G, S);
    printf("\nGraph after DFS:\n");
    printGraph(stdout, G);

    // Test transpose and copyGraph
    Graph transposedG = transpose(G);
    Graph copiedG = copyGraph(G);
    printf("\nTransposed Graph:\n");
    printGraph(stdout, transposedG);
    printf("\nCopied Graph:\n");
    printGraph(stdout, copiedG);
    printf("\n");

    // Free memory
    freeGraph(&G);
    freeGraph(&transposedG);
    freeGraph(&copiedG);
    freeList(&S);

    return 0;
}
