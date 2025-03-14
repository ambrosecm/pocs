#include <SDL/SDL.h>
#include "ngiflibSDL.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "SDLaffgif.c"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *file = argv[1];
    SDL_Surface *image = SDL_LoadGIF(file);

    if (image == NULL) {
        fprintf(stderr, "Failed to load GIF: %s\n", SDL_GetError());
        return 1;
    }

    // Optionally, you can add code here to display or process the loaded image.

    SDL_FreeSurface(image);
    return 0;
}