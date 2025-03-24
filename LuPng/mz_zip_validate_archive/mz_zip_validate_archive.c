#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/stat.h>
#include <time.h>
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

    // Get the file size
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    // Allocate memory for the file data
    uint8_t *fileData = (uint8_t *)malloc(fileSize);
    if (!fileData) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    // Read the file data
    if (fread(fileData, 1, fileSize, inputFile) != fileSize) {
        fprintf(stderr, "Error reading file data\n");
        free(fileData);
        fclose(inputFile);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Call the mz_zip_validate_archive function
    int result = mz_zip_validate_archive(fileData, fileSize);

    // Free the allocated memory
    free(fileData);

    // Output the result
    printf("Validation result: %d\n", result);

    return 0;
}