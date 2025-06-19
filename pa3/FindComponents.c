/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA3
 * FindComponents.c
 * Client to find strongly connected components of a graph
***/


#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open input file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open output file %s\n", argv[2]);
        fclose(in);
        exit(EXIT_FAILURE);
    }

    int n;
    fscanf(in, "%d", &n);

    // Create a new graph with n vertices.
    Graph G = newGraph(n);

    // Read the edges and add arcs.
    int u, v;
    while (fscanf(in, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) break;
        addArc(G, u, v);
    }

    // Print adjacency list of G.
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // Prepare list S with vertices in the order 1 to n.
    List S = newList();
    for (int i = 1; i <= n; i++) {
        append(S, i);
    }

    // Perform DFS on G.
    DFS(G, S);

    // Get the transpose of G.
    Graph GT = transpose(G);

    // Perform DFS on the transpose graph GT using the order of S.
    DFS(GT, S);

    // Prepare a list to hold the components.
    List* components = malloc(n * sizeof(List));
    int componentCount = 0;
    moveFront(S);

    // Extract components.
    while (index(S) != -1) {
        int v = get(S);
        if (getParent(GT, v) == NIL) {
            // Create a new list for the component.
            components[componentCount] = newList();
            componentCount++;
        }
        append(components[componentCount - 1], v);
        moveNext(S);
    }

    // Print the total number of strongly connected components.
    fprintf(out, "G contains %d strongly connected components:\n", componentCount);


    // Print the strongly connected components in reverse order.
    for (int i = componentCount - 1; i >= 0; i--) {
        fprintf(out, "Component %d: ", componentCount - i);
        printList(out, components[i]);
        fprintf(out, "\n");
        freeList(&components[i]);
    }

    // Free memory and close files.
    free(components);
    freeGraph(&G);
    freeGraph(&GT);
    freeList(&S);
    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}

