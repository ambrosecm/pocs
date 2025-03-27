#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

    // Read the character and table from the file
    widechar c;
    DisplayTableHeader *displayTable = NULL;
    if (fscanf(inputFile, "%hu", &c) != 1) {
        fprintf(stderr, "Error reading character from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the _lou_getDotsForChar function
    int result = _lou_getDotsForChar(c, displayTable);

    // Print the result
    printf("Result: %d\n", result);

    return 0;
}