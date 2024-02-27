#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,_first,_last,construct,self,V:2.6-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copy(a[0:n])
    {
        #pragma acc kernels loop tile(16)
        for (int x = 0; x < n; ++x){
            #pragma acc loop tile(16)
            for (int y = 0; y < n; ++y){
                a[x] = a[x] + a[y];
            }
        }
        #pragma acc update self(a[0:n])
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            a[x] = a[x] + a[y];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (2 * a[x])) > PRECISION){
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