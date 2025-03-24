#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miniz.h"

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

    // Read the file content into a buffer
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    void *pZip = malloc(fileSize);
    if (!pZip) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    fread(pZip, 1, fileSize, inputFile);
    fclose(inputFile);

    // Call the mz_zip_reader_end_internal function with the correct number of arguments
    mz_bool result = mz_zip_reader_end_internal((mz_zip_archive *)pZip, MZ_FALSE);

    // Free allocated memory
    free(pZip);

    // Output the result
    printf("mz_zip_reader_end_internal returned: %d\n", result);

    return 0;
}