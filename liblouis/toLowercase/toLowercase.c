#include <config.h>  // 必须在最前面包含 config.h
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lou_translateString.c"
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

    // Read the input data from the file
    TranslationTableHeader table;
    TranslationTableCharacter character;

    // Example: Read the table and character data from the file
    fread(&table, sizeof(TranslationTableHeader), 1, inputFile);
    fread(&character, sizeof(TranslationTableCharacter), 1, inputFile);

    // Close the input file
    fclose(inputFile);

    // Call the toLowercase function
    widechar result = toLowercase(&table, &character);

    // Output the result (if needed)
    printf("toLowercase result: %d\n", result);

    return 0;
}