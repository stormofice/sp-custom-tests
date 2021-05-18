#include <stdio.h>
#include <stdlib.h>

#include "../halde.h"

/**
 * Callocs a block (size 64) and checks its values
*/
void test() {
    printList();
    char* x = calloc(1, 64);
    for (int i = 0; i < 64; i++) {
        if (x[i] != 0) {
            fprintf(stderr, "calloc did not set 0x0 correctly at pos %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    printList();
    free(x);
    printList();
}