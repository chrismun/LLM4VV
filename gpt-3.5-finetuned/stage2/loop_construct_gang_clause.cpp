#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct gang clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a1 = new real_t[10 * n];
    real_t * a2 = new real_t[10 * n];

    for (int x = 0; x < 10 * n; ++x){
        a1[x] = 0;
        a2[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a2[0:10*n]) copyout(a1[0:10*n])
    {
        #pragma acc parallel loop gang private(temp)
        for (int y = 0; y < 10; ++y){
            temp = 0;
            #pragma acc loop gang
            for (int x = 0; x < n; ++x){
                temp = temp + a2[y * n + x];
            }
            #pragma acc loop gang
            for (int x = 0; x < n; ++x){
                a1[y * n + x] = a1[y * n + x] + a2[y * n + x] / temp;
            }
        }
    }

    for (int y = 0; y < 10; ++y){
        temp = 0;
        for (int x = 0; x < n; ++x){
            temp = temp + a2[y * n + x];
        }
        for (int x = 0; x < n; ++x){
            if (fabs(a1[y * n + x] - a2[y * n + x] / temp) > PRECISION){
                err += 1;
            }
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