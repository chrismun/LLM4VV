#include "acc_testsuite.h"
#include <math.h>
#include <stdio.h>

//T1:parallel,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }

        #pragma acc parallel async(2)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] += a[x];
            }
        }

        #pragma acc wait(1,2)
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x]*2 - b[x]) > PRECISION){
            err++;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }

    if (failed != 0){
        failcode++;
    }

    return failcode;
}