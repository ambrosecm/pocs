#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lou_translateString.c"
#include "internal.h"

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

    // Read the index from the file
    int idx;
    if (fscanf(inputFile, "%d", &idx) != 1) {
        fprintf(stderr, "Error reading index from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the releaseStringBuffer function
    releaseStringBuffer(idx);

    return 0;
}