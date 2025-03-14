#include <inttypes.h>
#include "ngiflib.h"
#include "ngiflib.c"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // 打开文件
    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // 读取文件内容
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    u8 *buffer = (u8 *)malloc(fileSize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    // 调用 CheckGif 函数
    int result = CheckGif(buffer);

    // 输出结果
    printf("CheckGif result: %d\n", result);

    // 释放内存
    free(buffer);

    return 0;
}