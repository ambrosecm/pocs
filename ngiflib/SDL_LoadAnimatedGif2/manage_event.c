#include "SDLaffgif.c"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "ngiflibSDL.h"
#include <stdlib.h>

int main(int argc, char** argv) {
    char windows_caption[256];
    char icon_caption[256];
    char* gifname = NULL;

    if (argc > 1) {
        gifname = argv[1];
    } else {
        fprintf(stderr, "Usage: %s <gif_file>\n", argv[0]);
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "Erreur d'init de la SDL !\n");
        return 1;
    }
    atexit(SDL_Quit);

    struct ngiflibSDL_animation* animation = SDL_LoadAnimatedGif(gifname);
    if (animation == NULL) {
        fprintf(stderr, "Failed to read %s\n", gifname);
        return 1;
    }

    if (animation->image_count == 0) {
        fprintf(stderr, "%s contains 0 images !\n", gifname);
        return 1;
    }

    int width = animation->images[0].surface->w;
    int height = animation->images[0].surface->h;

    snprintf(windows_caption, sizeof(windows_caption), "SDL gif viewer : %s", gifname);
    snprintf(icon_caption, sizeof(icon_caption), "gif viewer : %s", gifname);
    SDL_WM_SetCaption(windows_caption, icon_caption);

    const SDL_VideoInfo* vidinf = SDL_GetVideoInfo();
    printf("bpp of the \"best\" video mode = %d \n", vidinf->vfmt->BitsPerPixel);

    SDL_Rect** modes = SDL_ListModes(NULL, SDL_HWSURFACE);
    if (modes == (SDL_Rect**)-1) {
        printf("All resolutions available.\n");
    } else {
        printf("Available Modes\n");
        for (int i = 0; modes[i]; ++i) {
            printf("  %d x %d\n", modes[i]->w, modes[i]->h);
        }
    }

    int bpp = SDL_VideoModeOK(width, height, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!bpp) {
        printf("Mode not available.\n");
        exit(-1);
    }
    printf("SDL Recommends %dx%d@%dbpp.\n", width, height, bpp);

    SDL_Surface* screen = SDL_SetVideoMode(width, height, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL) {
        fprintf(stderr, "Failed to set video mode\n");
        return 1;
    }

    printf("%d images\n", animation->image_count);
    for (;;) {
        for (int i = 0; i < animation->image_count; i++) {
            SDL_Event event;
            SDL_Rect dest;
            dest.x = 0;
            dest.y = 0;
            dest.w = animation->images[i].surface->w;
            dest.h = animation->images[i].surface->h;
            SDL_BlitSurface(animation->images[i].surface, NULL, screen, &dest);
            SDL_UpdateRects(screen, 1, &dest);
            SDL_Flip(screen);

            if (animation->image_count > 1) {
                if (animation->images[i].delay_time > 0) {
                    SDL_Delay(10 * animation->images[i].delay_time);
                }
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        printf("SDL_QUIT\n");
                        exit(0);
                    } else if (event.type == SDL_KEYDOWN) {
                        printf("Touche %s _\n", SDL_GetKeyName(event.key.keysym.sym));
                        if (event.key.keysym.sym == SDLK_ESCAPE) exit(0);
                    }
                }
            } else {
                for (;;) {
                    manage_event();
                }
            }
        }
    }

    return 0;
}