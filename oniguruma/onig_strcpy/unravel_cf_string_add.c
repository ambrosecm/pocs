#include <stdio.h>
#include <stdlib.h>
#include "regcomp.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    OnigUChar *start, *end;
    int flag;
    if (fscanf(inputFile, "%p %p %d", (void**)&start, (void**)&end, &flag) != 3) {
        fprintf(stderr, "Error reading input data from file.\n");
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);

    Node *list = NULL_NODE;
    Node *sn = NULL_NODE;

    int r = unravel_cf_string_add(&list, &sn, start, end, flag);

    if (r != 0) {
        fprintf(stderr, "Error in unravel_cf_string_add function.\n");
        return 1;
    }

    if (IS_NOT_NULL(list)) {
        onig_node_free(list);
    } else if (IS_NOT_NULL(sn)) {
        onig_node_free(sn);
    }

    return 0;
}