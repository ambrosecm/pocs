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

    BMP bmp = {0};
    if (bmp_load(&bmp, argv[1]) == -1) {
        fprintf(stderr, "Failed to load BMP file: %s\n", argv[1]);
        return 1;
    }

    void *encoded_data = jfif_encode(&bmp);
    if (!encoded_data) {
        fprintf(stderr, "Failed to encode BMP to JFIF\n");
        return 1;
    }

    // Clean up
    if (bmp.pdata) {
        free(bmp.pdata);
    }

    return 0;
}