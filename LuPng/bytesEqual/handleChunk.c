#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "lupng.h"
#include "miniz.h"
#include "lupng.c"

// Function to read file into buffer
uint8_t* readFile(const char* filename, size_t* length) {
    FILE* file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t* buffer = (uint8_t*)malloc(*length);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, *length, file);
    fclose(file);
    return buffer;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    size_t length;
    uint8_t* buffer = readFile(argv[1], &length);
    if (!buffer) {
        fprintf(stderr, "Error reading file: %s\n", argv[1]);
        return 1;
    }

    // Initialize PngInfoStruct and LuUserContext
    PngInfoStruct info;
    memset(&info, 0, sizeof(PngInfoStruct));

    LuUserContext userCtx;
    luUserContextInitDefault(&userCtx);
    info.userCtx = &userCtx;

    // Initialize PngChunk
    PngChunk chunk;
    chunk.length = length;
    chunk.type = buffer;
    chunk.data = buffer + 4; // Assuming the first 4 bytes are the chunk type

    // Call handleChunk
    int result = handleChunk(&info, &chunk);

    // Clean up
    free(buffer);
    if (info.img) {
        luImageRelease(info.img, &userCtx);
    }

    return result == PNG_OK ? 0 : 1;
}