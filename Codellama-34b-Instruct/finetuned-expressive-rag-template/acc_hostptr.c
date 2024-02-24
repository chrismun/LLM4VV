#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc hostptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int N = 100;
    int *a = (int *)malloc(N * sizeof(int));
    int *d_a = (int *)acc_malloc(N * sizeof(int));

    for (int x = 0; x < N; ++x){
        a[x] = rand() % N;
        d_a[x] = a[x];
    }

    acc_map_data(a, d_a, N * sizeof(int));

    int *h_a = (int *)acc_hostptr(d_a);

    if (h_a != a){
        err = 1;
    }

    acc_unmap_data(a);
    acc_free(d_a);
    free(a);

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