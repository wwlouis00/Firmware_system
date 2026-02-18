#include "math_utils.h"
#include <stdio.h>
#include <stdlib.h>

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

void cmd_math(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: .MATH a b\n");
        return;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    printf("add(%d, %d) = %d\n",      a, b, add(a, b));
    printf("multiply(%d, %d) = %d\n", a, b, multiply(a, b));
}