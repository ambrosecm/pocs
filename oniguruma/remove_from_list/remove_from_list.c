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

    // 读取文件中的数据并解析为 remove_from_list 函数所需的格式
    // 这里假设输入文件包含两个节点的指针，分别代表 prev_node 和 node
    Node *prev_node = NULL;
    Node *node = NULL;
    if (fscanf(inputFile, "%p %p", &prev_node, &node) != 2) {
        fprintf(stderr, "Error reading node pointers from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 remove_from_list 函数
    remove_from_list(prev_node, node);

    return 0;
}