#include "../halde.h"

struct mblock {
    struct mblock* next;
    size_t size;
    char memory[];
};

void test() {
    malloc(40);
    struct mblock* b = malloc(40);
    b[-1].size = 0x600df00d;
    b[-1].next = (void*)0xbe57f00d;
    free(b);
    fprintf(stderr, "bad magic, free shoud have aborted");
}