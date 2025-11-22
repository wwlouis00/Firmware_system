#include "command.h"
#include "math_utils.h"
#include "version.h"

void test_module_name(void) {
    int result = add(2, 3);
    if (result == 5)
        printf("[PASS] add(2,3) == 5\n");
    else
        printf("[FAIL] add(2,3) expected 5, got %d\n", result);
}

void cmd_test(void) {
    printf("Executing test_module_name()...\n");
    test_module_name();
}

void cmd_math(int a, int b) {
    printf("add(%d, %d) = %d\n", a, b, add(a, b));
    printf("multiply(%d, %d) = %d\n", a, b, multiply(a, b));
}

void cmd_info(void) {
    printf("[BUILD INFO] %s %s\n", __DATE__, __TIME__);
    printf("[VERSION] MP Ver: %s%03d_V%03d\n", PROJECT, TSTCODE_SUBVER, TSTCODE_VER);
}

void cmd_help(void) {
    printf("\nAvailable commands:\n");
    printf("  .TEST  - run tests\n");
    printf("  .MATH  - math operations\n");
    printf("  .INFO  - build/version info\n");
    printf("  .HELP  - show help\n");
}
