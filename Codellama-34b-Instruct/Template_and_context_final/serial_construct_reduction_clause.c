#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc_testsuite.h>

#define SEED 12345
#define NUM_TEST_CALLS 100

int test1(){
    int err = 0;
    srand(SEED);

    int a[100];
    int b[100];
    int c[100];

    for (int i = 0; i < 100; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;
    }

    #pragma acc serial
    {
        #pragma acc reduction(+:c)
        for (int i = 0; i < 100; i++) {
            c[i] += a[i] + b[i];
        }
    }

    for (int i = 0; i < 100; i++) {
        if (c[i] != a[i] + b[i]) {
            err = 1;
            break;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test1();
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}