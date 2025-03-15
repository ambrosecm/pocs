#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stdefine.h"
#include "bitstr.h"
#include "huffman.h"
#include "quant.h"
#include "zigzag.h"
#include "dct.h"
#include "bmp.h"
#include "color.h"
#include "jfif.h"
#include "jfif.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    int du[64];
    int qtab[64];

    for (int i = 0; i < 64; i++) {
        if (fscanf(inputFile, "%d", &du[i]) != 1) {
            fprintf(stderr, "Error reading data from file.\n");
            fclose(inputFile);
            return 1;
        }
    }

    for (int i = 0; i < 64; i++) {
        if (fscanf(inputFile, "%d", &qtab[i]) != 1) {
            fprintf(stderr, "Error reading data from file.\n");
            fclose(inputFile);
            return 1;
        }
    }

    fclose(inputFile);

    quant_encode(du, qtab);

    return 0;
}