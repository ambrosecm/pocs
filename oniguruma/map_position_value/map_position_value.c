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

    // 读取文件中的编码类型和字符位置
    int i;
    if (fscanf(inputFile, "%d", &i) != 1) {
        fprintf(stderr, "Error reading position from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 使用默认的编码类型 (例如 UTF-8)
    OnigEncoding enc = ONIG_ENCODING_UTF8;

    // 调用 map_position_value 函数
    int val = map_position_value(enc, i);

    // 输出结果
    printf("Value: %d\n", val);

    return 0;
}