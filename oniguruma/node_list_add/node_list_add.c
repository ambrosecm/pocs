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

    // 读取文件中的输入数据
    Node *list = NULL;
    Node *add = NULL;
    Node **rlist = &list;  // Changed to pointer to pointer

    // 假设文件中有两个节点的数据，这里简化处理
    if (fscanf(inputFile, "%p %p", (void**)&list, (void**)&add) != 2) {
        fprintf(stderr, "Error reading node data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 node_list_add 函数
    if (IS_NULL(list)) {
        *rlist = add;  // Now this is correct as rlist is Node**
    } else {
        Node* r = node_list_add(list, add);
        if (IS_NULL(r)) {
            fprintf(stderr, "Failed to add node to list.\n");
            return 1;
        }
    }

    return 0;
}