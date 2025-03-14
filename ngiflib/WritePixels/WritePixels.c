#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "ngiflib.c"
#include "ngiflib.h"
#include <stdlib.h>

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

    // Initialize the GIF image structure
    struct ngiflib_gif gif;
    struct ngiflib_img img;
    img.parent = &gif;

    // Read necessary values from the input file
    fscanf(inputFile, "%hu %hu %hu %hu", &img.posX, &img.posY, &img.width, &img.height);

    // Initialize the decode context
    struct ngiflib_decode_context context;
    context.Xtogo = img.width;
    context.curY = img.posY;

    // Allocate memory for the pixel buffer
    u8 *pixels = (u8 *)malloc(img.width * img.height);
    if (!pixels) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    // Read pixel data from the input file
    for (int i = 0; i < img.width * img.height; i++) {
        fscanf(inputFile, "%hhu", &pixels[i]);
    }

    // Call the WritePixels function
    WritePixels(&img, &context, pixels, img.width * img.height);

    // Clean up
    free(pixels);
    fclose(inputFile);

    return 0;
}