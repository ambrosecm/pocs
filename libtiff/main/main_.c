#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "libport.h"
#include "tiffiop.h"
#include "tif_config.h"
#include "tiffinfo.c"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Read the input file and prepare arguments for main_
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening input file");
        return 1;
    }

    // Count lines to determine argument count
    int lines = 0;
    char ch;
    while(!feof(input)) {
        ch = fgetc(input);
        if(ch == '\n') {
            lines++;
        }
    }
    rewind(input);

    // Allocate memory for arguments
    char **args = malloc((lines + 2) * sizeof(char*));
    if (!args) {
        fclose(input);
        return 1;
    }

    // Read arguments from file
    args[0] = strdup("tiffinfo");  // program name
    size_t len = 0;
    for (int i = 1; i <= lines; i++) {
        args[i] = NULL;
        if (getline(&args[i], &len, input) == -1) {
            free(args[i]);
            args[i] = NULL;
            break;
        }
        // Remove newline if present
        char *nl = strchr(args[i], '\n');
        if (nl) *nl = '\0';
    }
    fclose(input);

    // Call main_ function
    int ret = main_(lines + 1, args);

    // Cleanup
    for (int i = 0; i <= lines; i++) {
        free(args[i]);
    }
    free(args);

    return ret;
}