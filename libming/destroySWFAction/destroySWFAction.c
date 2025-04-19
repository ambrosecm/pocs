#include <stdio.h>
#include <stdlib.h>
#include "button.h"
#include "outputblock.h"
#include "filter.h"
#include "../position.h"
#include "soundinstance.h"
#include "character.h"
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

    // Open the input file
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read the number of actions from the file
    int nActions;
    if (fscanf(inputFile, "%d", &nActions) != 1) {
        fprintf(stderr, "Error reading number of actions from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Create a new SWFButton using the library function
    SWFButton button = newSWFButton();
    if (!button) {
        fprintf(stderr, "Failed to create SWFButton.\n");
        fclose(inputFile);
        return 1;
    }

    // Allocate memory for the actions array
    SWFAction *actions = (SWFAction *)malloc(nActions * sizeof(SWFAction));
    if (!actions) {
        fprintf(stderr, "Memory allocation failed.\n");
        destroySWFButton(button);
        fclose(inputFile);
        return 1;
    }

    // Read each action from the file and assign it to the button
    for (int i = 0; i < nActions; ++i) {
        if (fscanf(inputFile, "%p", &actions[i]) != 1) {
            fprintf(stderr, "Error reading action from file.\n");
            free(actions);
            destroySWFButton(button);
            fclose(inputFile);
            return 1;
        }
    }

    // Close the input file
    fclose(inputFile);

    // Call the destroySWFAction function for each action
    for (int i = 0; i < nActions; ++i) {
        destroySWFAction(actions[i]);
    }

    // Free the allocated memory
    free(actions);
    destroySWFButton(button);

    return 0;
}