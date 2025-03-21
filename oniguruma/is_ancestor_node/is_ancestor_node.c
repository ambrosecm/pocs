#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"
#include "regparse.h"

// Assuming the necessary structures and functions are defined in the included headers

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

    // Read the input data (assuming the input is two node pointers)
    Node *ernode = NULL, *node = NULL;
    if (fscanf(inputFile, "%p %p", (void**)&ernode, (void**)&node) != 2) {
        fprintf(stderr, "Error reading node pointers from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the is_ancestor_node function
    if (is_ancestor_node(ernode, node)) {
        printf("The node is an ancestor.\n");
    } else {
        printf("The node is not an ancestor.\n");
    }

    return 0;
}