#include <stdio.h>
#include <openacc.h>

#define N 10

int main() {
    int a = 5;
    int b = 10;
    int c = 0;

    #pragma acc declare link(a)

    #pragma acc parallel
    {
        a += 1;
        b += 1;
        c = a + b;
    }

    printf("c = %d\n", c);

    return 0;