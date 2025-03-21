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

    // Variables to store the input data
    char *alloc_base = NULL;
    StackType *stk_base = NULL;
    StackType *stk_end = NULL;
    StackType *stk = NULL;
    int is_alloca = 0;
    struct MatchStackArg *msa = NULL;  // Changed to struct MatchStackArg

    // Read the input data from the file
    if (fscanf(inputFile, "%p %p %p %p %d %p", &alloc_base, &stk_base, &stk_end, &stk, &is_alloca, &msa) != 6) {
        fprintf(stderr, "Error reading input data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Call the stack_double function
    int result = stack_double(&alloc_base, &stk_base, &stk_end, &stk, &is_alloca, msa);

    // Output the result (for debugging purposes)
    printf("stack_double returned: %d\n", result);

    return 0;
}