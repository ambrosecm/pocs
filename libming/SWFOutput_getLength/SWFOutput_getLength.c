#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "fromswf.h"
#include "output.h"
#include "input.h"
#include "character.h"
#include "ming.h"
#include "method.h"
#include "ming_config.h"
#include <zlib.h>
#include "error.h"
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

    // Read the SWFPrebuiltClip structure from the file
    SWFPrebuiltClip clip = (SWFPrebuiltClip)malloc(sizeof(struct SWFPrebuiltClip_s));
    if (!clip) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }

    // Initialize the display member (assuming it's a pointer to SWFOutput)
    clip->display = (SWFOutput *)malloc(sizeof(SWFOutput));
    if (!clip->display) {
        fprintf(stderr, "Memory allocation for display failed.\n");
        free(clip);
        fclose(inputFile);
        return 1;
    }

    // Read the SWFPrebuiltClip structure from the file
    if (fread(clip, sizeof(struct SWFPrebuiltClip_s), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading SWFPrebuiltClip from file.\n");
        fclose(inputFile);
        free(clip->display);
        free(clip);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the SWFOutput_getLength function
    int length = SWFOutput_getLength(clip->display);

    // Output the result
    printf("SWFOutput_getLength returned: %d\n", length);

    // Free allocated memory
    free(clip->display);
    free(clip);

    return 0;
}