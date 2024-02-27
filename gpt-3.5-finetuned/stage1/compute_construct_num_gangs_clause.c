#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() != acc_device_none){
        real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
        real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
        real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));

        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = 0;
            c[x] = 0;
        }

        #pragma acc data copyin(a[0:n]) copyout(c[0:n])
        {
            #pragma acc compute num_gangs(16)
            {
                #pragma acc loop gang
                for (int x = 0; x < 16; ++x){
                    #pragma acc loop
                    for (int y = 0; y < n / 16; ++y){
                        c[x * (n / 16) + y] = a[x * (n / 16) + y];
                    }
                }
            }
        }

        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - a[x]) > PRECISION){
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