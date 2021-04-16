#include "customtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static const bool EXIT_ON_FAILURE = false;

void print_test_result(bool success, char message[], const char function[], int line)
{

    printf(success ? GREEN : RED);
    printf(success ? "[PASS ] " : "[ERROR] ");

    printf(BLUE);
    printf("{%s:%2d} ", function, line);
    printf(RESET);
    printf(success ? GREEN : RED);
    printf("%s\n", message);

    printf(RESET);

    if (!success && EXIT_ON_FAILURE)
        exit(-1);
}

void assert_equals_int(int one, int two, const char function[], int line)
{
    bool condition = one == two;
    char *text;
    text = malloc(64);
    snprintf(text, 64, condition ? "%d is equals to %d" : "%d is not equals to %d", one, two);
    print_test_result(condition, text, function, line);
    free(text);
}

void assert_equals_ptr(void *one, void *two, const char function[], int line)
{
    bool condition = one == two;
    char *text;
    text = malloc(64);
    snprintf(text, 64, condition ? "%p is equals to %p" : "%p is not equals to %p", one, two);
    print_test_result(condition, text, function, line);
    free(text);
}

void assert_not_null(void *in, const char function[], int line)
{
    bool condition = in;
    char *text;
    text = malloc(64);
    snprintf(text, 64, condition ? "%p is not null" : "%p is null", in);
    print_test_result(condition, text, function, line);
    free(text);
}

void assert_null(void *in, const char function[], int line)
{
    bool condition = !in;
    char *text;
    text = malloc(64);
    snprintf(text, 64, condition ? "%p is null" : "%p is not null", in);
    print_test_result(condition, text, function, line);
    free(text);
}
