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
    int *d_a = (int *)acc_malloc(10 * sizeof(int));

    for (int x = 0; x < 10; ++x) {
        a[x] = x;
    }

    acc_map_data(d_a, a, 10 * sizeof(int));

    #pragma acc data copy(d_a[0:10]) delete(d_a)
    {
        #pragma acc parallel loop
        for (int x = 0; x < 10; ++x) {
            d_a[x] += 1;
        }
    }

    for (int x = 0; x < 10; ++x) {
        if (a[x] != x + 1) {
            err = 1;
        }
    }

    acc_unmap_data(d_a);
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