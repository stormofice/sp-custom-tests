#include <stdlib.h>

#include "../halde.h"

#ifndef SIZE
#define SIZE (1024 * 1024 * 1)
#endif
/**
 * Malloc one big chunk that is too large -> ENOMEM
*/
void test() {
    printList();
    char* x = malloc(SIZE + 1);
    if (x == NULL)
        perror("malloc");
}