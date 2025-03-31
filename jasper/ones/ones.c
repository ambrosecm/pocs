#include "jasper/jas_image.h"
#include "jp2_cod.h"
#include "jasper/jas_malloc.h"
#include "jasper/jas_types.h"
#include <string.h>
#include "jasper/jas_debug.h"
#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include "jasper/jas_stream.h"

static inline uint_fast32_t ones(int n)
{
    assert(n >= 0);
    return (JAS_CAST(uint_fast32_t, 1) << n) - 1;
}

int main(int argc, char *argv[])
{
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

    int n;
    // Read the integer from the file
    if (fscanf(inputFile, "%d", &n) != 1) {
        fprintf(stderr, "Error reading integer from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the ones function
    uint_fast32_t result = ones(n);

    // Print the result (optional, for debugging)
    printf("Result: %u\n", result);

    return 0;
}