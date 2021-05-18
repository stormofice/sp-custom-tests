#include "../halde.h"

/**
 * Fills the memory with small blocks [32] and tries to free it after it is full
 * Frees everything afterwards
 * [No overflow]
*/
void test() {
    char* mem[32768];

    for (int i = 0; i < 32768; i++) {
        mem[i] = malloc(16);
        printList();
    }

    for (int i = 0; i < 32768; i++) {
        free(mem[i]);
    }

    printList();
}