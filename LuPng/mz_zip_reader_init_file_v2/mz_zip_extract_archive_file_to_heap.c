#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/stat.h>
#include <time.h>
#include "miniz.h"

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

    // 获取文件大小
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    // 读取文件内容
    void *fileData = malloc(fileSize);
    if (!fileData) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }
    fread(fileData, 1, fileSize, inputFile);
    fclose(inputFile);

    // 调用 mz_zip_extract_archive_file_to_heap 函数
    size_t out_len;
    void *extractedData = mz_zip_extract_archive_file_to_heap(fileData, argv[1], &out_len, 0);

    if (extractedData) {
        // 处理提取的数据
        printf("Extracted data size: %zu\n", out_len);
        free(extractedData);
    } else {
        fprintf(stderr, "Failed to extract data from archive\n");
    }

    free(fileData);
    return 0;
}