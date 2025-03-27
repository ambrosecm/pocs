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
    CharsString source, dest;

    // Read the input file into the source CharsString
    source.length = 0;
    int ch;
    while ((ch = fgetc(inputFile)) != EOF && source.length < MAXSTRING) {
        source.chars[source.length++] = ch;
    }
    fclose(inputFile);

    // Call the compileSwapDots function
    if (!compileSwapDots(&file, &source, &dest)) {
        fprintf(stderr, "Error in compileSwapDots function\n");
        return 1;
    }

    // Output the result (optional)
    for (int i = 0; i < dest.length; i++) {
        printf("%c", dest.chars[i]);
    }
    printf("\n");

    return 0;
}