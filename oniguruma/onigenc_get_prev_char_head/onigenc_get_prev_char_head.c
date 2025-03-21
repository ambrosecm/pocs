#include <stdio.h>
#include <stdlib.h>
#include "regint.h"
#include "regexec.c"

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
    UChar *s, *start, *adjust_text;
    OnigEncoding enc = ONIG_ENCODING_UTF8; // 假设使用UTF-8编码

    // 这里假设输入文件包含三个指针地址，分别对应 s, start, adjust_text
    if (fscanf(inputFile, "%p %p %p", &s, &start, &adjust_text) != 3) {
        fprintf(stderr, "Error reading input data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 onigenc_get_prev_char_head 函数
    UChar *result = onigenc_get_prev_char_head(enc, start, s);

    // 输出结果
    printf("Result: %p\n", result);

    return 0;
}