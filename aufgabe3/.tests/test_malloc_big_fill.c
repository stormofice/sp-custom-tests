#include <stdlib.h>

#include "../halde.h"

/**
 * Fills the memory with big chunks [65536] and tries to free it after it is full
 * Frees everything afterwards
 * [OVERFLOWS]
*/
void test() {
    char* a[64];

    for (int i = 0; i < 64; i++)
        a[i] = NULL;

    for (int i = 0; i < 64; i++) {
        char* c = malloc(65536);
        printList();
        a[i] = c;
    }
    printList();

    for (int i = 0; i < 64; i++)
        free(a[i]);
    printList();
}