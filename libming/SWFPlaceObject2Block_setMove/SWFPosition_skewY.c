#include <stdio.h>
#include <stdlib.h>
#include "blocks/blocktypes.h"
#include "position.h"
#include "blocks/filter.h"
#include "blocks/scalinggrid.h"
#include "displaylist.c"
#include "blocks/outputblock.h"
#include "displaylist.h"
#include "blocks/soundstream.h"
#include "blocklist.h"
#include "blocks/sprite.h"
#include "blocks/videostream.h"
#include "blocks/button.h"
#include <math.h>
#include "ming.h"
#include "blocks/character.h"
#include "libming.h"
#include "blocks/matrix.h"
#include "blocks/placeobject.h"

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
    double y;
    if (fscanf(inputFile, "%lf", &y) != 1) {
        fprintf(stderr, "Error reading input from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 创建必要的对象
    SWFDisplayItem item = newSWFDisplayList();
    if (item->block == NULL) {
        item->block = newSWFPlaceObject2Block(item->depth);
    }

    // 调用 SWFPosition_skewY 函数
    checkBlock(item);
    SWFPosition_skewY(item->position, y);

    // 清理资源
    destroySWFDisplayItem(item);

    return 0;
}