#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "libport.h"
#include "tiffio.h"
#include "tif_config.h"
#include "tiffcp.c"

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

    // Read input parameters from file
    uint32_t rows, cols;
    int outskew, inskew;
    tsample_t spp;
    int bytes_per_sample;
    
    if (fread(&rows, sizeof(uint32_t), 1, inputFile) != 1 ||
        fread(&cols, sizeof(uint32_t), 1, inputFile) != 1 ||
        fread(&outskew, sizeof(int), 1, inputFile) != 1 ||
        fread(&inskew, sizeof(int), 1, inputFile) != 1 ||
        fread(&spp, sizeof(tsample_t), 1, inputFile) != 1 ||
        fread(&bytes_per_sample, sizeof(int), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading parameters from file\n");
        fclose(inputFile);
        return 1;
    }

    // Calculate buffer sizes
    size_t in_size = cols * spp * bytes_per_sample * rows;
    size_t out_size = cols * spp * bytes_per_sample * rows;

    // Allocate buffers
    uint8_t *in = (uint8_t *)malloc(in_size);
    uint8_t *out = (uint8_t *)malloc(out_size);
    
    if (!in || !out) {
        fprintf(stderr, "Memory allocation failed\n");
        free(in);
        free(out);
        fclose(inputFile);
        return 1;
    }

    // Read input buffer data
    if (fread(in, 1, in_size, inputFile) != in_size) {
        fprintf(stderr, "Error reading buffer data from file\n");
        free(in);
        free(out);
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);

    // Call the target function
    cpSeparateBufToContigBuf(out, in, rows, cols, outskew, inskew, spp, bytes_per_sample);

    // Clean up
    free(in);
    free(out);

    return 0;
}