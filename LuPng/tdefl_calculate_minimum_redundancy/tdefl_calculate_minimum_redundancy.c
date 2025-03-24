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

    // Read the number of elements from the file
    uint32_t num_elements;
    if (fscanf(inputFile, "%u", &num_elements) != 1) {
        fprintf(stderr, "Error reading number of elements from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Allocate memory for the frequencies array
    uint16_t *frequencies = (uint16_t *)malloc(num_elements * sizeof(uint16_t));
    if (!frequencies) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }

    // Read the frequencies from the file
    for (uint32_t i = 0; i < num_elements; i++) {
        if (fscanf(inputFile, "%hu", &frequencies[i]) != 1) {
            fprintf(stderr, "Error reading frequency from file.\n");
            free(frequencies);
            fclose(inputFile);
            return 1;
        }
    }

    // Close the file
    fclose(inputFile);

    // Call the tdefl_calculate_minimum_redundancy function
    tdefl_calculate_minimum_redundancy(frequencies, num_elements);

    // Free allocated memory
    free(frequencies);

    return 0;
}