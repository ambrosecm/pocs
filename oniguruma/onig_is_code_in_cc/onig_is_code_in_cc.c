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

    // 读取文件中的输入数据
    OnigEncoding enc;
    OnigCodePoint code;
    CClassNode cc;

    // 假设输入文件格式为：<encoding> <code> <cc>
    if (fscanf(inputFile, "%p %u %p", &enc, &code, &cc) != 3) {
        fprintf(stderr, "Error reading input data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 onig_is_code_in_cc 函数
    int result = onig_is_code_in_cc(enc, code, &cc);

    // 输出结果
    printf("Result: %d\n", result);

    return 0;
}