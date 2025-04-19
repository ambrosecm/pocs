#include <stdio.h>
#include <stdlib.h>
#include "button.h"
#include "outputblock.h"
#include "filter.h"
#include "../position.h"
#include "soundinstance.h"
#include "character.h"
#include "button.c"
#include "ming.h"
#include "matrix.h"
#include "method.h"
#include "browserfont.h"
#include "action.h"
#include "scalinggrid.h"
#include "error.h"
#include "libming.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    int flags;
    SWFCharacter character;
    SWFButton button;

    // Read input data from file
    if (fscanf(inputFile, "%d %p %p", &flags, &character, &button) != 3) {
        fprintf(stderr, "Error reading input data from file.\n");
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);

    // Create a new matrix
    SWFMatrix m = newSWFMatrix(1.0, 0, 0, 1.0, 0, 0);

    // Add the character as a dependency to the button
    SWFCharacter_addDependency((SWFCharacter)button, (SWFCharacter)character);

    // Set the character as finished
    SWFCharacter_setFinished(character);

    // Add the record to the button
    SWFButton_addRecord(button, newSWFButtonRecord(flags, character, 0, m));

    return 0;
}