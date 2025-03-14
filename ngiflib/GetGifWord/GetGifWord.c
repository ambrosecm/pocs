#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "ngiflib.h"
#include "ngiflib.c"

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

    // Initialize ngiflib_img and ngiflib_decode_context structures
    struct ngiflib_img img = {0};
    struct ngiflib_decode_context context = {0};

    // Read input data into the context (simplified for fuzz testing)
    fread(&context, sizeof(context), 1, inputFile);
    fclose(inputFile);

    // Call GetGifWord function
    u16 result = GetGifWord(&img, &context);

    // Output the result (for debugging purposes)
    printf("GetGifWord result: %u\n", result);

    return 0;
}