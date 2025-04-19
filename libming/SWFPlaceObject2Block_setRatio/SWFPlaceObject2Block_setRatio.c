#include <stdio.h>
#include <stdlib.h>
#include "blocks/videostream.h"
#include "blocks/outputblock.h"
#include "blocks/character.h"
#include "blocks/scalinggrid.h"
#include "libming.h"
#include "blocklist.h"
#include "blocks/sprite.h"
#include "blocks/button.h"
#include "displaylist.h"
#include "blocks/matrix.h"
#include "blocks/blocktypes.h"
#include "ming.h"
#include "blocks/placeobject.h"
#include "blocks/soundstream.h"
#include <math.h>
#include "blocks/filter.h"
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

    // Read the ratio value from the file
    float ratio;
    if (fscanf(inputFile, "%f", &ratio) != 1) {
        fprintf(stderr, "Error reading ratio from file.\n");
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);

    // Create a new SWFDisplayList
    SWFDisplayList displayList = newSWFDisplayList();
    if (displayList == NULL) {
        fprintf(stderr, "Failed to create SWFDisplayList.\n");
        return 1;
    }

    // Create a new SWFDisplayItem
    SWFDisplayItem item = (SWFDisplayItem)displayList; // Corrected to use displayList
    if (item == NULL) {
        fprintf(stderr, "Failed to create SWFDisplayItem.\n");
        destroySWFDisplayList(displayList);
        return 1;
    }

    // Check if the block is NULL and create a new SWFPlaceObject2Block if necessary
    if (item->block == NULL) {
        item->block = newSWFPlaceObject2Block(item->depth);
    }

    // Call SWFPlaceObject2Block_setRatio with the parsed ratio
    int res = (int)floor(ratio * 65535);
    SWFPlaceObject2Block_setRatio(item->block, res);

    // Clean up
    destroySWFDisplayList(displayList); // Corrected to use destroySWFDisplayList

    return 0;
}