#include "openacc_testsuite.h"

#ifndef ASYNC_TEST
// ASYNC_TEST:parallel,async,V:2.0-2.7
void async_test() {
    int error = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int i = 0; i < n; ++i){
        a[i] = rand() / (real_t)(RAND_MAX / 10);
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc kernels async
        for (int i = 0; i < n; ++i){
            b[i] = a[i];
        }

        #pragma acc wait
    }

    for (int i = 0; i < n; ++i){
        if (fabs(b[i] - a[i]) > PRECISION){
            error++;
        }
    }

    if(error != 0) {
        printf("Async test failed with %d errors\n", error);
    } else {
        printf("Async test passed\n");
    }
}
#endif

int main() {
    async_test();
    return 0;
}