#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "fax2ps.c"
#include "libport.h"
#include "tiffiop.h"
#include "tiffio.h"
#include "tif_config.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Prepare arguments for main_
    char *new_argv[] = {
        argv[0],    // program name
        argv[1],     // input file
        NULL
    };
    int new_argc = 2;

    // Call main_ function with the prepared arguments
    return main_(new_argc, new_argv);
}