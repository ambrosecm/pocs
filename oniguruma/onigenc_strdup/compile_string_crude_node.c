#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"
#include "regparse.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Error opening file");
        return 1;
    }

    char *pattern = NULL;
    size_t len = 0;
    ssize_t read;

    // Read the entire line from the file
    read = getline(&pattern, &len, inputFile);
    if (read == -1) {
        fprintf(stderr, "Error reading pattern from file.\n");
        fclose(inputFile);
        return 1;
    }
    fclose(inputFile);

    // Remove newline if present
    if (pattern[read - 1] == '\n') {
        pattern[read - 1] = '\0';
    }

    // Initialize regex
    OnigRegex reg;
    OnigErrorInfo einfo;
    OnigEncoding enc = ONIG_ENCODING_ASCII;
    OnigSyntaxType *syntax = ONIG_SYNTAX_DEFAULT;

    int r = onig_new(&reg, (const OnigUChar *)pattern, 
                    (const OnigUChar *)(pattern + read - 1),
                    ONIG_OPTION_DEFAULT, enc, syntax, &einfo);
    if (r != ONIG_NORMAL) {
        char s[ONIG_MAX_ERROR_MESSAGE_LEN];
        onig_error_code_to_str((OnigUChar *)s, r, &einfo);
        fprintf(stderr, "ERROR: %s\n", s);
        free(pattern);
        return 1;
    }

    // Call the target function
    r = compile_string_crude_node((const OnigUChar *)pattern, reg);
    if (r != 0) {
        fprintf(stderr, "Error in compile_string_crude_node\n");
    }

    // Cleanup
    onig_free(reg);
    free(pattern);

    return 0;
}