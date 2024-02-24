#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:data construct delete clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));

    #pragma acc enter data copyin(a[0:10])
    #pragma acc enter data copyin(b[0:10])

    for (int x = 0; x < 10; ++x) {
        a[x] = rand() % 100;
        b[x] = rand() % 100;
    }

    #pragma acc data delete(a[0:10])
    {
        #pragma acc parallel loop
        for (int x = 0; x < 10; ++x) {
            a[x] += b[x];
        }
    }

    for (int x = 0; x < 10; ++x) {
        if (a[x] != (rand() % 100 + rand() % 100)) {
            err = 1;
        }
    }

    #pragma acc exit data delete(a[0:10])
    #pragma acc exit data delete(b[0:10])

    free(a);
    free(b);

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