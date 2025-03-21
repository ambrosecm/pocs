#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"
#include "regparse.h"

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

    // Read the bitset data from the file
    unsigned char bs[BITSET_REAL_SIZE];
    if (fread(bs, sizeof(unsigned char), BITSET_REAL_SIZE, inputFile) != BITSET_REAL_SIZE) {
        fprintf(stderr, "Error reading bitset data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the bitset_is_empty function
    int result = bitset_is_empty(bs);

    // Output the result
    printf("bitset_is_empty result: %d\n", result);

    return 0;
}