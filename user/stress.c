#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define ITERATIONS 5000000000
uint16 lfsr = 0xACE1u;

uint16 rand() {
    uint16 bit = 0;
    bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
    return lfsr = (lfsr >> 1) | (bit << 15);
}


int main(int argc, char *argv[]) {
    int n, pid = 0;
    uint64 i, j, x = 0;

    if(argc != 2)
        n = 2;
    else
        n = atoi(argv[1]);

    if(n < 0 || n > 32)
        n = 2;

    for(i = 0; i < n; n++) {
        pid = fork2(rand());
        
        if(pid > 0) {
            pid = wait(0);
        }
        else if(pid == 0) {
            for(j = 0; j < ITERATIONS; j++)
                x = x + 3.14 * 89.64;
            break;
        }
        else {
            printf("stress test fail: could not fork\n");
            exit(1);
        }
    }
    printf("stress test OK\n");
    exit(0);
}