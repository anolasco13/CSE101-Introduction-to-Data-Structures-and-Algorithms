/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA2
 * FindPath.c
 * Uses Graph ADT to find shortest paths between pairs of vertices
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define INF -1
#define NIL 0
#define stringDistance "infinity"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE* outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    int n, u, v;

    // read the graph from the input file
    fscanf(inputFile, "%d", &n);

    if (n <= 0) {
        fprintf(stderr, "Error: Invalid number of vertices\n");
        fclose(inputFile);
        fclose(outputFile);
        exit(EXIT_FAILURE);
    }

    // declare 
    Graph G = newGraph(n);
 //   List pathList;

    while (fscanf(inputFile, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) {
            break;
        }

        if (u < 1 || u > n || v < 1 || v > n) {
            fprintf(stderr, "Error: Invalid vertex label\n");
            freeGraph(&G);
            fclose(inputFile);
            fclose(outputFile);
            exit(EXIT_FAILURE);
        }

        addEdge(G, u, v);
    }

    // print the adjacency list representation to the output file
    printGraph(outputFile, G);

    // process source-desitination pairs
    while (fscanf(inputFile, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) {
            break;
        }

        if (u < 1 || u > n || v < 1 || v > n) {
            fprintf(stderr, "Error: Invalid vertex label\n");
            freeGraph(&G);
            fclose(inputFile);
            fclose(outputFile);
            exit(EXIT_FAILURE);
        }

    // perform BFS from source vertex
    BFS(G, u);

    // print distance from source to destination
    int distance = getDist(G, v);
    
    // print shortest path
    List pathList = newList();
    getPath(pathList, G, v);

    if (front(pathList) == NIL) {
	fprintf(outputFile, "\nThe distance from %d to %d is %s\n", u, v, stringDistance);
	fprintf(outputFile, "No %d-%d path exists\n", u, v);
    } else {
	fprintf(outputFile, "\nThe distance from %d to %d is %d\n", u, v, distance);
        fprintf(outputFile, "A shortest %d-%d path is: ", u, v);
	printList(outputFile, pathList);
        fprintf(outputFile, "\n");
    }

    freeList(&pathList);
}

    // free memory and close files
    freeGraph(&G);
    fclose(inputFile);
    fclose(outputFile);
    // fix this
 //   freeList(&pathList);
    return 0;
}
