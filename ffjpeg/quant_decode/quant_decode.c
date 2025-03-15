#include <stdio.h>
#include <stdlib.h>
#include "quant.c"
#include "quant.h"

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

    int du[64];
    int qtab[64];

    // 读取文件中的数据
    for (int i = 0; i < 64; i++) {
        if (fscanf(inputFile, "%d", &du[i]) != 1) {
            fprintf(stderr, "Error reading data from file.\n");
            fclose(inputFile);
            return 1;
        }
    }

    for (int i = 0; i < 64; i++) {
        if (fscanf(inputFile, "%d", &qtab[i]) != 1) {
            fprintf(stderr, "Error reading data from file.\n");
            fclose(inputFile);
            return 1;
        }
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 quant_decode 函数
    quant_decode(du, qtab);

    return 0;
}