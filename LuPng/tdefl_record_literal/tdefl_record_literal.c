#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "miniz.h"

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
    uint8_t literal;
    if (fscanf(inputFile, "%hhu", &literal) != 1) {
        fprintf(stderr, "Error reading literal from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Initialize the compressor
    tdefl_compressor *pComp = (tdefl_compressor *)malloc(sizeof(tdefl_compressor));
    if (!pComp) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Call tdefl_record_literal
    tdefl_record_literal(pComp, literal);

    // Free the compressor
    free(pComp);

    return 0;
}