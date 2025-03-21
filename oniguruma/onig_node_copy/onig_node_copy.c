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

    // Read the input data (assuming it's a single integer for simplicity)
    int inputValue;
    if (fscanf(inputFile, "%d", &inputValue) != 1) {
        fprintf(stderr, "Error reading integer from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Initialize necessary variables for onig_node_copy
    Node *tail = NULL;  // Assuming this is the node to be copied
    Node *copiedNode = NULL;

    // Call onig_node_copy
    int result = onig_node_copy(&copiedNode, tail);

    // Check the result of the function call
    if (result != 0) {
        fprintf(stderr, "Error in onig_node_copy: %d\n", result);
        return 1;
    }

    // Clean up (if necessary)
    // ...

    return 0;
}