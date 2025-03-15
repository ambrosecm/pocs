#include "bitstr.h"
#include "bmp.h"
#include "zigzag.h"
#include "stdefine.h"
#include <stdlib.h>
#include "huffman.h"
#include "color.h"
#include "quant.h"
#include <string.h>
#include "dct.h"
#include <stdio.h>
#include "jfif.c"
#include "jfif.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Load the JFIF structure from the input file
    void *jfif = jfif_load(argv[1]);
    if (!jfif) {
        fprintf(stderr, "Failed to load JFIF from file: %s\n", argv[1]);
        return 1;
    }

    // Call the jfif_free function to free the allocated memory
    jfif_free(jfif);

    return 0;
}