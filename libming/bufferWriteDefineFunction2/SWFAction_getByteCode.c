#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ming.h"
#include "action.h"
#include "output.h"
#include "input.h"
#include "actioncompiler/compile.h"
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

    // Read the input file into a buffer
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

    // Create an SWFAction object from the buffer
    SWFAction action = newSWFAction(buffer);
    if (!action) {
        fprintf(stderr, "Failed to create SWFAction\n");
        free(buffer);
        return 1;
    }

    // Get the bytecode from the SWFAction object
    int length;
    const unsigned char *bytecode = SWFAction_getByteCode(action, &length);
    if (!bytecode) {
        fprintf(stderr, "Failed to get bytecode\n");
        destroySWFAction(action);
        free(buffer);
        return 1;
    }

    // Output the bytecode (for testing purposes)
    printf("Bytecode length: %d\n", length);
    for (int i = 0; i < length; i++) {
        printf("%02x ", bytecode[i]);
    }
    printf("\n");

    // Clean up
    destroySWFAction(action);
    free(buffer);

    return 0;
}