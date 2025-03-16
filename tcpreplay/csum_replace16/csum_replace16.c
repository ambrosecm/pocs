#include "checksum.h"
#include <sys/socket.h>
#include <sys/types.h>
#include "incremental_checksum.h"
#include "config.h"
#include "common.h"
#include "dlt.h"
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include <string.h>
#include "tcpedit.h"
#include <stdio.h>
#include <pcap.h>  // 添加 pcap 头文件

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
    uint16_t old, new;
    if (fscanf(inputFile, "%hu %hu", &old, &new) != 2) {
        fprintf(stderr, "Error reading data from file.\n");
        fclose(inputFile);
        return 1;
    }

    // Close the input file
    fclose(inputFile);

    // Create a dummy TCP header for testing
    struct tcphdr tcp_hdr;
    tcp_hdr.th_sum = 0x1234; // Example checksum value

    // Convert old and new to __be32 type
    __be32 old_be32 = htonl((uint32_t)old);
    __be32 new_be32 = htonl((uint32_t)new);

    // Call the csum_replace16 function
    csum_replace16(&tcp_hdr.th_sum, &old_be32, &new_be32);

    // Output the result (for debugging purposes)
    printf("Updated checksum: 0x%04x\n", tcp_hdr.th_sum);

    return 0;
}