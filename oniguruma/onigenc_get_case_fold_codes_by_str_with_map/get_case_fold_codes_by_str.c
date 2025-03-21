#include <stdio.h>
#include <stdlib.h>
#include "regenc.h"  // Ensure this header file exists and is correct

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
    OnigUChar *str;
    OnigUChar *end;
    OnigCaseFoldCodeItem items[ONIGENC_GET_CASE_FOLD_CODES_MAX_NUM];
    int num_items;

    // 假设输入文件包含一个字符串和其长度
    size_t len;
    if (fscanf(inputFile, "%zu", &len) != 1) {
        fprintf(stderr, "Error reading string length from file.\n");
        fclose(inputFile);
        return 1;
    }

    str = (OnigUChar *)malloc(len + 1);
    if (!str) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }

    if (fread(str, 1, len, inputFile) != len) {
        fprintf(stderr, "Error reading string from file.\n");
        free(str);
        fclose(inputFile);
        return 1;
    }
    str[len] = '\0'; // Null-terminate the string
    end = str + len;

    // 调用 get_case_fold_codes_by_str 函数
    num_items = onigenc_get_case_fold_codes_by_str_with_map(
        256, // map_size
        NULL, // map (assuming no custom map is provided)
        0, // ess_tsett_flag
        ONIGENC_CASE_FOLD_MIN, // flag
        str, // p
        end, // end
        items // items
    );

    // 输出结果
    printf("Number of case fold codes: %d\n", num_items);
    for (int i = 0; i < num_items; i++) {
        printf("Code: %x, Length: %d\n", items[i].code, items[i].byte_len);
    }

    // 释放内存并关闭文件
    free(str);
    fclose(inputFile);

    return 0;
}