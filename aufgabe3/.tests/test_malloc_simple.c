#include "../halde.h"

/**
 *  Simple and small allocation with subsequent free
*/
void test() {
    printList();
    char* test2 = malloc(20);
    printList();
    free(test2);
    printList();
    char* test3 = malloc(40);
    printList();
    free(test3);
    printList();
}