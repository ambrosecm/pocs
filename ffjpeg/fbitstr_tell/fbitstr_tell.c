#include <stdio.h>
#include <stdlib.h>
#include "bitstr.h"

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

    // 读取文件中的流类型
    int type;
    if (fscanf(inputFile, "%d", &type) != 1) {
        fprintf(stderr, "Error reading type from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 创建流对象
    void *stream = malloc(sizeof(int));
    if (!stream) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }
    *(int*)stream = type;

    // 调用 fbitstr_tell 函数
    long result = bitstr_tell(stream);

    // 输出结果
    printf("Result: %ld\n", result);

    // 释放资源
    free(stream);
    fclose(inputFile);

    return 0;
}