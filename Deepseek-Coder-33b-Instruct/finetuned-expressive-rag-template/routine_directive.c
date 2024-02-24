#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#pragma acc routine seq
void test_routine() {
    printf("Inside test_routine\n");
}

int main() {
    #pragma acc parallel
    {
        test_routine();
    }
    return 0;
}