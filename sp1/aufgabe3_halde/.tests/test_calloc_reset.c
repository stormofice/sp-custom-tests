#include <stdio.h>
#include <stdlib.h>

#include "../halde.h"

/**
 * Mallocs a block and writes values to its memory, frees it subsequently
 * Calloc the same are again and check its value
*/
void test() {
    printList();
    char* temp = malloc(64);
    printList();
    for (int i = 0; i < 64; i++)
        temp[i] = i;
    free(temp);
    printList();
    temp = calloc(2, 32);
    printList();
    for (int i = 0; i < 64; i++) {
        if (temp[i] != 0) {
            fprintf(stderr, "calloc did not set 0x0 correctly at pos %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    printList();
    free(temp);
    printList();
}
