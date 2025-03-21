#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regenc.c"
#include "config.h"
#include "regint.h"
#include "oniguruma.h"

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

    // Read the input string from the file
    char input[1024];
    if (fgets(input, sizeof(input), inputFile) == NULL) {
        fprintf(stderr, "Error reading input from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Remove newline character if present
    input[strcspn(input, "\n")] = '\0';

    // Initialize the encoding (e.g., UTF-8)
    OnigEncoding enc = ONIG_ENCODING_UTF8;

    // Call the onigenc_str_bytelen_null function
    int length = onigenc_str_bytelen_null(enc, (const unsigned char *)input);

    // Print the result
    printf("Length of the string: %d\n", length);

    return 0;
}