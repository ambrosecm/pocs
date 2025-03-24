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

    // Read the input data (assuming it's a valid z_stream structure)
    mz_stream zstream;
    if (fread(&zstream, sizeof(mz_stream), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading z_stream data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call mz_deflateReset with the parsed z_stream
    int result = mz_deflateReset(&zstream);

    // Output the result for debugging
    printf("mz_deflateReset result: %d\n", result);

    return 0;
}