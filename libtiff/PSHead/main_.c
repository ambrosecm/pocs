#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "libport.h"
#include "tiffio.h"
#include "tiff2ps.c"
#include "tif_config.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Prepare arguments for main_
    char *fuzz_argv[] = {
        argv[0],  // program name
        argv[1],  // input file
        NULL
    };
    int fuzz_argc = 2;

    // Call the target function with fuzzed input
    return main_(fuzz_argc, fuzz_argv);
}