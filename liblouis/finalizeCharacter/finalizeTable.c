#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compileTranslationTable.c"
#include <stddef.h>
#include "internal.h"
#include <sys/stat.h>
#include <ctype.h>
#include <stdarg.h>

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

    // Read the TranslationTableHeader from the file
    TranslationTableHeader *table = (TranslationTableHeader *)malloc(sizeof(TranslationTableHeader));
    if (!table) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    if (fread(table, sizeof(TranslationTableHeader), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading TranslationTableHeader from file\n");
        fclose(inputFile);
        free(table);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the finalizeTable function
    if (!finalizeTable(table)) {
        fprintf(stderr, "Failed to finalize table\n");
        free(table);
        return 1;
    }

    // Free allocated memory
    free(table);

    return 0;
}