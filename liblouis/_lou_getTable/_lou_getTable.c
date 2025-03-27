#include <config.h>  // 添加 config.h 头文件
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

    // Read the table list from the file
    char tableList[256];
    if (!fgets(tableList, sizeof(tableList), inputFile)) {
        fprintf(stderr, "Error reading table list from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Remove newline character if present
    tableList[strcspn(tableList, "\n")] = '\0';

    // Close the file
    fclose(inputFile);

    // Variables to hold the tables
    const TranslationTableHeader *translationTable = NULL;
    const DisplayTableHeader *displayTable = NULL;

    // Call the _lou_getTable function
    _lou_getTable(tableList, tableList, &translationTable, &displayTable);

    if (translationTable == NULL) {
        fprintf(stderr, "Failed to load translation table.\n");
        return 1;
    }

    // Print success message
    printf("Successfully loaded translation table.\n");

    return 0;
}