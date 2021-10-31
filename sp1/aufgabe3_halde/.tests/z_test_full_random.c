#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../halde.h"

// CONFIG
// NOTE: As this does change the output to stderr (which the test checks for differences),
// it could seem as if the test has passed even if it has not.
_Bool doesPrintList = true;
_Bool doesPrintCommands = false;
_Bool doesPrintAdditionalInfo = true;

char *translate(int num) {
    if (num == 0)
        return "malloc";
    else if (num == 1)
        return "calloc";
    else if (num == 2)
        return "realloc";
    else if (num == 3)
        return "free";
    return "error";
}

/**
 * Test your implementation against the reference with random calls
 * If your test failed, check local_out and reference_out
 * It will contain all the necessary info to reproduce the same behaviour
*/
void test(unsigned int seed) {
    int ACTION_COUNT = 128;
    int SKIP_EMPTY_ALLOC = 1;

    // Seed PRNG
    srand(seed);

    char *blocks[ACTION_COUNT];
    int allocatedBlocks = 0;
    if (doesPrintList) printList();
    for (int i = 0; i < ACTION_COUNT; i++) {
        int random = rand() % 4;
        int multiplier = rand() % 10;
        int amount = (rand() % 256) * multiplier;

        if (doesPrintAdditionalInfo) fprintf(stderr, "=== mode: %s, multiplier: %d, amount: %d, full: %d ===\n", translate(random), multiplier, amount, multiplier * amount);

        switch (random) {
            case 0:;
                if (SKIP_EMPTY_ALLOC && amount == 0)
                    continue;
                blocks[allocatedBlocks] = (char *)malloc(amount);
                if (doesPrintCommands) fprintf(stderr, "malloc(%d);\n", amount);
                allocatedBlocks++;
                break;
            case 1:;
                if (SKIP_EMPTY_ALLOC && amount == 0)
                    continue;
                blocks[allocatedBlocks] = (char *)calloc(1, amount);
                if (doesPrintCommands) fprintf(stderr, "calloc(1,%d);\n", amount);
                allocatedBlocks++;
                break;
            case 2:;
                if (allocatedBlocks == 0) {
                    if (doesPrintAdditionalInfo) fprintf(stderr, "=== zero allocated, no realloc possible ===\n");
                    continue;
                }
                int delta_block = rand() % allocatedBlocks;
                blocks[delta_block] = (char *)realloc(blocks[delta_block], amount);
                if (doesPrintCommands) fprintf(stderr, "realloc(%d,%d);\n", **&blocks[delta_block], amount);
                break;
            case 3:;
                if (allocatedBlocks == 0) {
                    if (doesPrintAdditionalInfo) fprintf(stderr, "=== zero allocated, no free possible ===\n");
                    continue;
                }
                int free_block = rand() % allocatedBlocks;
                free(blocks[free_block]);
                if (doesPrintCommands) fprintf(stderr, "free(%d);\n", **&blocks[free_block]);
                allocatedBlocks--;
                break;
        }
        if (doesPrintList) printList();
    }
    if (doesPrintList) printList();
}