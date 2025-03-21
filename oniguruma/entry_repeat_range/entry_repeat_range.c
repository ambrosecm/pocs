#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"
#include "regparse.h"

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

    // Initialize the regex structure
    regex_t reg;
    reg.repeat_range_alloc = 0;
    reg.num_repeat = 0;

    // Read the parameters from the file
    int id, lower, upper, ops_index;
    if (fscanf(inputFile, "%d %d %d %d", &id, &lower, &upper, &ops_index) != 4) {
        fprintf(stderr, "Error reading parameters from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the entry_repeat_range function
    int result = entry_repeat_range(&reg, id, lower, upper, ops_index);
    if (result != 0) {
        fprintf(stderr, "Error in entry_repeat_range function.\n");
        return 1;
    }

    // Free allocated memory
    if (reg.repeat_range) {
        free(reg.repeat_range);
    }

    return 0;
}