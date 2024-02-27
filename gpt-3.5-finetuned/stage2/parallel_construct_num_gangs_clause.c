#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() != acc_device_none){
        real_t * a = (real_t *)malloc(n * sizeof(real_t));
        real_t * b = (real_t *)malloc(n * sizeof(real_t));

        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(n);
        }

        #pragma acc data copy(a[0:n])
        {
            #pragma acc parallel num_gangs(16)
            {
                #pragma acc loop gang
                {
                    for (int x = 0; x < 15; ++x){
                        a[x] = 0.0;
                    }
                }
            }
        }

        for (int x = 0; x < 16; ++x){
            if (fabs(a[x] - 0.0) > PRECISION){
                err += 1;
            }
        }

        #pragma acc exit data copyout(a[0:n])

        if (err == 0){
            for (int x = 0; x < n; ++x){
                if (fabs(a[x] - 0.0) > PRECISION){
                    err = 1;
                }
            }
        }
    }
    else{
        return err;
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