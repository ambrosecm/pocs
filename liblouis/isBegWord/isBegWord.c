#include <config.h>  // 确保在代码的最开始包含 config.h
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "internal.h"
#include "lou_backTranslateString.c"

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
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), inputFile) == NULL) {
        fprintf(stderr, "Error reading from file.\n");
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);

    // Initialize the TranslationTableHeader and OutString structures
    TranslationTableHeader table;
    OutString output;

    // Populate the output structure with the input data
    output.length = strlen(buffer);
    output.chars = (widechar *)buffer;

    // Call the isBegWord function
    int result = isBegWord(&table, &output);

    // Print the result
    printf("isBegWord result: %d\n", result);

    return 0;
}