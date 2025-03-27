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
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Initialize FileInfo and CharsString structures
    FileInfo file;
    CharsString token;
    CharsString result;

    // Read the input file into the token CharsString
    token.length = 0;
    int ch;
    while ((ch = fgetc(inputFile)) != EOF && token.length < MAXSTRING) {
        token.chars[token.length++] = (widechar)ch;
    }
    fclose(inputFile);

    // Call the parseChars function
    if (!parseChars(&file, &result, &token)) {
        fprintf(stderr, "Error parsing characters\n");
        return 1;
    }

    // Output the result
    for (int i = 0; i < result.length; i++) {
        printf("%c", (char)result.chars[i]);
    }
    printf("\n");

    return 0;
}