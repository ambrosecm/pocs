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
    int node_type;
    if (fscanf(inputFile, "%d", &node_type) != 1) {
        fprintf(stderr, "Error reading node type from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Initialize the necessary structures
    regex_t *reg;
    OnigRegion *region = onig_region_new();
    OnigErrorInfo einfo;
    OnigEncoding enc = ONIG_ENCODING_ASCII;
    OnigSyntaxType syntax = *ONIG_SYNTAX_DEFAULT;  // Dereference the pointer

    // Initialize the regex engine
    int r = onig_new(&reg, NULL, 0, ONIG_OPTION_DEFAULT, enc, &syntax, &einfo);
    if (r != ONIG_NORMAL) {
        fprintf(stderr, "Error initializing regex engine.\n");
        return 1;
    }

    // Create a dummy node structure for testing
    Node node;
    ND_TYPE(&node) = node_type;  // Pass a pointer to node

    // Call the compile_tree function
    r = compile_tree(&node, reg, NULL);
    if (r != 0) {
        fprintf(stderr, "Error compiling tree.\n");
        onig_free(reg);
        onig_region_free(region, 1);
        return 1;
    }

    // Clean up
    onig_free(reg);
    onig_region_free(region, 1);

    return 0;
}