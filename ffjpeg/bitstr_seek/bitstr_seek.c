#include "bitstr.h"
#include "stdefine.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

    // 读取文件中的参数
    void *stream;
    long offset;
    int origin;
    if (fscanf(inputFile, "%p %ld %d", &stream, &offset, &origin) != 3) {
        fprintf(stderr, "Error reading parameters from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 bitstr_seek 函数
    int result = bitstr_seek(stream, offset, origin);

    // 输出结果
    printf("bitstr_seek result: %d\n", result);

    return 0;
}