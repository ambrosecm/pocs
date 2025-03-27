#include <config.h>  // 添加 config.h 头文件
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "internal.h"
#include "lou_backTranslateString.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read the input data from the file
    char inputBuffer[1024];
    size_t inputLength = fread(inputBuffer, 1, sizeof(inputBuffer), inputFile);
    fclose(inputFile);

    // Initialize the necessary structures
    OutString output;
    output.chars = (widechar *)malloc(inputLength * sizeof(widechar));  // 修复指针类型
    output.length = 0;
    output.maxlength = inputLength;

    TranslationContext ctx;
    ctx.nextUpper = 0;
    ctx.allUpper = 0;
    ctx.allUpperPhrase = 0;

    // Call the putchars function
    int result = putchars((const widechar *)inputBuffer, inputLength, NULL, &output, &ctx);

    // Output the result
    if (result) {
        printf("Output: %.*s\n", (int)output.length, (char *)output.chars);  // 修复指针类型
    } else {
        printf("Error in putchars function\n");
    }

    // Free allocated memory
    free(output.chars);

    return 0;
}