#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include "libport.h"
#include "tiffiop.h"
#include "tiffdump.c"
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
        argv[0],  // program name
        argv[1],  // input file
        NULL
    };
    int new_argc = 2;

    // Call the target function
    return main_(new_argc, new_argv);
}