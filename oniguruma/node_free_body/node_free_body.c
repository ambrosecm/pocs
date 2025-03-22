#include <stdio.h>
#include <stdlib.h>
#include "regint.h"
#include "st.h"
#include "regparse.c"  // Include the .c file directly if necessary

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the file
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

    // Read data from the file into the Node structure
    if (fread(node, sizeof(Node), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading data from file\n");
        fclose(inputFile);
        free(node);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the node_free_body function
    node_free_body(node);

    // Free the allocated memory
    free(node);

    return 0;
}