#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"
#include "regparse.h"

// Function prototype for is_anychar_infinite_greedy
int is_anychar_infinite_greedy(QuantNode *qn);

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

    // Read the input data into a QuantNode structure
    QuantNode qn;
    if (fscanf(inputFile, "%d %d %d %d %d", 
               &qn.greedy, &qn.upper, &qn.lower, 
               (int*)&qn.emptiness, &qn.include_referred) != 5) {
        fprintf(stderr, "Error reading data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the is_anychar_infinite_greedy function
    int result = is_anychar_infinite_greedy(&qn);

    // Output the result (for debugging purposes)
    printf("Result: %d\n", result);

    return 0;
}