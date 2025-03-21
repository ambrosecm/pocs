#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regint.h"
#include "regexec.c"

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

    // Read the number of regex patterns from the file
    int n;
    if (fscanf(inputFile, "%d", &n) != 1) {
        fprintf(stderr, "Error reading the number of regex patterns from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Allocate memory for the regex patterns
    regex_t **regs = (regex_t **)malloc(sizeof(regex_t *) * n);
    if (!regs) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }

    // Read each regex pattern from the file
    for (int i = 0; i < n; i++) {
        char pattern[256];
        if (fscanf(inputFile, "%255s", pattern) != 1) {
            fprintf(stderr, "Error reading regex pattern from file.\n");
            fclose(inputFile);
            free(regs);
            return 1;
        }

        // Compile the regex pattern
        int err = onig_new(&regs[i], (const OnigUChar *)pattern, (const OnigUChar *)(pattern + strlen(pattern)),
                           ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT, NULL);
        if (err != ONIG_NORMAL) {
            fprintf(stderr, "Error compiling regex pattern: %s\n", pattern);
            fclose(inputFile);
            free(regs);
            return 1;
        }
    }

    // Close the input file
    fclose(inputFile);

    // Create a new regex set
    OnigRegSet *rset;
    int result = onig_regset_new(&rset, n, regs);  // Corrected argument order
    if (result != 0) {
        fprintf(stderr, "Error creating regex set.\n");
        for (int i = 0; i < n; i++) {
            onig_free(regs[i]);
        }
        free(regs);
        return 1;
    }

    // Free the regex patterns and the regex set
    for (int i = 0; i < n; i++) {
        onig_free(regs[i]);
    }
    free(regs);
    onig_regset_free(rset);

    return 0;
}