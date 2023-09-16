#include "acc_testsuite.h"

int test(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n]) //copy data to device
    {
        #pragma acc parallel
        {
            #pragma acc loop gang // gang clause for distributing iterations among gangs
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}