#include <stdio.h>
#include <stdlib.h>
#include "placeobject.h"
#include "action.h"
#include "output.h"
#include "block.h"
#include "method.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile)
    {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read action data from file
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    byte *actionData = malloc(fileSize);
    if (!actionData)
    {
        fclose(inputFile);
        return 1;
    }

    fread(actionData, 1, fileSize, inputFile);
    fclose(inputFile);

    // Create action
    SWFAction action = newSWFAction((const char *)actionData);
    SWFOutput out = newSWFOutput();

    // Call the target function
    SWFOutput_writeAction(out, action);

    // Cleanup
    destroySWFAction(action);
    destroySWFOutput(out);
    free(actionData);

    return 0;
}