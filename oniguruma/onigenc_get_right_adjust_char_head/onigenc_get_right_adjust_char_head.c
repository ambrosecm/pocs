#include <stdio.h>
#include <stdlib.h>
#include "regint.h"
#include "regexec.c"

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

    // Read the input data from the file
    UChar *start, *s;
    if (fscanf(inputFile, "%p %p", &start, &s) != 2) {
        fprintf(stderr, "Error reading input data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the onigenc_get_right_adjust_char_head function
    OnigEncoding enc = ONIG_ENCODING_UTF8; // Assuming UTF-8 encoding for simplicity
    UChar *result = onigenc_get_right_adjust_char_head(enc, start, s);

    // Output the result (for debugging purposes)
    printf("Result: %p\n", result);

    return 0;
}