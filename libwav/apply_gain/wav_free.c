#include "wav_gain.c"
#include <stdio.h>
#include "../../libwav.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    wav_file wavfile;

    // Read the WAV file
    if (wav_read(&wavfile, filename) != WAV_OK) {
        printf("Error: Couldn't read the file!\n");
        return 1;
    }

    // Apply gain (optional, but included to match the slice code)
    apply_gain(&wavfile, 2.0);

    // Free the WAV file data
    wav_free(&wavfile);

    return 0;
}