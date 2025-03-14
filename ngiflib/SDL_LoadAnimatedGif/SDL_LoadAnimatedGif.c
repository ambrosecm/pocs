#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <string.h>
#include "ngiflibSDL.h"
#include "SDLaffgif.c"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <gif_file>\n", argv[0]);
        return 1;
    }

    const char *gifname = argv[1];

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    struct ngiflibSDL_animation *animation = SDL_LoadAnimatedGif(gifname);
    if (!animation) {
        fprintf(stderr, "Failed to load animated GIF: %s\n", gifname);
        SDL_Quit();
        return 1;
    }

    // Clean up
    if (animation) {
        for (int i = 0; i < animation->image_count; i++) {
            SDL_FreeSurface(animation->images[i].surface);
        }
        free(animation);
    }

    SDL_Quit();
    return 0;
}