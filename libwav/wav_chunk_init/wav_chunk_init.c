#include <stdio.h>
#include <stdlib.h>
#include "libwav.h"
#include "libwav.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read the file content into a buffer
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    void *fileContent = malloc(fileSize);
    if (!fileContent) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }
    fread(fileContent, 1, fileSize, inputFile);
    fclose(inputFile);

    // Initialize the wav_chunk structure
    wav_chunk chunk;
    wav_chunk_init(&chunk, WAV_CHUNKID_RIFF, fileSize, fileContent);

    // Free the allocated memory
    free(fileContent);

    return 0;
}