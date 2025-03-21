#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regcomp.c"
#include "regparse.h"

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

    char pattern[1024];
    if (fgets(pattern, sizeof(pattern), inputFile) == NULL) {
        fprintf(stderr, "Error reading pattern from file.\n");
        fclose(inputFile);
        return 1;
    }
    fclose(inputFile);

    OnigRegex reg;
    OnigErrorInfo einfo;
    ParseEnv scan_env = {0};
    UnsetAddrList uslist = {0};
    Node *root = NULL_NODE;
    UChar *pattern_end = (UChar *)pattern + strlen(pattern);

    int r = onig_new(&reg, (const UChar *)pattern, pattern_end, ONIG_OPTION_DEFAULT, ONIG_ENCODING_ASCII, ONIG_SYNTAX_DEFAULT, &einfo);
    if (r != ONIG_NORMAL) {
        fprintf(stderr, "Error initializing regex: %d\n", r);
        return 1;
    }

    r = parse_and_tune(reg, (const UChar *)pattern, pattern_end, &scan_env, &root, &einfo, &uslist);
    if (r != 0) {
        fprintf(stderr, "Error in parse_and_tune: %d\n", r);
        onig_free(reg);
        return 1;
    }

    onig_free(reg);
    onig_node_free(root);

    return 0;
}