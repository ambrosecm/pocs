#include <stdio.h>
#include <stdlib.h>
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

    // Allocate memory for the mz_streamp structure
    mz_streamp stream = (mz_streamp)malloc(sizeof(mz_stream));
    if (!stream) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    // Read the input file into the mz_streamp structure
    if (fread(stream, sizeof(mz_stream), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading input file\n");
        fclose(inputFile);
        free(stream);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Call the mz_inflateEnd function
    int result = mz_inflateEnd(stream);

    // Free the allocated memory
    free(stream);

    // Return the result of mz_inflateEnd
    return result;
}