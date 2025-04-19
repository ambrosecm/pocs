#include <stdio.h>
#include <stdlib.h>
#include "ming.h"
#include "button.h"
#include "position.h"

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

    // 读取文件中的角度值
    float deg;
    if (fscanf(inputFile, "%f", &deg) != 1) {
        fprintf(stderr, "Error reading angle from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 创建一个 SWFButtonRecord 对象
    SWFButtonRecord record = newSWFButtonSound(NULL); // Correctly create a SWFButtonRecord object

    // 调用 SWFButtonRecord_rotateTo 函数
    SWFButtonRecord_rotateTo(record, deg);

    // 清理资源
    free(record); // Use the correct function to destroy the record

    return 0;
}