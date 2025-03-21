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

    // Read the node type from the file
    int node_type;
    if (fscanf(inputFile, "%d", &node_type) != 1) {
        fprintf(stderr, "Error reading node type from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Allocate memory for the node
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }
    ND_TYPE(node) = node_type;

    // Close the file
    fclose(inputFile);

    // Call the onig_node_free function
    onig_node_free(node);

    return 0;
}