#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include "tiffio.h"
#include "tiffiop.h"
#include "tiffcrop.c"
#include "libport.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Read input file to get arguments for main_
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error opening input file\n");
        return 1;
    }

    // Count lines in input file to determine argument count
    int lines = 0;
    char ch;
    while(!feof(input)) {
        ch = fgetc(input);
        if(ch == '\n') {
            lines++;
        }
    }
    rewind(input);

    // Allocate and read arguments
    char **args = malloc((lines + 2) * sizeof(char*));
    args[0] = strdup("tiffcrop");  // program name
    size_t len = 0;
    ssize_t read;
    
    for (int i = 1; i <= lines; i++) {
        args[i] = NULL;
        if ((read = getline(&args[i], &len, input)) == -1) {
            break;
        }
        // Remove newline if present
        if (args[i][read-1] == '\n') {
            args[i][read-1] = '\0';
        }
    }
    fclose(input);
    args[lines+1] = NULL;  // NULL terminate

    // Call main_ with the arguments
    int result = main_(lines+1, args);

    // Cleanup
    for (int i = 0; i <= lines; i++) {
        free(args[i]);
    }
    free(args);

    return result;
}