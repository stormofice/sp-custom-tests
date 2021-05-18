#include <stdlib.h>

#include "../halde.h"

/**
 * Fills the memory with small blocks [32] and tries to free it after it is full
 * Frees everything afterwards
 * [OVERFLOWS]
*/
void test() {
    // 32769 blocks with size 16
    char* mem[32769];

    for (int i = 0; i < 32769; i++) {
        mem[i] = malloc(16);
        if (mem[i] == NULL) {
            perror("malloc");
        }
        printList();
    }

    for (int i = 0; i < 32769; i++) {
        free(mem[i]);
    }

    printList();
}