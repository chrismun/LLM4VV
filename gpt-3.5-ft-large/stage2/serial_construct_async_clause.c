#include "acc_testsuite.h"
#ifndef T1
//T1: serial construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x];
    }

    #pragma acc data copy(a[0:n])
    {
        #pragma acc serial async(1)
        {
            #pragma acc loop
            for (int x = 1; x < n; ++x){
                a[x] += a[x - 1];
            }
        }
        #pragma acc wait(1)
    }

    for (int x = 1; x < n; ++x){
        b[x] += b[x - 1];
    }
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err = 1;
            break;
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