#include <stdlib.h>
#include <stdio.h>
#include "fillstyle.h"
#include "font.h"
#include "matrix.h"
#include "ming.h"
#include "output.h"
#include "shape.h"
#include "rect.h"
#include "libming.h"
#include "character.h"
#include "linestyle.h"
#include <stdarg.h>

// Define the SWFLineStyle structure
struct SWFLineStyle_s {
    int width;
    int color;
};

typedef struct SWFLineStyle_s *SWFLineStyle;

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

    // Read the number of lines
    int nLines;
    if (fscanf(inputFile, "%d", &nLines) != 1) {
        fprintf(stderr, "Error reading number of lines from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Allocate memory for line styles
    SWFLineStyle lines = (SWFLineStyle)malloc(nLines * sizeof(struct SWFLineStyle_s));
    if (!lines) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }

    // Read line styles from the file
    for (int i = 0; i < nLines; ++i) {
        if (fscanf(inputFile, "%d %d", &lines[i].width, &lines[i].color) != 2) {
            fprintf(stderr, "Error reading line style from file.\n");
            free(lines);
            fclose(inputFile);
            return 1;
        }
    }

    // Close the file
    fclose(inputFile);

    // Create a new SWFOutput object
    SWFOutput out = newSWFOutput();

    // Call the SWFOutput_writeLineStyles function
    SWFOutput_writeLineStyles(out, lines, nLines, SWF_DEFINESHAPE4, NULL);

    // Free allocated memory
    free(lines);

    return 0;
}