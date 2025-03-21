#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"

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

    // Read the encoding from the file
    OnigEncoding encodings[1];  // Array of encodings
    if (fscanf(inputFile, "%d", (int*)&encodings[0]) != 1) {
        fprintf(stderr, "Error reading encoding from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Initialize Oniguruma with the array of encodings
    int r = onig_initialize(encodings, 1);
    if (r != 0) {
        fprintf(stderr, "Failed to initialize Oniguruma.\n");
        return 1;
    }

    return 0;
}