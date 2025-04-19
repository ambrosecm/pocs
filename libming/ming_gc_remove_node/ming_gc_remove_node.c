#include "block.h"
#include "input.h"
#include "character.h"
#include "ming.h"
#include "dbl.c"
#include "dbl.h"
#include "method.h"
#include "ming_config.h"
#include <stdlib.h>
#include "error.h"
#include "libming.h"

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

    // Read the input data (assuming it's a pointer to a GC node)
    void *gcnode;
    if (fscanf(inputFile, "%p", &gcnode) != 1) {
        fprintf(stderr, "Error reading GC node from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the ming_gc_remove_node function
    ming_gc_remove_node(gcnode);

    return 0;
}