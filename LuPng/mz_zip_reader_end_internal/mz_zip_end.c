#include <stdio.h>
#include <stdlib.h>
#include "miniz.h"

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

    // Read the ZIP archive handle from the file
    mz_zip_archive zip_archive;
    if (fread(&zip_archive, sizeof(mz_zip_archive), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading ZIP archive handle from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Call mz_zip_end to finalize and close the ZIP archive
    mz_bool result = mz_zip_end(&zip_archive);

    // Check the result of mz_zip_end
    if (result == MZ_FALSE) {
        fprintf(stderr, "Error finalizing ZIP archive.\n");
        return 1;
    }

    printf("ZIP archive finalized successfully.\n");
    return 0;
}