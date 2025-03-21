#include <stdio.h>
#include <stdlib.h>
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

    // Read the necessary parameters from the file
    int n;
    OnigRegion *region;
    if (fscanf(inputFile, "%p %d", &region, &n) != 2) {
        fprintf(stderr, "Error reading parameters from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Call the onig_region_resize_clear function
    int result = onig_region_resize_clear(region, n);

    // Output the result (for debugging purposes)
    printf("onig_region_resize_clear returned: %d\n", result);

    return 0;
}