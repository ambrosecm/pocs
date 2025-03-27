#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

    // Read the file name and line number for the FileInfo structure
    char fileName[256];
    int lineNumber;
    if (fscanf(inputFile, "%255s %d", fileName, &lineNumber) != 2) {
        fprintf(stderr, "Error reading file name and line number from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Read the warning message format string
    char format[256];
    if (fgets(format, sizeof(format), inputFile) == NULL) {
        fprintf(stderr, "Error reading format string from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Remove the newline character from the format string if present
    format[strcspn(format, "\n")] = '\0';

    // Create the FileInfo structure
    FileInfo file;
    file.fileName = fileName;
    file.lineNumber = lineNumber;

    // Call the compileWarning function
    compileWarning(&file, format);

    // Close the input file
    fclose(inputFile);

    return 0;
}