#include <stdio.h>
#include <stdlib.h>
#include "ming.h"
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

    float degrees;
    // Read the degrees from the file
    if (fscanf(inputFile, "%f", &degrees) != 1) {
        fprintf(stderr, "Error reading degrees from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Create a SWFFillStyle object using the correct function
    SWFFillStyle fillstyle = newSWFLineStyle(1, 255, 255, 255, 255); // Example values for width and color

    // Create a SWFFill object with the fillstyle
    SWFFill fill = newSWFFill(fillstyle);

    // Call the SWFFill_rotateTo function
    SWFFill_rotateTo(fill, degrees);

    // Clean up
    destroySWFFill(fill);

    return 0;
}