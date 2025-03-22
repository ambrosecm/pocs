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

    UChar *buffer = (UChar *)malloc(fileSize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    // 设置函数调用所需的变量
    const UChar *pp = buffer;
    const UChar *end = buffer + fileSize;
    int flag = 0; // 假设 flag 为 0，具体值根据实际需求设置
    UChar fold[ONIGENC_CODE_TO_MBC_MAXLEN]; // 用于存储折叠后的字符

    // 调用 onigenc_unicode_mbc_case_fold 函数
    onigenc_unicode_mbc_case_fold(ONIG_ENCODING_UTF32_BE, flag, &pp, end, fold);

    // 释放内存
    free(buffer);

    return 0;
}