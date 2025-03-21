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

    int from, to, not;
    OnigCtype ctype;
    OnigEncoding enc;
    OnigCodePoint sb_out;
    OnigCodePoint mbr[2]; // Assuming mbr is an array of 2 elements
    CClassNode cc;

    // 读取文件中的输入数据
    if (fscanf(inputFile, "%d %d %d %d %d %d", &from, &to, &ctype, &not, &sb_out, &mbr[0]) != 6) {
        fprintf(stderr, "Error reading input data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // 关闭文件
    fclose(inputFile);

    // 调用 add_ctype_to_cc_by_range 函数
    add_ctype_to_cc_by_range(&cc, ctype, not, enc, sb_out, mbr);

    return 0;
}