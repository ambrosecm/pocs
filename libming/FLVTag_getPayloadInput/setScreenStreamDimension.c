#include <stdlib.h>
#include <stdio.h>
#include "block.h"
#include "method.h"
#include "ming.h"
#include "flv.h"
#include "../displaylist.h"
#include "input.h"
#include "videostream.c"
#include "libming.h"
#include "character.h"
#include "videostream.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read the FLV tag from the file
    FLVTag tag;
    if (fread(&tag, sizeof(FLVTag), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading FLV tag from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Create a SWFVideoStream object
    SWFVideoStream stream = newSWFVideoStream();
    if (!stream) {
        fprintf(stderr, "Memory allocation failed for SWFVideoStream.\n");
        return 1;
    }

    // Call the setScreenStreamDimension function
    int ret = setScreenStreamDimension(stream, &tag);
    if (ret != 0) {
        fprintf(stderr, "Error in setScreenStreamDimension function.\n");
        destroySWFVideoStream(stream);
        return 1;
    }

    // Clean up
    destroySWFVideoStream(stream);

    return 0;
}