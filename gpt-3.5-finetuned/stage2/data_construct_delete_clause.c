#include "acc_testsuite.h"
#ifndef T1
//T1:data construct delete clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_ptr = (real_t *)malloc(n * sizeof(real_t));
    int * deleted = (int *)malloc(n * sizeof(int));
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < n; ++x){
        a_ptr[x] = a[x];
        deleted[x] = 0;
    }

    #pragma acc enter data create(a[0:n])

    for (int x = 0; x < n; ++x){
        a[x] = 0;
    }
    #pragma acc update device(a[0:n])
    #pragma acc data delete(a[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = x;
            }
        }
    }
    #pragma acc exit data copyout(a[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - a_ptr[x]) > PRECISION){
            err = 1;
        }
    }

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