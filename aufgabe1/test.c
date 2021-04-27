#include <stdio.h>
#include <stdlib.h>

int removeElement();
int insertElement(int);

#define MAGENTA "\x1B[35m"
#define RED "\x1B[31m"
#define CYAN "\x1B[36m"
#define GREEN "\x1B[32m"
#define ORANGE "\x1B[33m"
#define RESET "\x1B[0m"

int __wrap_main(int argc, const char* argv[]) {
    printf(MAGENTA ":=:=: [Custom Test] lilo.c v1.3 :=:=:\n");
    printf("https://github.com/stormofice/sp-custom-tests\n");
    printf(ORANGE "This does not test the order of your elements or the head variable due to limitations of this testing method\n");
    printf(RED "! While this test shouldn't alter/destroy anything, it may happen due to bugs !\n");
    printf("! I do not take responsibilty for errors that may result of this !\n");
    printf(ORANGE "Press any key to continue\n");

    getchar();

    printf(CYAN ":=: Static constants test :=:\n");
    int mx = removeElement();
    if (mx != -1) {
        printf(RED "[ERROR:%3d] Expected: -1, but was %3d\n", __LINE__, mx);
        printf("\x1B[0m");
        abort();
    }
    int mt = insertElement(0);
    if (mt != 0) {
        printf(RED "[ERROR:%3d] Expected: 0, but was %3d\n", __LINE__, mt);
        printf("\x1B[0m");
        abort();
    }
    int mr = removeElement();
    if (mr != 0) {
        printf(RED "[ERROR:%3d] Expected: 0, but was %3d\n", __LINE__, mr);
        printf("\x1B[0m");
        abort();
    }
    printf(GREEN "[PASSED:%3d] Constants test\n", __LINE__);

    printf(CYAN ":=: Static negative numbers test :=:\n");
    for (int i = -1; i > -65536; i--) {
        int x = insertElement(i);
        if (-1 != x) {
            printf(RED "[ERROR:%3d] Expected: -1, but was %3d\n", __LINE__, i);
            printf("\x1B[0m");
            abort();
        }
    }

    printf(GREEN "[PASSED:%3d] Negative numbers\n", __LINE__);

    printf(CYAN ":=: Sequential test, this could take a while :=:\n");
    for (int i = 0; i < 32768; i++) {
        int x = insertElement(i);
        if (i != x) {
            printf(RED "[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i, x);
            printf("\x1B[0m");
            abort();
        }
    }

    printf(GREEN "[PASSED:%3d] Sequential insertion\n", __LINE__);

    for (int i = 0; i < 32768; i++) {
        int x = insertElement(i);
        if (-1 != x) {
            printf(RED "[ERROR:%3d] Expected: -1, but was %3d\n", __LINE__, i);
            printf("\x1B[0m");
            abort();
        }
    }

    printf(GREEN "[PASSED:%3d] Sequential duplicate values\n", __LINE__);

    for (int i = 0; i < 32768; i++) {
        int x = removeElement();
        if (i != x) {
            printf(RED "[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i, x);
            printf("\x1B[0m");
            abort();
        }
    }

    printf(GREEN "[PASSED:%3d] Sequential remove\n", __LINE__);

    printf(CYAN ":=: Repeating patterns test :=:\n");

    for (int i = 0; i < 1024; i++) {
        int randomValue = 0 + rand() / (RAND_MAX / ((RAND_MAX - 4) - 0 + 1) + 1);
        int x = insertElement(randomValue);
        if (randomValue != x) {
            printf(RED "[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__,
                   randomValue, x);
            printf("\x1B[0m");
            abort();
        }
        int y = removeElement();
        if (randomValue != y) {
            printf(RED "[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__,
                   randomValue, y);
            printf("\x1B[0m");
            abort();
        }
    }

    printf(GREEN "[PASSED:%3d] Single element shuffle\n", __LINE__);

    printf(RESET);

    exit(EXIT_SUCCESS);
}