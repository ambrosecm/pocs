#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    // 读取文件中的输入数据
    int type;
    if (fscanf(inputFile, "%d", &type) != 1) {
        fprintf(stderr, "Error reading type from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 创建stream对象并设置type
    void *stream = malloc(sizeof(int));
    if (!stream) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    *(int*)stream = type;

    // 调用bitstr_close函数
    int result = bitstr_close(stream);

    // 释放stream对象
    free(stream);

    return result;
}