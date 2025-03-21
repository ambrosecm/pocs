#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"
#include "regparse.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Error opening file");
        return 1;
    }

    // Initialize the required structures
    Node node;
    regex_t reg;
    ParseEnv env;

    // Read the input file and populate the structures
    // Note: This is a simplified example. You may need to adjust this based on your actual input format.
    if (fscanf(inputFile, "%d", &node) != 1) {
        fprintf(stderr, "Error reading integer from file.\n");
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);

    // Call the function with the correct types
    int tlen = compile_length_tree(&node, &reg, &env);

    printf("Compile length: %d\n", tlen);

    return 0;
}