#include "tiffio.h"
#include "tiffiop.h"
#include <limits.h>
#include <float.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    TIFF *tif = TIFFOpen(argv[1], "r");
    if (!tif) {
        fprintf(stderr, "Could not open TIFF file\n");
        return 1;
    }

    const TIFFFieldArray *tiffFieldArray = _TIFFGetFields();
    _TIFFSetupFields(tif, tiffFieldArray);

    TIFFClose(tif);
    return 0;
}