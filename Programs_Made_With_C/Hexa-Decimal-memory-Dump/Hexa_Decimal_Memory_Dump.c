#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main() {
    printf("\033[2j\033[?25l");
    long addr = 0x7ffe0000;
    while (1) {
        printf("\033[H\033[1;36m\n [ REAl-TIME MEMORY DUMP SCAN ]\n\n");
        for (int i = 0; i < 12; i++) {
            printf("\033[1;33m%016lx: ", addr + i * 16);
            for (int j = 0; j < 16; j++) {
                unsigned char byte = *((unsigned char*)(addr + i * 16 + j));
                printf("%02x ", byte);
            }
            printf("\n");
        }
    }

    return 0;
}
