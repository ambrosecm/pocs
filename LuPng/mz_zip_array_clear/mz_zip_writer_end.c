#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "miniz.h"
#include <time.h>
#include <stdio.h>
#include <utime.h>

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

    // 读取文件中的 mz_zip_archive 结构体数据
    mz_zip_archive zip_archive;
    if (fread(&zip_archive, sizeof(mz_zip_archive), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading mz_zip_archive from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 mz_zip_writer_end 函数
    mz_bool result = mz_zip_writer_end(&zip_archive);

    // 输出结果
    printf("mz_zip_writer_end returned: %d\n", result);

    return 0;
}