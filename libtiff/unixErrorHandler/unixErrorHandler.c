#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tiffiop.h"

void callTIFFErrorExt(const char* module, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    TIFFErrorExt(NULL, module, fmt, ap);
    va_end(ap);
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) 
    {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read module name (first line)
    char module[256] = {0};
    if (!fgets(module, sizeof(module), inputFile))
    {
        module[0] = '\0';  // Empty module if not provided
    }
    else 
    {
        // Remove newline if present
        module[strcspn(module, "\n")] = '\0';
    }

    // Read format string (second line)
    char fmt[1024] = {0};
    if (!fgets(fmt, sizeof(fmt), inputFile)) 
    {
        strcpy(fmt, "default error message");
    }
    else 
    {
        // Remove newline if present
        fmt[strcspn(fmt, "\n")] = '\0';
    }

    fclose(inputFile);

    // Call the target function through our variadic wrapper
    callTIFFErrorExt(strlen(module) > 0 ? module : NULL, fmt);

    return 0;
}