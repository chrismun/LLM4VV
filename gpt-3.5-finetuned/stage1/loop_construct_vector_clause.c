#include "acc_testsuite.h"

#ifndef T1
//T1:loop,construct,loop,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    // Input vectors
    float * a = (float *)malloc(10 * n * sizeof(a));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:10*n]) copyout(a[0:10*n])
    {
        #pragma acc loop vector
        for (int x = 0; x < 10; ++x){
            for (int y = 0; y < n; ++y){
                a[x * n + y] = a[x * n + y] * 2;
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            if (fabs(a[x * n + y] - (2 * a[x * n + y])) > 1){
                err = 1;
            }
        }
    }

    return err;
}

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