#include <config.h>  // 必须放在最前面
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdarg.h>
#include "compileTranslationTable.c"
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

    // Allocate memory for the TranslationTableHeader
    TranslationTableHeader *table = (TranslationTableHeader *)malloc(sizeof(TranslationTableHeader));
    if (!table) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    // Initialize the table
    table->characterClasses = NULL;
    table->nextCharacterClassAttribute = 1;  // CTC_Space

    // Read input data from the file and parse it (assuming the input is a list of character class names)
    char characterClassNames[100][MAXSTRING];
    int k = 0;
    while (fgets(characterClassNames[k], MAXSTRING, inputFile)) {
        // Remove newline character if present
        characterClassNames[k][strcspn(characterClassNames[k], "\n")] = 0;
        k++;
    }

    // Close the input file
    fclose(inputFile);

    // Allocate character classes based on the input
    for (int i = 0; i < k; i++) {
        widechar wname[MAXSTRING];
        int length = (int)strlen(characterClassNames[i]);
        for (int j = 0; j < length; j++) {
            wname[j] = (widechar)characterClassNames[i][j];
        }
        if (!addCharacterClass(NULL, wname, length, table, 0)) {
            deallocateCharacterClasses(table);
            free(table);
            return 1;
        }
    }

    // Deallocate character classes
    deallocateCharacterClasses(table);

    // Free the table
    free(table);

    return 0;
}