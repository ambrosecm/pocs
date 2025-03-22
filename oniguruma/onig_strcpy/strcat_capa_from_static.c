#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regint.h"
#include "st.h"
#include "regparse.c"  // Include the .c file instead of .h

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

    // Variables to hold the input data
    char static_str[256];
    char dynamic_str[256];
    size_t capacity;

    // Read the input data from the file
    if (fscanf(inputFile, "%255s %255s %zu", static_str, dynamic_str, &capacity) != 3) {
        fprintf(stderr, "Error reading input data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Define the end pointers for the strings
    UChar *static_str_end = (UChar *)static_str + strlen(static_str);
    UChar *dynamic_str_end = (UChar *)dynamic_str + strlen(dynamic_str);

    // Call the strcat_capa_from_static function with all required parameters
    strcat_capa_from_static((UChar *)static_str, static_str_end, (UChar *)dynamic_str, dynamic_str_end, (int)capacity);

    return 0;
}