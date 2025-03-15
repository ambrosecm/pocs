#include <stdio.h>
#include <stdlib.h>
#include "stdefine.h"
#include "bitstr.h"
#include "bitstr.c"

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

    // 读取文件中的字符
    int c;
    if (fscanf(inputFile, "%d", &c) != 1) {
        fprintf(stderr, "Error reading character from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 设置stream为BITSTR_FILE类型
    int stream_type = BITSTR_FILE;
    void *stream = &stream_type;

    // 调用bitstr_putc函数
    bitstr_putc(c, stream);

    return 0;
}