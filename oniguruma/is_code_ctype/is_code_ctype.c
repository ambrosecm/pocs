#include <stdio.h>
#include <stdlib.h>
#include "iso8859_1.c"
#include "regenc.h"

// Correct the function declaration to match the definition in iso8859_1.c
int is_code_ctype(OnigCodePoint code, unsigned int ctype);

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

    OnigCodePoint code;
    unsigned int ctype;
    // 读取文件中的两个整数
    if (fscanf(inputFile, "%u %u", &code, &ctype) != 2) {
        fprintf(stderr, "Error reading integers from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 is_code_ctype 函数
    int result = is_code_ctype(code, ctype);
    printf("Result: %d\n", result);

    return 0;
}