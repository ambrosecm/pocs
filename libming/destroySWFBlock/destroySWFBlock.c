#include <stdio.h>
#include <stdlib.h>
#include "blocklist.h"
#include "ming.h"
#include "blocks/character.h"
#include "blocks/block.h"
#include "libming.h"

// Define the structures if they are not already defined in the included headers
struct blocklist_entry {
    int isCharacter;
    struct SWFBlock *block;
};

struct blocklist {
    int nBlocks;
    struct blocklist_entry *blocks;
};

struct SWFBlock {
    void (*dtor)(struct SWFBlock *);
    // Add other necessary fields here
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

    // Read the number of blocks from the file
    int nBlocks;
    if (fscanf(inputFile, "%d", &nBlocks) != 1) {
        fprintf(stderr, "Error reading number of blocks from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Allocate memory for the blocklist
    struct blocklist *list = (struct blocklist *)malloc(sizeof(struct blocklist));
    if (!list) {
        fprintf(stderr, "Memory allocation failed for blocklist.\n");
        fclose(inputFile);
        return 1;
    }

    list->nBlocks = nBlocks;
    list->blocks = (struct blocklist_entry *)malloc(nBlocks * sizeof(struct blocklist_entry));
    if (!list->blocks) {
        fprintf(stderr, "Memory allocation failed for blocklist entries.\n");
        free(list);
        fclose(inputFile);
        return 1;
    }

    // Read each block entry from the file
    for (int i = 0; i < nBlocks; ++i) {
        int isCharacter;
        if (fscanf(inputFile, "%d", &isCharacter) != 1) {
            fprintf(stderr, "Error reading isCharacter flag for block %d.\n", i);
            free(list->blocks);
            free(list);
            fclose(inputFile);
            return 1;
        }
        list->blocks[i].isCharacter = isCharacter;

        // Allocate memory for the block (assuming it's a simple structure)
        list->blocks[i].block = (struct SWFBlock *)malloc(sizeof(struct SWFBlock));
        if (!list->blocks[i].block) {
            fprintf(stderr, "Memory allocation failed for block %d.\n", i);
            free(list->blocks);
            free(list);
            fclose(inputFile);
            return 1;
        }
    }

    // Close the input file
    fclose(inputFile);

    // Call the destroySWFBlock function for non-character blocks
    for (int i = 0; i < list->nBlocks; ++i) {
        if (!list->blocks[i].isCharacter) {
            destroySWFBlock(list->blocks[i].block);
        }
    }

    // Free the blocklist and its entries
    free(list->blocks);
    free(list);

    return 0;
}