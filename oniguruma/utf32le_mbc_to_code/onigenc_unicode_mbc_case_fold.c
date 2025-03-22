#include <stdio.h>
#include <stdlib.h>
#include "utf32_le.c"
#include "regenc.h"
#include "oniguruma.h"  // Ensure this is the correct version of the header file

// Define ONIGENC_CASE_FOLD_MINIMAL if it is not defined in oniguruma.h
#ifndef ONIGENC_CASE_FOLD_MINIMAL
#define ONIGENC_CASE_FOLD_MINIMAL 0
#endif

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the file
    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read the file content
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    UChar *buffer = (UChar *)malloc(fileSize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    const UChar *p = buffer;
    const UChar *end = buffer + fileSize;
    OnigCaseFoldType flag = ONIGENC_CASE_FOLD_MINIMAL;
    UChar fold[ONIGENC_GET_CASE_FOLD_CODES_MAX_NUM];

    // Call onigenc_unicode_mbc_case_fold function
    int result = onigenc_unicode_mbc_case_fold(ONIG_ENCODING_UTF32_LE, flag, &p, end, fold);

    // Output the result
    if (result == 0) {
        printf("Case fold successful.\n");
    } else {
        printf("Case fold failed.\n");
    }

    free(buffer);
    return 0;
}