#include <stdio.h>
#include <stdlib.h>

#include "../halde.h"

/**
 * Allocates a block and frees it to check whether free resets the memory
 * [It should not do that]
*/
void test() {
    printList();
    char* x = calloc(1, 40);
    x[0] = 'A';
    printList();
    free(x);
    printList();
    if (x[0] != 'A') {
        fprintf(stderr, "Malloc should not reset memory");
        exit(EXIT_FAILURE);
    }
}