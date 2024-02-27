#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct if_present clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() != acc_device_none){
        real_t * a = (real_t *)malloc(n * sizeof(real_t));
        if (a == NULL){
            err = err + 1;
        }
        else {
            for (int x = 0; x < n; ++x){
                a[x] = rand() / (real_t)(RAND_MAX / 10);
            }
            #pragma acc enter data copyin(a[0:n])
            #pragma acc host_data use_device(a)
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = a[x] + 1;
                }
            }
            #pragma acc exit data copyout(a[0:n])
            for (int x = 0; x < n; ++x){
                if (fabs(a[x] - 1) > PRECISION){
                    err = err + 1;
                    break;
                }
            }
            for (int x = 0; x < n; ++x){
                a[x] = 0;
            }
            #pragma acc enter data copyin(a[0:n])
            #pragma acc host_data if_present(a)
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = a[x] + 1;
                }
            }
            #pragma acc exit data delete(a[0:n])
            for (int x = 0; x < n; ++x){
                if (fabs(a[x] - 1) > PRECISION){
                    err = err + 1;
                    break;
                }
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