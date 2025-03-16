#include "ieee80211.h"
#include "ieee80211_hdr.h"
#include "plugins_types.h"
#include <stdlib.h>
#include "dlt_utils.h"
#include "ieee80211_types.h"
#include "tcpedit_stub.h"
#include <string.h>
#include "tcpedit.h"
#include <stdio.h>
#include <assert.h>
#include <pcap.h>  // Include pcap library for pcap functions

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read the packet length from the file
    int pktlen;
    if (fread(&pktlen, sizeof(int), 1, inputFile) != 1) {
        fprintf(stderr, "Error reading packet length from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Allocate memory for the packet
    u_char *packet = (u_char *)malloc(pktlen);
    if (!packet) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }

    // Read the packet data from the file
    if (fread(packet, sizeof(u_char), pktlen, inputFile) != pktlen) {
        fprintf(stderr, "Error reading packet data from file.\n");
        free(packet);
        fclose(inputFile);
        return 1;
    }

    // Close the file
    fclose(inputFile);

    // Create a dummy context for the function call
    tcpeditdlt_t *ctx = (tcpeditdlt_t *)malloc(sizeof(tcpeditdlt_t));
    if (!ctx) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(packet);
        return 1;
    }

    // Call the ieee80211_is_data function
    int result = ieee80211_is_data(ctx, packet, pktlen);

    // Print the result
    printf("ieee80211_is_data returned: %d\n", result);

    // Clean up
    free(packet);
    free(ctx);

    return 0;
}