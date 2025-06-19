/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA1 
 * Lex.c
 * Main Program
 ***/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LINES 10000

// Function to compare strings for sorting
int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Error opening files");
        return 1;
    }

    char *lines[MAX_LINES];
    char buffer[300];

    int lineCount = 0;

    // Read lines from the input file
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        // Remove newline character if present
        size_t length = strlen(buffer);
        if (buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }
	
	// Allocate memory for the line and copy it
	lines[lineCount] = malloc(strlen(buffer) + 1);
        strcpy(lines[lineCount], buffer);

        lineCount++;
	
	// Check if the number of lines exceeds the maximum limit
	if (lineCount >= MAX_LINES) {
            fprintf(stderr, "Error: Maximum number of lines exceeded\n");
            return 1;
        }
    }
    
    // Sort the lines lexicographically
    qsort(lines, lineCount, sizeof(char *), compareStrings);

    // write the sorted lines to the output file
    for (int i = 0; i < lineCount; i++) {
        fprintf(outputFile, "%s\n", lines[i]);

	// free the allocated memory for each line
	free(lines[i]);
    }

    // close the files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
