#include <iostream>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:parallel, construct, num_workers clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1000;
    int *a = new int[size];
    int *b = new int[size];
    int expectedSum = 0, actualSum = 0;

    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        expectedSum += a[i];
    }

    #pragma acc parallel num_workers(4) copyout(b[0:size])
    {
        #pragma acc loop
        for(int i = 0; i < size; ++i) {
            b[i] = a[i];
        }
    }

    for (int i = 0; i < size; ++i) {
        actualSum += b[i];
    }

    if (expectedSum != actualSum) {
        err += 1;
    }

    delete[] a;
    delete[] b;

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