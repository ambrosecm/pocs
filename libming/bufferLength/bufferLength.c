#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compile.h"
#include "actiontypes.h"
#include <unistd.h>
#include "blocks/error.h"
#include "ming.h"
#include <ctype.h>
#include "compile.c"
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

    // Read the buffer data from the file
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    fread(buffer, 1, fileSize, inputFile);
    buffer[fileSize] = '\0'; // Null-terminate the buffer

    fclose(inputFile);

    // Call the bufferLength function
    int len = bufferLength(buffer);

    // Output the result
    printf("Buffer length: %d\n", len);

    // Free the allocated buffer
    free(buffer);

    return 0;
}