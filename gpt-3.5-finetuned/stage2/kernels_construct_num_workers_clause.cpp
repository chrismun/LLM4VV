#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct num_workers clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = new real_t [4096];
    real_t *b = new real_t [4096];
    real_t *c = new real_t [4096];

    for (int x = 0; x < 4096; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:4096], b[0:4096]) copyout(c[0:4096])
    {
        #pragma acc kernels num_workers(16)
        {
            #pragma acc loop
            for (int x = 0; x < 16; ++x){
                #pragma acc loop worker
                for (int y = 0; y < 256; ++y){
                    #pragma acc loop vector
                    for (int z = 0; z < 16; ++z){
                        c[x * 256 * 16 + y * 16 + z] = a[x * 256 * 16 + y * 16 + z] + b[x * 256 * 16 + y * 16 + z];
                    }
                }
            }
        }
    }

    for (int x = 0; x < 4096; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
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