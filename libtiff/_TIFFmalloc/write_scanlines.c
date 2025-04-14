#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiffio.h"
#include "strip.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open input file
    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Get file size
    fseek(inputFile, 0, SEEK_END);
    tsize_t size = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    // Allocate buffer and read file
    tdata_t buffer = _TIFFmalloc(size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }
    fread(buffer, 1, size, inputFile);
    fclose(inputFile);

    // Create dummy TIFF file for testing
    TIFF *tif = TIFFOpen("test.tif", "w");
    if (!tif) {
        fprintf(stderr, "Could not create test TIFF file\n");
        _TIFFfree(buffer);
        return 1;
    }

    // Set required TIFF tags (minimal set for testing)
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 256);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 256);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
    TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, 256);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

    // Call write_scanlines with the input data
    int result = write_scanlines(tif, buffer, size);

    // Cleanup
    _TIFFfree(buffer);
    TIFFClose(tif);

    return result;
}