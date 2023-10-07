#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>

int test1() {
    int err = 0;
    const int arr_size = 1000;
    float *h_x, *h_y, *h_res;

    h_x = (float *) malloc(arr_size * sizeof(float));
    h_y = (float *) malloc(arr_size * sizeof(float));
    h_res = (float *) malloc(arr_size * sizeof(float));

    for (int i = 0; i < arr_size; i++) {
        h_x[i] = i + 1;
        h_y[i] = i + 1;
    }

    #pragma acc data create(h_x[0:arr_size], h_y[0:arr_size]) copyout(h_res[0:arr_size])
    {
        #pragma acc kernels async
        for (int i = 0; i < arr_size; i++) {
            h_res[i] = h_x[i] + h_y[i];
        }

        acc_wait_all();
    }

    for (int i = 0; i < arr_size; i++) {
        if (h_res[i] != 2 * (i + 1) ) {
            err = 1;
            break;
        }
    }

    free(h_x);
    free(h_y);
    free(h_res);

    return err;
}

int main() {
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}