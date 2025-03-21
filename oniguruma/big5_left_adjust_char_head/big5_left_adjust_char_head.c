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
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read the input data
    UChar *start, *s;
    if (fscanf(inputFile, "%p %p", &start, &s) != 2) {
        fprintf(stderr, "Error reading pointers from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the big5_left_adjust_char_head function
    UChar *result = big5_left_adjust_char_head(start, s);

    // Output the result (for testing purposes)
    printf("Result: %p\n", result);

    return 0;
}