#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:acc memcpy d2d,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    double *h_src = (double *)malloc(n * sizeof(double));
    double *h_dest = (double *)malloc(n * sizeof(double));
    double *d_src, *d_dest;

    for (int i = 0; i < n; i++) {
        h_src[i] = rand() / (double)RAND_MAX;
        h_dest[i] = 0.0;
    }

    d_src = acc_malloc(n * sizeof(double));
    d_dest = acc_malloc(n * sizeof(double));

    acc_memcpy_to_device(d_src, h_src, n * sizeof(double));

    acc_memcpy_d2d(d_dest, d_src, n * sizeof(double), acc_device_nvidia, acc_device_nvidia);

    acc_memcpy_from_device(h_dest, d_dest, n * sizeof(double));

    for (int i = 0; i < n; i++) {
        if (h_src[i] != h_dest[i]) {
            err = 1;
            break;
        }
    }

    acc_free(d_src);
    acc_free(d_dest);
    free(h_src);
    free(h_dest);

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