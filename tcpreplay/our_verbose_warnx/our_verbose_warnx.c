#include "config.h"
#include <stdio.h>
#include "common.h"
#include "err.c"
#include "defines.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

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

    char fmt[256];
    // 读取文件中的格式化字符串
    if (fgets(fmt, sizeof(fmt), inputFile) == NULL) {
        fprintf(stderr, "Error reading format string from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 our_verbose_warnx 函数
    our_verbose_warnx(fmt);

    return 0;
}