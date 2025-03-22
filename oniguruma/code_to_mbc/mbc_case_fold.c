#include <stdio.h>
#include <stdlib.h>
#include "regenc.h"  // Ensure this includes the definition of UChar and mbc_case_fold
#include "utf8.c"    // Include the .c file instead of the .h file

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the file
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read a character from the file
    UChar inputChar;
    if (fread(&inputChar, sizeof(UChar), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading character from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Set up variables for mbc_case_fold
    const UChar *pp = &inputChar;
    const UChar *end = pp + 1;  // Assuming the input character length is 1
    OnigCaseFoldType flag = ONIGENC_CASE_FOLD_MIN;
    UChar fold;

    // Call mbc_case_fold
    int result = mbc_case_fold(flag, &pp, end, &fold);

    // Output the result
    printf("Result: %d, Folded Char: %c\n", result, fold);

    return 0;
}