#include "blocktypes.h"
#include "output.h"
#include "character.h"
#include "ming.h"
#include "rect.h"
#include "gradient.h"  // Ensure this header contains the full definition of SWFGradient
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "fillstyle.h"
#include "libming.h"

// Define the SWFGradient structure if not already defined in gradient.h
struct SWFGradient_s {
    int nGrads;
    struct {
        unsigned char ratio;
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } entries[16];  // Assuming a maximum of 16 gradient entries
    int isFocalGradient;
    float focalPoint;
};

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

    // Read the shapeType and gradient data from the file
    int shapeType;
    struct SWFGradient_s gradient;
    SWFOutput out;

    if (fscanf(inputFile, "%d", &shapeType) != 1) {
        fprintf(stderr, "Error reading shapeType from file.\n");
        fclose(inputFile);
        return 1;
    }

    if (fscanf(inputFile, "%d", &gradient.nGrads) != 1) {
        fprintf(stderr, "Error reading nGrads from file.\n");
        fclose(inputFile);
        return 1;
    }

    for (int i = 0; i < gradient.nGrads; ++i) {
        if (fscanf(inputFile, "%hhu %hhu %hhu %hhu %hhu",
                   &gradient.entries[i].ratio,
                   &gradient.entries[i].r,
                   &gradient.entries[i].g,
                   &gradient.entries[i].b,
                   &gradient.entries[i].a) != 5) {
            fprintf(stderr, "Error reading gradient entries from file.\n");
            fclose(inputFile);
            return 1;
        }
    }

    if (fscanf(inputFile, "%d %f", &gradient.isFocalGradient, &gradient.focalPoint) != 2) {
        fprintf(stderr, "Error reading focal gradient data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the SWFOutput_writeGradient function
    SWFOutput_writeGradient(out, (SWFGradient)&gradient, shapeType);

    return 0;
}