#include "../halde.h"
#include "stdlib.h"

void test() {
    printList();
    free(NULL);
    printList();
}