#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "miniz.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Get the file size
    fseek(inputFile, 0, SEEK_END);
    size_t inputSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    // Allocate memory for the input data
    void *pCompressedData = malloc(inputSize);
    if (!pCompressedData) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    // Read the compressed data from the file
    if (fread(pCompressedData, 1, inputSize, inputFile) != inputSize) {
        fprintf(stderr, "Error reading file\n");
        free(pCompressedData);
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);

    // Decompress the data using tinfl_decompress_mem_to_heap
    size_t out_len;
    void *pDecompressedData = tinfl_decompress_mem_to_heap(pCompressedData, inputSize, &out_len, 0);
    if (!pDecompressedData) {
        fprintf(stderr, "Decompression failed\n");
        free(pCompressedData);
        return 1;
    }

    // Output the decompressed data size
    printf("Decompressed data size: %zu\n", out_len);

    // Clean up
    free(pCompressedData);
    free(pDecompressedData);

    return 0;
}