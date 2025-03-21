#include <stdio.h>
#include <stdlib.h>
#include "big5.c"
#include "regenc.h"

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

    // Read the input data
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    UChar *inputData = (UChar *)malloc(fileSize);
    if (!inputData) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    fread(inputData, 1, fileSize, inputFile);
    fclose(inputFile);

    // Prepare variables for the function call
    const UChar *pp = inputData;
    UChar lower[4]; // Assuming maximum 4 bytes for a multi-byte character
    int flag = 0;   // Default flag value

    // Call the function
    int result = onigenc_mbn_mbc_case_fold(ONIG_ENCODING_BIG5, flag, &pp, pp + fileSize, lower);

    // Output the result
    printf("Result: %d\n", result);
    if (result > 0) {
        printf("Lowercase character: ");
        for (int i = 0; i < result; i++) {
            printf("%02x ", lower[i]);
        }
        printf("\n");
    }

    // Clean up
    free(inputData);
    return 0;
}