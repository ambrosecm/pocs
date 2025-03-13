#include <stdio.h>
#include <stdlib.h>
#include "ngiflib.h"
#include "ngiflib.c"

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

    // Read the GIF structure from the file
    struct ngiflib_gif gif;
    if (fread(&gif, sizeof(struct ngiflib_gif), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading GIF structure from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call GifDestroy which will internally call GifImgDestroy
    GifDestroy(&gif);

    return 0;
}