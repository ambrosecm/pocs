#include <stdio.h>
#include <stdlib.h>
#include "blocktypes.h"
#include "output.h"
#include "character.h"
#include "ming.h"
#include "rect.h"
#include "gradient.h"
#include "matrix.h"
#include "error.h"
#include "fillstyle.h"
#include "libming.h"

// Define the SWFOutput_s structure
struct SWFOutput_s {
    unsigned char *pos;
    int free;
};

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

    // 读取文件中的数据
    unsigned char data;
    if (fscanf(inputFile, "%hhu", &data) != 1) {
        fprintf(stderr, "Error reading data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 创建 SWFOutput 对象
    SWFOutput out = (SWFOutput)malloc(sizeof(struct SWFOutput_s));
    out->pos = (unsigned char *)malloc(1);
    out->free = 1;

    // 调用 SWFOutput_writeUInt8 函数
    SWFOutput_writeUInt8(out, data);

    // 释放资源
    free(out->pos);
    free(out);

    return 0;
}