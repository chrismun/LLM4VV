#include "acc_testsuite.h"
#ifndef T1
//T1:routine,attach-detach,async,V:1.0
int test1(){
    int async1;
    int async2;
    int err = 0;
    srand(SEED);

    int *h_a = (int *)malloc(n * sizeof(int));
    int *h_b = (int *)malloc(n * sizeof(int));
    int *h_c = (int *)malloc(n * sizeof(int));
    int *h_d = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        h_a[x] = rand() / (real_t)(RAND_MAX / 10);
        h_b[x] = rand() / (real_t)(RAND_MAX / 10);
        h_c[x] = 0.0;
        h_d[x] = 0.0;
    }

    #pragma acc data copyin(h_a[0:n], h_b[0:n]), create(h_c[0:n], h_d[0:n])
    {
        async1 = acc_async_test();
        #pragma acc parallel loop independent async
        for (int x = 0; x < n; ++x){
            h_c[x] = h_a[x] + h_b[x];
        }
        acc_attach(h_c); // Attach h_c to the accelerator device

        async2 = acc_async_test();
        #pragma acc parallel loop independent async
        for (int x = 0; x < n; ++x){
            h_d[x] = h_c[x] * h_b[x];
        }
        acc_detach(h_c); // Detach h_c from the accelerator device

        async2 = async2 or acc_async_test();
    }

    for (int x = 0; x < n; ++x){
        if (h_d[x] != (h_a[x] + h_b[x]) * h_b[x]){
            err += 1;
            break;
        }
    }

    free(h_a);
    free(h_b);
    free(h_c);
    free(h_d);

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