#include <math.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include "SDLaffgif.c"
#include "ngiflibSDL.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // 调用 main_ 函数，传递输入文件路径
    char *args[] = {argv[0], argv[1]};
    return main_(2, args);
}