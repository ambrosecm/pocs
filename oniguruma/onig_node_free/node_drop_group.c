#include <stdio.h>
#include <stdlib.h>
#include "regint.h"
#include "st.h"
#include "regparse.c"
#include "regparse.h"

// Assuming node_drop_group is defined in one of the included headers
// and has the following signature:
// void node_drop_group(Node* node);

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

    // Read the input data from the file
    // Assuming the input file contains the necessary data to initialize a Node structure
    Node node;
    if (fread(&node, sizeof(Node), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading Node data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Call the node_drop_group function
    node_drop_group(&node);

    return 0;
}