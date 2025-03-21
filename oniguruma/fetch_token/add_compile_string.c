#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"
#include "regparse.h"

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

    // 读取文件内容
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *fileContent = (char *)malloc(fileSize + 1);
    if (!fileContent) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    fread(fileContent, 1, fileSize, inputFile);
    fileContent[fileSize] = '\0';
    fclose(inputFile);

    // 初始化正则表达式结构
    OnigRegex reg;
    OnigEncoding enc = ONIG_ENCODING_UTF8;
    OnigErrorInfo einfo;
    int r = onig_new(&reg, (UChar *)fileContent, (UChar *)(fileContent + fileSize),
                     ONIG_OPTION_DEFAULT, enc, ONIG_SYNTAX_DEFAULT, &einfo);
    if (r != ONIG_NORMAL) {
        char s[ONIG_MAX_ERROR_MESSAGE_LEN];
        onig_error_code_to_str((UChar *)s, r, &einfo);
        fprintf(stderr, "ERROR: %s\n", s);
        free(fileContent);
        return 1;
    }

    // 调用 add_compile_string 函数
    // 这里假设 fileContent 是我们要传递的字符串
    // 由于 add_compile_string 需要更多上下文，这里仅作为示例
    int slen = 1; // 假设字符串长度为1
    r = add_compile_string((UChar *)fileContent, 1, slen, reg);
    if (r != 0) {
        fprintf(stderr, "Error in add_compile_string\n");
        free(fileContent);
        onig_free(reg);
        return 1;
    }

    // 释放资源
    free(fileContent);
    onig_free(reg);

    return 0;
}