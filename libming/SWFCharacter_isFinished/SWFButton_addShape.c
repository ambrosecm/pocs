#include <stdio.h>
#include <stdlib.h>
#include "ming.h"
#include "button.h"
#include "character.h"
#include "matrix.h"
#include "outputblock.h"
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

    // 读取文件中的输入数据
    int flags;
    SWFButton button;
    SWFCharacter character;
    if (fscanf(inputFile, "%d %p %p", &flags, (void**)&button, (void**)&character) != 3) {
        fprintf(stderr, "Error reading input data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 SWFButton_addShape 函数
    SWFButton_addShape(button, character, flags);

    return 0;
}