#include <stdio.h>
#include <stdlib.h>
#include "exif.c"

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

    // 读取文件中的数据
    int value;
    if (fread(&value, sizeof(int), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 Get32s 函数
    int result = Get32s(&value);

    // 输出结果
    printf("Result: %d\n", result);

    return 0;
}