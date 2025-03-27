#include "config.h"  // Include config.h first
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lou_translateString.c"
#include "internal.h"

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

    int pos, len;
    EmphasisInfo *emphasisBuffer = NULL;

    // Read pos and len from the file
    if (fscanf(inputFile, "%d %d", &pos, &len) != 2) {
        fprintf(stderr, "Error reading pos and len from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Allocate memory for emphasisBuffer
    emphasisBuffer = (EmphasisInfo *)malloc(len * sizeof(EmphasisInfo));
    if (!emphasisBuffer) {
        fprintf(stderr, "Memory allocation failed for emphasisBuffer.\n");
        fclose(inputFile);
        return 1;
    }

    // Read emphasisBuffer data from the file
    for (int i = 0; i < len; i++) {
        int begin, end, word;
        if (fscanf(inputFile, "%d %d %d", &begin, &end, &word) != 3) {
            fprintf(stderr, "Error reading emphasisBuffer data from file.\n");
            free(emphasisBuffer);
            fclose(inputFile);
            return 1;
        }
        emphasisBuffer[i].begin = begin;
        emphasisBuffer[i].end = end;
        emphasisBuffer[i].word = word;
    }

    // Close the input file
    fclose(inputFile);

    // Call the checkEmphasisChange function
    int result = checkEmphasisChange(pos, len, emphasisBuffer);

    // Free allocated memory
    free(emphasisBuffer);

    // Output the result (optional)
    printf("checkEmphasisChange returned: %d\n", result);

    return 0;
}