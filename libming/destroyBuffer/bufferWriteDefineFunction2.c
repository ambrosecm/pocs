#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compile.h"
#include "actiontypes.h"
#include "ming.h"
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

    // Read the function name
    char func_name[256];
    if (fgets(func_name, sizeof(func_name), inputFile) == NULL) {
        fprintf(stderr, "Error reading function name from file.\n");
        fclose(inputFile);
        return 1;
    }
    // Remove newline character if present
    func_name[strcspn(func_name, "\n")] = '\0';

    // Read the number of parameters
    int num_args;
    if (fscanf(inputFile, "%d", &num_args) != 1) {
        fprintf(stderr, "Error reading number of parameters from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Read the parameters buffer
    char params_buffer[1024];
    if (fgets(params_buffer, sizeof(params_buffer), inputFile) == NULL) {
        fprintf(stderr, "Error reading parameters buffer from file.\n");
        fclose(inputFile);
        return 1;
    }
    // Remove newline character if present
    params_buffer[strcspn(params_buffer, "\n")] = '\0';

    // Read the code buffer
    char code_buffer[1024];
    if (fgets(code_buffer, sizeof(code_buffer), inputFile) == NULL) {
        fprintf(stderr, "Error reading code buffer from file.\n");
        fclose(inputFile);
        return 1;
    }
    // Remove newline character if present
    code_buffer[strcspn(code_buffer, "\n")] = '\0';

    // Read the flags
    int flags;
    if (fscanf(inputFile, "%d", &flags) != 1) {
        fprintf(stderr, "Error reading flags from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Create the output buffer
    Buffer out = newBuffer();

    // Allocate memory for the ASFunction structure
    ASFunction function = (ASFunction)malloc(sizeof(struct function_s));
    if (!function) {
        fprintf(stderr, "Memory allocation failed for ASFunction.\n");
        destroyBuffer(out);
        return 1;
    }

    // Initialize the ASFunction structure
    function->name = strdup(func_name);
    function->params.buffer = strdup(params_buffer);
    function->params.count = num_args;
    function->code = strdup(code_buffer);
    function->flags = flags;

    // Call the bufferWriteFunction
    int tagLen = bufferWriteFunction(out, function, 2);

    // Output the result
    printf("Tag length: %d\n", tagLen);

    // Clean up
    free(function->name);
    free(function->params.buffer);
    free(function->code);
    free(function);
    destroyBuffer(out);

    return 0;
}