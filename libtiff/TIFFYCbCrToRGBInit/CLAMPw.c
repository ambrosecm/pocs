#include <stdio.h>
#include <stdlib.h>
#include "tif_color.c"
#include <math.h>
#include "tiffiop.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error opening input file\n");
        return 1;
    }

    // Read input values from file
    float luma[3], refBlackWhite[6];
    for (int i = 0; i < 3; i++) {
        if (fscanf(input, "%f", &luma[i]) != 1) {
            fprintf(stderr, "Error reading luma values\n");
            fclose(input);
            return 1;
        }
    }
    for (int i = 0; i < 6; i++) {
        if (fscanf(input, "%f", &refBlackWhite[i]) != 1) {
            fprintf(stderr, "Error reading refBlackWhite values\n");
            fclose(input);
            return 1;
        }
    }
    fclose(input);

    // Initialize and call the function
    TIFFYCbCrToRGB ycbcr;
    if (TIFFYCbCrToRGBInit(&ycbcr, luma, refBlackWhite) != 0) {
        fprintf(stderr, "TIFFYCbCrToRGBInit failed\n");
        return 1;
    }

    return 0;
}