#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"
#include "regparse.h"

// Define the MinMax structure if it is not already defined in regparse.h
typedef struct {
    int min;
    int max;
} MinMax;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Declare MinMax structures and other variables
    MinMax d1, d2;
    int ae, am;

    // Read values from the input file
    if (fscanf(inputFile, "%d %d %d %d %d %d", &d1.min, &d1.max, &d2.min, &d2.max, &ae, &am) != 6) {
        fprintf(stderr, "Error reading values from file.\n");
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);

    // Call the comp_distance_value function
    int result = comp_distance_value(&d1, &d2, ae, am);

    // Output the result (optional)
    printf("Result: %d\n", result);

    return 0;
}