#include <stdio.h>
#include <stdlib.h>
#include "dct.c"
#include "stdefine.h"
#include "dct.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // 打开文件
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    int ftab[64], qtab[64];

    // 读取文件中的64个整数到ftab和qtab
    for (int i = 0; i < 64; i++) {
        if (fscanf(inputFile, "%d", &ftab[i]) != 1) {
            fprintf(stderr, "Error reading ftab from file.\n");
            fclose(inputFile);
            return 1;
        }
    }
    for (int i = 0; i < 64; i++) {
        if (fscanf(inputFile, "%d", &qtab[i]) != 1) {
            fprintf(stderr, "Error reading qtab from file.\n");
            fclose(inputFile);
            return 1;
        }
    }

    // 关闭文件
    fclose(inputFile);

    // 调用init_fdct_ftab函数
    init_fdct_ftab(ftab, qtab);

    return 0;
}