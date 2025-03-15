#include "bitstr.h"
#include "stdefine.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bitstr.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Assuming the input file contains the type of stream (BITSTR_MEM or BITSTR_FILE)
    int type;
    if (fscanf(inputFile, "%d", &type) != 1) {
        fprintf(stderr, "Error reading stream type from file.\n");
        fclose(inputFile);
        return 1;
    }

    void *stream = malloc(sizeof(int));
    if (!stream) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }

    *(int*)stream = type;

    // Call bitstr_getc with the prepared stream
    int result = bitstr_getc(stream);

    printf("bitstr_getc returned: %d\n", result);

    free(stream);
    fclose(inputFile);
    return 0;
}