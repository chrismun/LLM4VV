#include "acc_testsuite.h"
//T1:kernels,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 2);
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels present_or_copyout(a[0:n])
        {
            #pragma acc loop self
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * 2;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] / 2 - b[x]) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    if (failcode != 0){
        printf("Error:Test failed. Code-%d\n",failcode);
    }
    else{
        printf("Test passed.\n");
    }

    return failcode;
}