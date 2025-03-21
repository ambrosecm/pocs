#include <stdio.h>
#include <stdlib.h>
#include "regint.h"
#include "st.h"
#include "regparse.c"
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

    // 读取文件中的数据
    OnigCodePoint start1, end1, start2, end2;
    if (fscanf(inputFile, "%x %x %x %x", &start1, &end1, &start2, &end2) != 4) {
        fprintf(stderr, "Error reading code points from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 初始化 BBuf
    BBuf *pbuf = NULL;
    OnigCodePoint data[2];
    int n = 2;

    // 调用 and_code_range1 函数
    int result = and_code_range1(&pbuf, start1, end1, data, n);

    // 输出结果
    if (result == 0) {
        printf("Intersection: [%x, %x]\n", data[0], data[1]);
    } else {
        printf("No intersection found.\n");
    }

    return 0;
}