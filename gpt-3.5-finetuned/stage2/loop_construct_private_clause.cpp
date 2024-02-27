
#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = new real_t[n * 4];
    real_t * b = new real_t[n * 4];
    real_t * c = new real_t[n * 4];

    for (int x = 0; x < n * 4; ++x){
        a[x] = 0.0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(b[0:n*4], c[0:n*4]) copyout(a[0:n*4])
    {
        #pragma acc parallel
        {
            #pragma acc loop private(a)
            for (int x = 0; x < 2; ++x){
                int y;
                #pragma acc loop private(y)
                for (y = 0; y < 2; ++y){
                    a[(2 * x + y) * n] = b[(2 * x + y) * n] + c[(2 * x + y) * n];
                    #pragma acc loop
                    for (int z = 0; z < n - 1; ++z){
                        a[(2 * x + y) * n + 1 + z] = (a[(2 * x + y) * n] + b[(2 * x + y) * n + 1 + z]) / c[(2 * x + y) * n + 1 + z];
                    }
                }
            }
        }
    }

    for (int x = 0; x < n * 4; ++x){
        a[x] = a[x] / (b[x] + c[x]);
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