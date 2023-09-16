#include "acc_testsuite.h"
#include <stdlib.h>

real_t a[N], b[N], c[N];
#pragma acc declare device_resident(a, b, c)

int wait_test()
{
    int i;
    int async1 = 20, async2 = 30;
    int errors = 0;

    for (i = 0; i < N; i++) {
        a[i] = 1.0f;
        b[i] = 2.0f;
        c[i] = 0.0f;
    }

    #pragma acc parallel async(async1)
    #pragma acc loop
    for (i = 0; i < N; i++){
        a[i] += b[i];
    }

    #pragma acc parallel async(async2)
    #pragma acc loop
    for (i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    }

    #pragma acc wait(async1)

    #pragma acc parallel async(async2)
    #pragma acc loop
    for (i = 0; i < N; i++){
        c[i] += a[i];
    }

    #pragma acc wait(async2)

    for (i = 0; i < N; i++) {
        real_t expected = 2.0f * a[i] + b[i];
        if (c[i] != expected){
            errors += 1;
        }
    }

    return errors;
}

int main(){
    int errors = wait_test();
    if (errors != 0){
        printf("Test failed with %d errors\n", errors);
        return 1;
    }
    printf("Test passed\n");
    return 0;
}