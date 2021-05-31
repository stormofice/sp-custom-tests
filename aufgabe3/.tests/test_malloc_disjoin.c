#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../halde.h"

#define MEMORY_SIZE (1 << 20)
#define CONTROL_SIZE 16
#define MAX_MALLOC (MEMORY_SIZE - CONTROL_SIZE)

void test() {
    char* pointers[20] = {NULL};
    size_t sizes[20] = {0};

    bool alloc_map[MAX_MALLOC];
    memset(alloc_map, 0, sizeof(alloc_map));

    // malloc all to get the lowest address
    char* low = my_malloc(MAX_MALLOC);
    assert(low != NULL);
    my_free(low);

    for (int i = 0; i < 10000; i++) {
        if (rand() % 2) {  // malloc
            size_t request = rand() % 1000;
            int pi;
            for (pi = 0; pi < 20; pi++) {
                if (pointers[pi] == NULL) break;
            }
            if (pi < 20) {
                pointers[pi] = my_malloc(request);
                sizes[pi] = request;
                if (pointers[pi] != 0) {
                    // malloc successfull -> mark region
                    ptrdiff_t offset = pointers[pi] - low;
                    for (size_t oi = 0; oi < request; oi++) {
                        assert(alloc_map[offset + oi] == false);
                        alloc_map[offset + oi] = true;
                    }
                }
            }
        } else {  // free
            bool all_free = true;
            for (int pi = 0; pi < 20; pi++)
                if (pointers[pi]) all_free = false;
            if (!all_free) {
                for (;;) {
                    int pi = rand() % 20;
                    if (pointers[pi] != NULL) {
                        my_free(pointers[pi]);
                        memset(alloc_map + (pointers[pi] - low), 0, sizes[pi]);
                        pointers[pi] = NULL;
                        break;
                    }
                }
            }
        }
    }
}
