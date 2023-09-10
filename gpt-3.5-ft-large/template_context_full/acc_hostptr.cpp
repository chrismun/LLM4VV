#include "acc_testsuite.h"
#ifndef T1
//T1:acc hostptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(acc_get_device_type() == acc_device_none){
        real_t *a = (real_t *)malloc(n * sizeof(real_t));
        real_t *a_copy = (real_t *)malloc(n * sizeof(real_t));
        int deviceon = 0;

        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            a_copy[x] = a[x];
        }

        #pragma acc enter data copyin(a[0:n])
        for (int x = 0; x < n; ++x){
            acc_hostptr((void *)&a[x]) = acc_deviceptr((void *)&a[x]);
        }
        #pragma acc parallel present(a[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                *((real_t *) acc_hostptr((void *)&a[x]))) = *((real_t *) acc_hostptr((void *)&a[x]))) + 1;
            }
        }
        #pragma acc exit data copyout(a[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - (a_copy[x] + 1)) > PRECISION){
                err += 1;
            }
        }

        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
        }

        for (int x = 0; x < n; ++x){
            a_copy[x] = a[x];
        }

        #pragma acc enter data copyin(a[0:n])
        for (int x = 0; x < n; ++x){
            acc_hostptr((void *)&a[x]) = acc_deviceptr((void *)&a[x]);
        }
        #pragma acc parallel present(a[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                *((real_t *) acc_hostptr((void *)&a[x]))) = *((real_t *) acc_hostptr((void *)&a[x]))) + 1;
            }
        }
        #pragma acc exit data copyout(a[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - (a_copy[x] + 1)) > PRECISION){
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