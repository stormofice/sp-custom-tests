#include "../halde.h"

/**
 * Test some simple reallocations 
*/
void test() {
    char* x = malloc(128);
    x = realloc(x, 0);
    printList();
    x = malloc(256);
    printList();
    x = realloc(x, 512);
    printList();
    x = realloc(x, 128);
    printList();
    free(x);
    printList();
}