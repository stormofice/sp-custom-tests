#include "../lib/customtest.h"
#include <stddef.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    void *test = malloc(1);
    assert_equals_int(1, 2, __func__, __LINE__);
    assert_equals_int(0, 0, __func__, __LINE__);
    assert_equals_ptr(NULL, test, __func__, __LINE__);
    assert_null(NULL, __func__, __LINE__);
    free(test);
    return 0;
}
