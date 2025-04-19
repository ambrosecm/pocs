#include <stdio.h>
#include <stdlib.h>
#include "fdbfont.c"
#include "movie.h"
#include "libming.h"
#include "character.h"
#include "input.h"
#include "shape.h"
#include "utf8.h"
#include "method.h"
#include "error.h"
#include "font.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    SWFInput input = newSWFInput_file(file);
    if (input == NULL) {
        fprintf(stderr, "Error creating SWFInput from file.\n");
        fclose(file);
        return 1;
    }

    SWFFont font = loadSWFFontFromInput(input);
    if (font == NULL) {
        fprintf(stderr, "Error loading SWFFont from input.\n");
        destroySWFInput(input);
        fclose(file);
        return 1;
    }

    destroySWFInput(input);
    fclose(file);

    // Optionally, you can add code here to use the loaded font for further testing.

    return 0;
}