#include <config.h>  // Must be included first
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "internal.h"
#include <sys/stat.h>
#include <ctype.h>
#include <stdarg.h>
#include "compileTranslationTable.c"

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

    // Initialize the TranslationTableHeader
    TranslationTableHeader *table = (TranslationTableHeader *)malloc(sizeof(TranslationTableHeader));
    if (!table) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }
    memset(table, 0, sizeof(TranslationTableHeader));

    // Initialize the TranslationTableRule
    TranslationTableRule rule;
    memset(&rule, 0, sizeof(TranslationTableRule));

    // Read the rule data from the input file
    if (fscanf(inputFile, "%hd %hd %hd %c", &rule.opcode, &rule.charslen, &rule.dotslen, &rule.nocross) != 4) {
        fprintf(stderr, "Error reading rule data from file.\n");
        fclose(inputFile);
        free(table);
        return 1;
    }

    // Allocate space for the rule in the table
    TranslationTableOffset ruleOffset;
    if (!allocateSpaceInTranslationTable(NULL, &ruleOffset, sizeof(TranslationTableRule), &table)) {
        fprintf(stderr, "Failed to allocate space in translation table.\n");
        fclose(inputFile);
        free(table);
        return 1;
    }

    // Add the rule to the table
    if (!addBackwardPassRule(ruleOffset, &rule, table)) {
        fprintf(stderr, "Failed to add backward pass rule.\n");
        fclose(inputFile);
        free(table);
        return 1;
    }

    // Clean up
    fclose(inputFile);
    free(table);

    return 0;
}