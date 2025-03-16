#include "tcpreplay.h"
#include <fcntl.h>
#include "common.h"
#include <limits.h>
#include <string.h>
#include "tcpreplay_api.h"
#include <errno.h>
#include "tcpreplay_opts.h"
#include <autoopts/options.h>
#include <stdio.h>
#include <sys/stat.h>
#include "config.h"
#include "defines.h"
#include <stdnoreturn.h>
#include <autoopts/usage-txt.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

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

    // Read the input values
    tOptions *pOptions;
    tOptDesc *pOptDesc;
    if (fscanf(inputFile, "%p %p", &pOptions, &pOptDesc) != 2) {
        fprintf(stderr, "Error reading values from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Call the optionNumericVal function
    optionNumericVal(pOptions, pOptDesc);

    return 0;
}