#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"
#include "regparse.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Allocate memory for the Node structure
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    // Read the node type from the file
    int nodeType;
    if (fscanf(inputFile, "%d", &nodeType) != 1) {
        fprintf(stderr, "Error reading node type from file\n");
        free(node);
        fclose(inputFile);
        return 1;
    }

    // Set the node type using the ND_TYPE macro
    ND_TYPE(node) = nodeType;

    // Close the file
    fclose(inputFile);

    // Call the onig_reduce_nested_quantifier function
    int result = onig_reduce_nested_quantifier(node);

    // Output the result (for debugging purposes)
    printf("Result of onig_reduce_nested_quantifier: %d\n", result);

    // Clean up
    free(node);

    return 0;
}