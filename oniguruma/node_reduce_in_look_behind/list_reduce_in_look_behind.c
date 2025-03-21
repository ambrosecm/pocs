#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"
#include "regparse.h"

int list_reduce_in_look_behind(Node* node);

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

    // Read the input data (assuming it's a Node structure)
    Node node;
    if (fread(&node, sizeof(Node), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading Node from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the list_reduce_in_look_behind function
    int result = list_reduce_in_look_behind(&node);

    // Output the result (for debugging purposes)
    printf("Result: %d\n", result);

    return 0;
}