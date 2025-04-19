#include <stdio.h>
#include <stdlib.h>
#include "ming.h"  // Ensure SWFFont is defined here
#include "blocks/fdbfont.h"
#include "compat.c"
#include "blocks/shape.h"

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

    // Read the font and character from the input file
    SWFFont font;
    char c;
    if (fscanf(inputFile, "%p %c", &font, &c) != 2) {
        fprintf(stderr, "Error reading font and character from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Create a new SWFShape
    SWFShape s = newSWFShape();

    // Draw the scaled glyph using the font and character
    SWFShape_drawScaledGlyph(s, font, c, 1024.0);

    // Dump the outline of the shape
    char *out = SWFShape_dumpOutline(s);

    // Print the outline
    printf("%s\n", out);

    // Free the allocated memory for the outline
    free(out);

    // Destroy the SWFShape
    destroySWFShape(s);

    return 0;
}