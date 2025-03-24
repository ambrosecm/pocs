#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "miniz.h"

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

    // Read the time values from the file
    struct tm tm_time;
    if (fscanf(inputFile, "%d %d %d %d %d %d", 
               &tm_time.tm_year, &tm_time.tm_mon, &tm_time.tm_mday, 
               &tm_time.tm_hour, &tm_time.tm_min, &tm_time.tm_sec) != 6) {
        fprintf(stderr, "Error reading time values from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Convert the time to DOS format
    time_t time = mktime(&tm_time);
    mz_uint16 dos_time, dos_date;
    mz_zip_time_t_to_dos_time(time, &dos_time, &dos_date);

    // Print the result
    printf("DOS Time: %04x\n", dos_time);
    printf("DOS Date: %04x\n", dos_date);

    return 0;
}