/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA2
 * GraphTest.c
 * Test client that tests graph operations in isolation
***/

#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"Graph.h"

int main() {
    // test creating a new graph
    Graph G = newGraph(5);

    // test adding edges and arcs
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addArc(G, 3, 5);

    // test printing the graph
    printf("Graph G:\n");
    printGraph(stdout, G);

    // test BFS
    BFS(G, 1);

    // test accessing information after BFS
    printf("\nBFS Results:\n");
    printf("Order: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));
    printf("Source: %d\n", getSource(G));

    // print distance and parent information
    for (int i = 1; i <= getOrder(G); i++) {
        printf("Distance from source to %d: %d\n", i, getDist(G, i));
        printf("Parent of %d: %d\n", i, getParent(G, i));
    }

    // test getPath
    List pathList = newList();
    for (int i = 1; i <= getOrder(G); i++) {
        printf("\nShortest path from source to %d:\n", i);
        getPath(pathList, G, i);
        printList(stdout, pathList);
        printf("\n");
        clear(pathList);
    }

    // test freeing graph
    freeGraph(&G);

    return 0;
}
    
