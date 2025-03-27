#include "config.h"  // Include config.h first
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
    widechar inputChars[256];
    int pos, direction;
    widechar pattern[256];
    TranslationTableHeader table;

    // Assuming the input file format is:
    // pos direction pattern_length pattern table_data
    if (fscanf(inputFile, "%d %d %hd", &pos, &direction, &pattern[0]) != 3) {
        fprintf(stderr, "Error reading input data from file.\n");
        fclose(inputFile);
        return 1;
    }

    for (int i = 1; i <= pattern[0]; i++) {
        if (fscanf(inputFile, "%hd", &pattern[i]) != 1) {
            fprintf(stderr, "Error reading pattern data from file.\n");
            fclose(inputFile);
            return 1;
        }
    }

    // Read table data (simplified for example)
    // In a real scenario, you would need to properly initialize the TranslationTableHeader
    if (fread(&table, sizeof(TranslationTableHeader), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading table data from file.\n");
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);

    // Call the _lou_pattern_check function
    int result = _lou_pattern_check(inputChars, pos, direction, pattern[0], pattern, &table);

    // Output the result
    printf("_lou_pattern_check result: %d\n", result);

    return 0;
}