int main(int argc, char const *argv[]) {
    printf("\x1B[35m:=:=: [Custom Test] lilo.c v1.0 :=:=:\n");
    printf("\x1B[35mhttps://github.com/stormofice/sp-custom-tests\n");
    printf("\x1B[33m!!! Disable track-origins=yes in your valgrind flags or this will take *forever*!!!\n");
    printf("\x1B[33mIf you find a bug in your code and want to use track-origins, lower the numbers (16384) -> (256)\n");

    printf("\x1B[36m:=:Static constants test:=:\n");

    if (head) {
        printf("\x1B[31m[ERROR:%3d] HEAD should be NULL\n", __LINE__);
        printf("\x1B[0m");
        abort();
    }

    int mx = removeElement();
    if (mx != -1) {
        printf("\x1B[31m[ERROR:%3d] Expected: -1, but was %3d\n", __LINE__, mx);
        printf("\x1B[0m");
        abort();
    }
    int mt = insertElement(0);
    if (mt != 0) {
        printf("\x1B[31m[ERROR:%3d] Expected: -1, but was %3d\n", __LINE__, mt);
        printf("\x1B[0m");
        abort();
    }
    int mr = removeElement();
    if (mr != 0) {
        printf("\x1B[31m[ERROR:%3d] Expected: 0, but was %3d\n", __LINE__, mt);
        printf("\x1B[0m");
        abort();
    }
    printf("\x1B[32m[PASSED:%3d] Constants test\n", __LINE__);

    printf("\x1B[36m:=:Static negative numbers test:=:\n");
    for (int i = -1; i > -65536; i--) {
        int x = insertElement(i);
        if (-1 != x) {
            printf("\x1B[31m[ERROR:%3d] Expected: -1, but was %3d\n", __LINE__, i);
            printf("\x1B[0m");
            abort();
        }
    }

    printf("\x1B[32m[PASSED:%3d] Negative numbers\n", __LINE__);

    printf("\x1B[36m:=:Sequential test, this could take a while:=:\n");
    for (int i = 0; i < 32768; i++) {
        int x = insertElement(i);
        if (i != x) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i, x);
            printf("\x1B[0m");
            abort();
        }
    }

    printf("\x1B[32m[PASSED:%3d] Sequential insertion\n", __LINE__);

    for (int i = 0; i < 32768; i++) {
        int x = insertElement(i);
        if (-1 != x) {
            printf("\x1B[31m[ERROR:%3d] Expected: -1, but was %3d\n", __LINE__, i);
            printf("\x1B[0m");
            abort();
        }
    }

    printf("\x1B[32m[PASSED:%3d] Sequential duplicate values\n", __LINE__);

    for (int i = 0; i < 32768; i++) {
        int x = removeElement();
        if (i != x) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i, x);
            printf("\x1B[0m");
            abort();
        }
    }

    if (head) {
        printf("\x1B[31m[ERROR:%3d] HEAD should be NULL\n", __LINE__);
        printf("\x1B[0m");
        abort();
    }

    printf("\x1B[32m[PASSED:%3d] Sequential remove\n", __LINE__);

    printf("\x1B[36m:=:Repeating patterns test:=:\n");

    for (int i = 0; i < 1024; i++) {
        if (head) {
            printf("\x1B[31m[ERROR:%3d] Head should be NULL\n", __LINE__);
            printf("\x1B[0m");
            abort();
        }
        int randomValue = 0 + rand() / (RAND_MAX / ((RAND_MAX - 4) - 0 + 1) + 1);
        int x = insertElement(randomValue);
        if (randomValue != x) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, randomValue, x);
            printf("\x1B[0m");
            abort();
        }
        int y = removeElement();
        if (randomValue != y) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, randomValue, y);
            printf("\x1B[0m");
            abort();
        }
    }

    printf("\x1B[32m[PASSED:%3d] Single element shuffle\n", __LINE__);
    printf("\x1B[36m:=:Static order test:=:\n");

    for (int i = 1; i < 64; i += 2) {
        int t = insertElement(i);
        if (i != t) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i, t);
            printf("\x1B[0m");
            abort();
        }
    }

    for (int i = 0; i < 64; i += 2) {
        listenelement *start = head;
        int x = 1;
        for (int k = 0; k < i / 2; k++) {
            if (start->value != x) {
                printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, x, start->value);
                printf("\x1B[0m");
                abort();
            }
            x += 2;
            start = start->next;
        }
        if (start->value != i + 1) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i + 1, start->value);
            printf("\x1B[0m");
            abort();
        }
    }
    printf("\x1B[0m");
    for (int i = 1; i < 64; i += 2) {
        int y = removeElement();
        if (y != i) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i, y);
            printf("\x1B[0m");
            abort();
        }
        listenelement *start = head;

        int x = y + 2;
        for (int k = 0; k < (64 - i) / 2; k++) {
            if (start->value != x) {
                printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i, y);
                printf("\x1B[0m");
                abort();
            }
            start = start->next;
            x += 2;
        }
    }
    printf("\x1B[32m[PASSED:%3d] Static order\n", __LINE__);

    printf("\x1B[0m");

    exit(EXIT_SUCCESS);
}