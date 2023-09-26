#include "acc_testsuite.h"

#ifndef T1
//T1:data,delete,V:2.5-4.5
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    #pragma acc enter data create(a[0:n]) copyout(b[0:n])

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc parallel num_gangs(1) num_workers(1) vector_length(1) present(a[0:n], b[0:n])
    {
        // Perform some computations on a and b
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] += 10;
            b[x] += 5;
        }
    }

    // Release memory allocated on the device
    #pragma acc exit data delete(a[0:n])

    // Verify if the values in b are correct
    for (int x = 0; x < n; ++x){
        if (b[x] != 5.0){
            err += 1;
            break;
        }
    }

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