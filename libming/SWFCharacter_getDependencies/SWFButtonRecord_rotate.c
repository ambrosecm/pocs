#include <stdio.h>
#include <stdlib.h>
#include "ming.h"
#include "button.h"
#include "position.h"

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

    // Read the input values from the file
    float deg;
    if (fscanf(inputFile, "%f", &deg) != 1) {
        fprintf(stderr, "Error reading degree value from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Create a SWFButton object
    SWFButton button = newSWFButton();

    // Add a record to the button (assuming this is how SWFButtonRecord is created)
    SWFButtonRecord record = SWFButton_addCharacter(button, NULL, SWFBUTTON_HIT);

    // Call the SWFButtonRecord_rotate function
    SWFButtonRecord_rotate(record, deg);

    // Clean up (assuming the button destruction also destroys the record)
    destroySWFButton(button);

    return 0;
}