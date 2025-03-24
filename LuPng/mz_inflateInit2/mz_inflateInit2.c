#include <stdio.h>
#include <stdlib.h>
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

    // Read the windowBits value from the file
    int windowBits;
    if (fread(&windowBits, sizeof(int), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading windowBits from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Initialize the z_stream structure
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    // Call the mz_inflateInit2 function
    int ret = mz_inflateInit2(&strm, windowBits);
    if (ret != Z_OK) {
        fprintf(stderr, "mz_inflateInit2 failed with error code: %d\n", ret);
        return 1;
    }

    // Clean up
    mz_inflateEnd(&strm);

    return 0;
}