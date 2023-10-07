#include "acc_testsuite.h"

// Testing cache directive
int test_cache_directive(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // OpenACC parallel region with cache directive
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {  
        #pragma acc parallel loop
        {
            #pragma acc cache(a[0:n/2])
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err++;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_cache_directive();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }

    return failcode;
}