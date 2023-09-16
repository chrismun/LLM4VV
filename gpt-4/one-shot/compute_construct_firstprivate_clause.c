#include "acc_testsuite.h"

#ifndef FIRST_PRIVATE_TEST
// FIRST_PRIVATE_TEST:kernels,compute_construct,V:2.0-2.7

int test_first_private(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    real_t scalar = rand() / (real_t)(RAND_MAX / 10);

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop firstprivate(scalar)
            for (int x = 0; x < n; ++x){
                b[x] = a[x]*scalar;
            }
        }
        #pragma acc update host(b[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]*scalar) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int failed = 0;

#ifndef FIRST_PRIVATE_TEST
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_first_private();
    }
    if (failed != 0) {
        printf("Validation of compute construct firstprivate clause failed with %d errors.\n", failed);
        return 1;
    }
#endif

    printf("Validation of compute construct firstprivate clause succeeded.\n");
    return 0;
}