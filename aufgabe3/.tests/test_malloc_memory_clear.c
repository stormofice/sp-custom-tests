#include <stdio.h>
#include <stdlib.h>

#include "../halde.h"

void test() {
    printList();
    char* x = malloc(16);
    x[0] = 'A';
    free(x);
    printList();
    x = malloc(16);
    if (x[0] != 'A') {
        fprintf(stderr, "malloc should not reset its memory contents");
        exit(EXIT_FAILURE);
    }
    printList();
}