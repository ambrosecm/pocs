#include <stdio.h>
#include <stdlib.h>
#include "tiffio.h"  // Changed from tiffiop.h to tiffio.h for standard usage
#include "tiff.h"    // Added for TIFFCodec definition
#include "tif_dir.h" // Added for _TIFF* functions

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read the codec structure from file
    TIFFCodec *codec = (TIFFCodec *)malloc(sizeof(TIFFCodec));
    if (!codec) {
        fclose(inputFile);
        return 1;
    }

    // Read minimal data needed for the fuzz test
    if (fread(codec, sizeof(TIFFCodec), 1, inputFile) != 1) {
        free(codec);
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);

    // Initialize TIFF library (important for internal functions)
    TIFFGetVersion();

    // Call the target function
    TIFFUnRegisterCODEC(codec);

    free(codec);
    return 0;
}