void assert_equals_int(int, int, const char[], int);
void assert_equals_ptr(void *, void *, const char[], int);
void assert_null(void *, const char[], int);
void assert_not_null(void *, const char[], int);

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"