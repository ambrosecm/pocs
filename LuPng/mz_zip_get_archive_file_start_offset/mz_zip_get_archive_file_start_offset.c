#include <stdio.h>
#include <stdlib.h>
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
    void *pZipArchive = malloc(fileSize);
    if (!pZipArchive) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    // Read the file data into memory
    if (fread(pZipArchive, 1, fileSize, inputFile) != fileSize) {
        fprintf(stderr, "Error reading file data\n");
        free(pZipArchive);
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the function to get the archive file start offset
    size_t offset = mz_zip_get_archive_file_start_offset(pZipArchive);

    // Print the result
    printf("Archive file start offset: %zu\n", offset);

    // Free the allocated memory
    free(pZipArchive);

    return 0;
}