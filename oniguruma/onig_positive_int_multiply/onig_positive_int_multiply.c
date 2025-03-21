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

    int x, y;
    // 读取文件中的两个整数
    if (fscanf(inputFile, "%d %d", &x, &y) != 2) {
        fprintf(stderr, "Error reading integers from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 onig_positive_int_multiply 函数
    int result = onig_positive_int_multiply(x, y);
    printf("Result: %d\n", result);

    return 0;
}