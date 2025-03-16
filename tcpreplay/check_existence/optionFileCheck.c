#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // For strrchr
#include <sys/stat.h>  // For stat
#include <errno.h>  // For errno, ENOENT, EINVAL
#include <fcntl.h>  // For open

// Assuming optionFileCheck is declared or defined elsewhere in the codebase
extern void optionFileCheck(int inputData);

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
    // Assuming the input data is a single integer for simplicity
    int inputData;
    if (fscanf(inputFile, "%d", &inputData) != 1) {
        fprintf(stderr, "Error reading integer from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Call the optionFileCheck function with the input data
    optionFileCheck(inputData);

    return 0;
}