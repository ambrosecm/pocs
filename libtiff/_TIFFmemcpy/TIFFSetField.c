#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "tiffio.h"
#include "tiff.h"

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

    TIFF *tif = TIFFOpen("dummy.tif", "w");
    if (!tif) {
        fprintf(stderr, "Could not create dummy TIFF file\n");
        fclose(inputFile);
        return 1;
    }

    uint32_t tag;
    char value[256];
    
    if (fread(&tag, sizeof(uint32_t), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading tag from file\n");
        fclose(inputFile);
        TIFFClose(tif);
        return 1;
    }

    size_t value_len = fread(value, 1, sizeof(value), inputFile);
    if (value_len == 0) {
        fprintf(stderr, "Error reading value from file\n");
        fclose(inputFile);
        TIFFClose(tif);
        return 1;
    }

    TIFFSetField(tif, tag, value);

    fclose(inputFile);
    TIFFClose(tif);
    return 0;
}