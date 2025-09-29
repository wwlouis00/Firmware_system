/**
 *
 * @file      main.c
 *
 * @author    Louis wang
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math_utils.h"

void Test_ModuleName(void)
{
    // Add your test code here
    printf("Testing ModuleName...\n");
    // Example test case
    int result = add(2, 3);
    if (result == 5) {
        printf("Test passed!\n");
    } else {
        printf("Test failed! Expected 5 but got %d\n", result);
    }
}

int main(void) {

    
    int a = 12, b = 18;
    printf("a + b = %d\n", add(a, b));
    printf("a * b = %d\n", multiply(a, b));
    Test_ModuleName();
    printf( "\n BUILD TIME: %s %s\n",__DATE__, __TIME__ );
    printf("\n========================================\n");
    printf("LOG UART PORT\n");
    printf("========================================\n");


#ifdef EMBEDDED
    while(1); // MCU 版本保留
#endif
    return 0;
}
