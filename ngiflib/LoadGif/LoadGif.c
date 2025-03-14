#include <SDL/SDL.h>
#include "ngiflibSDL.h"
#include <stdio.h>
#include "ngiflibSDL.c"
#include "ngiflib.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fgif = fopen(argv[1], "rb");
    if (fgif == NULL) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    struct ngiflib_gif *gif = (struct ngiflib_gif *)ngiflib_malloc(sizeof(struct ngiflib_gif));
    if (gif == NULL) {
        fclose(fgif);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    ngiflib_memset(gif, 0, sizeof(struct ngiflib_gif));
    gif->input.file = fgif;
    gif->mode = NGIFLIB_MODE_FROM_FILE | NGIFLIB_MODE_INDEXED;
    gif->log = stdout;

    int err = LoadGif(gif);
    fclose(fgif);

    if (err != 1) {
        GifDestroy(gif);
        return 1;
    }

    SDL_Surface *surface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCCOLORKEY,
                                                gif->width, gif->height, 8,
                                                0, 0, 0, 0);
    if (surface == NULL) {
        fprintf(stderr, "SDL_CreateRGBSurface(..., %d, %d, 8, ...) failed : %s\n", gif->width, gif->height, SDL_GetError());
        GifDestroy(gif);
        return 1;
    }

    SDL_LockSurface(surface);
    if (gif->cur_img->gce.transparent_flag) {
        SDL_SetColorKey(surface, SDL_SRCCOLORKEY, gif->cur_img->gce.transparent_color);
    }

    for (int i = 0; i < gif->ncolors; i++) {
        surface->format->palette->colors[i].r = gif->palette[i].r;
        surface->format->palette->colors[i].g = gif->palette[i].g;
        surface->format->palette->colors[i].b = gif->palette[i].b;
    }

    unsigned char *psrc = gif->frbuff.p8;
    unsigned char *pdst = surface->pixels;
    for (int i = 0; i < gif->height; i++) {
        ngiflib_memcpy(pdst, psrc, gif->width);
        pdst += surface->pitch;
        psrc += gif->width;
    }

    SDL_UnlockSurface(surface);
    GifDestroy(gif);

    // You can add code here to display or save the surface if needed

    return 0;
}