#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "../halde.h"

/**
 * This tests whether calloc handles an overflow while multiplying its input parameters correctly 
*/
void test() {
    size_t x = 0;
    x = ~x;
    x >>= 1;
    x = ~x;
    x |= 1;
    char* m1 = calloc(x, 2);

    int errno_save = errno;
    printList();
    if (m1 != NULL || errno_save != ENOMEM) {
        fprintf(stderr, "calloc did not handle multiplication overflow correctly");
        exit(EXIT_FAILURE);
    }
}