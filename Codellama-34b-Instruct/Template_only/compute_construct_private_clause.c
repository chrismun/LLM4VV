#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);
    int *c = (int *)malloc(sizeof(int) * 10);

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = i * 2;
        c[i] = a[i] + b[i];
    }

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = i * 2;
        b[i] = i * 3;
        c[i] = a[i] + b[i];
    }

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = i * 3;
        b[i] = i * 4;
        c[i] = a[i] + b[i];
    }

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = i * 4;
        b[i] = i * 5;
        c[i] = a[i] + b[i];
    }

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = i * 5;
        b[i] = i * 6;
        c[i] = a[i] + b[i];
    }

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = i * 6;
        b[i] = i * 7;
        c[i] = a[i] + b[i];
    }

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = i * 7;
        b[i] = i * 8;
        c[i] = a[i] + b[i];
    }

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = i * 8;
        b[i] = i * 9;
        c[i] = a[i] + b[i];
    }

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = i * 9;
        b[i] = i * 10;
        c[i] = a[i] + b[i];
    }

    for (int i = 0; i < 10; i++) {
        if (a[i] != i * 10 || b[i] != i * 10 || c[i] != i * 20) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}