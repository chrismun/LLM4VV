#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct tile clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = new real_t[30000];
    real_t * b = new real_t[30000];
    real_t * c = new real_t[30000];

    for (int x = 0; x < 30000; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:30000], b[0:30000]) copyout(c[0:30000])
    {
        #pragma acc parallel
        {
            #pragma acc loop tile(12, 3)
            for (int x = 0; x < 100; ++x){
                #pragma acc loop tile(*, 7)
                for (int y = 0; y < 100; ++y){
                    #pragma acc loop tile(2)
                    for (int z = 0; z < 100; ++z){
                        c[(x * 100 + y) * 100 + z] = a[(x * 100 + y) * 100 + z] + b[(x * 100 + y) * 100 + z];
                    }
                }
            }
        }
    }

    for (int x = 0; x < 30000; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > 10*FLP_EPSILON){
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