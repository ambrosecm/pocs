#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "tiffio.h"
#include "tiffiop.h"  // This contains the full definition of struct tiff

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file.tiff>\n", argv[0]);
        return 1;
    }

    TIFF *tif = TIFFOpen(argv[1], "r");
    if (!tif) {
        fprintf(stderr, "Could not open TIFF file\n");
        return 1;
    }

    // Initialize necessary directory fields
    tif->tif_dir.td_nstrips = 1;  // Start with single strip
    tif->tif_dir.td_stripoffset_p = (uint64_t *)malloc(sizeof(uint64_t));
    tif->tif_dir.td_stripbytecount_p = (uint64_t *)malloc(sizeof(uint64_t));
    
    if (!tif->tif_dir.td_stripoffset_p || !tif->tif_dir.td_stripbytecount_p) {
        fprintf(stderr, "Memory allocation failed\n");
        TIFFClose(tif);
        return 1;
    }

    // Set some dummy values for testing
    tif->tif_dir.td_stripoffset_p[0] = 0;
    tif->tif_dir.td_stripbytecount_p[0] = 1000;
    tif->tif_dir.td_imagelength = 100;
    tif->tif_dir.td_planarconfig = PLANARCONFIG_CONTIG;
    tif->tif_dir.td_photometric = PHOTOMETRIC_RGB;

    // Cleanup
    free(tif->tif_dir.td_stripoffset_p);
    free(tif->tif_dir.td_stripbytecount_p);
    TIFFClose(tif);
    return 0;
}