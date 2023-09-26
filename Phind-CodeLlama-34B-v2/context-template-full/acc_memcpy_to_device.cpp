#include "acc_testsuite.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <openacc.h>

#ifndef T1
/*T1:acc memcpy to device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int N = 100;
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)acc_malloc(N * sizeof(int));

    for (int x = 0; x < N; ++x){
        a[x] = rand() % N;
    }

    acc_memcpy_to_device(b, a, N * sizeof(int));
    acc_memcpy_from_device(a, b, N * sizeof(int));

    for (int x = 0; x < N; ++x){
        if (a[x] != b[x]){
            err = 1;
            break;
        }
    }

    free(a);
    acc_free(b);

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