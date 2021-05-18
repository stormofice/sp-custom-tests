#include "../halde.h"

/**
 * Repeatedly mallocs and frees the same section over and over again 
 * This should only create 2 blocks in total
*/
void test() {
    printList();
    for (int i = 0; i < 16; i++) {
        void* a = malloc(16);
        printList();
        free(a);
    }
    printList();
}