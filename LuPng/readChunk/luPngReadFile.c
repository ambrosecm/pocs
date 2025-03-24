#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "lupng.h"
#include "miniz.h"
#include "lupng.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Call the luPngReadFile function with the input file
    LuImage *img = luPngReadFile(argv[1]);

    if (img) {
        printf("PNG file successfully read.\n");
        // You can add further processing of the image here if needed
    } else {
        fprintf(stderr, "Failed to read PNG file.\n");
    }

    return 0;
}