#include <stdio.h>
#include <stdlib.h>
#include "regposix.c"  // Include the necessary implementation file
#include "regint.h"    // Include internal definitions
#include "onigposix.h" // Include the POSIX API header file

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

    // Read the onig_posix_regex_t structure from the file
    onig_posix_regex_t regex;
    if (fread(&regex, sizeof(onig_posix_regex_t), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading onig_posix_regex_t from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the onig_posix_regfree function
    onig_posix_regfree(&regex);

    return 0;
}