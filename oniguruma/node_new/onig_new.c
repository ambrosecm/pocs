#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regcomp.c"
#include "regparse.h"
#include "oniguruma.h"

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

    // Read the pattern from the file
    char pattern[1024];
    if (fgets(pattern, sizeof(pattern), inputFile) == NULL) {
        fprintf(stderr, "Error reading pattern from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Initialize Oniguruma
    regex_t *reg;
    OnigErrorInfo einfo;
    OnigEncoding enc = ONIG_ENCODING_UTF8;
    OnigSyntaxType *syntax = ONIG_SYNTAX_DEFAULT;
    int option = ONIG_OPTION_NONE;

    // Call onig_new
    int r = onig_new(&reg, (const OnigUChar *)pattern, (const OnigUChar *)(pattern + strlen(pattern)), option, enc, syntax, &einfo);
    if (r != ONIG_NORMAL) {
        fprintf(stderr, "Error in onig_new: %d\n", r);
        return 1;
    }

    // Free the regex object
    onig_free(reg);

    return 0;
}