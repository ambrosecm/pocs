#include <stdio.h>
#include <stdlib.h>
#include "font.h"  // Ensure this header file is included for SWFFont_getGlyphCount

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

    // Read the SWFFont object pointer from the file
    SWFFont font;
    if (fscanf(inputFile, "%p", &font) != 1) {
        fprintf(stderr, "Error reading SWFFont object from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the SWFFont_getGlyphCount function
    int glyphCount = SWFFont_getGlyphCount(font);

    // Print the result
    printf("Glyph Count: %d\n", glyphCount);

    return 0;
}