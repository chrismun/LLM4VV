#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

int test_func() {
    int err = 0;
    int* h = (int*)malloc(1000 * sizeof(int));
    int* d_h = (int*)malloc(1000 * sizeof(int));

    for(int i = 0; i < 1000; i++) {
        h[i] = i;
    }

    #pragma acc data copy(h[0:1000]) copyout(d_h[0:1000])
    {
        #pragma acc parallel loop async(1)
        for(int i = 0; i < 1000; i++) {
            h[i] += 1;
        }
        #pragma acc update host(d_h[0:1000]) async(1)
    }
    acc_wait(1);

    for(int i = 0; i < 1000; i++) {
        if (d_h[i] != h[i]) {
            err = 1;
        }
    }

    free(h);
    free(d_h);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_func();
    }
    if (failed != 0) {
        failcode = failcode + 1;
    }
    return failcode;
}