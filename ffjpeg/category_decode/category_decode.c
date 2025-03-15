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

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    int code, size;
    if (fscanf(inputFile, "%d %d", &code, &size) != 2) {
        fprintf(stderr, "Error reading integers from file.\n");
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);

    int result = category_decode(code, size);
    printf("Result: %d\n", result);

    return 0;
}