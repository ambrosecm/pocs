#include <stdio.h>
#include <stdlib.h>
#include "blocks/character.h"
#include "ming.h"
#include "libming.h"
#include "blocks/block.h"
#include "blocklist.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "rb");
    if (!input)
    {
        fprintf(stderr, "Error opening input file\n");
        return 1;
    }

    // Create sprite
    SWFSprite sprite = newSWFSprite();
    
    // Create block using proper initialization
    SWFBlock block = (SWFBlock)malloc(sizeof(struct SWFBlock_s));
    if (!block)
    {
        fprintf(stderr, "Error allocating block\n");
        fclose(input);
        return 1;
    }

    // Read block type from input file
    if (fread(&block->type, sizeof(block->type), 1, input) != 1)
    {
        fprintf(stderr, "Error reading block type\n");
        fclose(input);
        free(block);
        return 1;
    }

    // Call the target function
    SWFSprite_addBlock(sprite, block);

    // Cleanup
    destroySWFSprite(sprite);
    free(block);
    fclose(input);

    return 0;
}