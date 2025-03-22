#include <stdio.h>
#include <stdlib.h>
#include "utf32_be.c"
#include "regenc.h"

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

    UChar *inputData = (UChar *)malloc(fileSize);
    if (!inputData) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    fread(inputData, 1, fileSize, inputFile);
    fclose(inputFile);

    // 准备调用 utf32be_mbc_case_fold 函数的参数
    const UChar *pp = inputData;
    const UChar *end = inputData + fileSize;
    UChar fold[4];
    OnigCaseFoldType flag = ONIGENC_CASE_FOLD_MIN;

    // 调用 utf32be_mbc_case_fold 函数
    int result = utf32be_mbc_case_fold(flag, &pp, end, fold);

    // 输出结果
    printf("Case fold result: %d\n", result);

    // 释放内存
    free(inputData);

    return 0;
}