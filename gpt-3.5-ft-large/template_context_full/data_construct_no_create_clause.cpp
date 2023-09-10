#include "acc_testsuite.h"
#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    device_ptr = (int *)acc_malloc(n * sizeof(int));
    real_vec = (int *)malloc(n * sizeof(int));

    for (x = 0; x < n; ++x){
        device_ptr[x] = 1;
        real_vec[x] = 1;
    }

    #pragma acc data copy(real_vec[0:10]) delete(real_vec[5:5]) device_ptr[create(device_ptr[0:n])]
    {
        #pragma acc parallel present(real_vec[0:10], device_ptr[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < 5; ++x){
                real_vec[x] += device_ptr[x];
            }
        }
    }

    for (x = 0; x < n; ++x){
        if (x < 5 && device_ptr[x] > real_vec[x]){
            err += 1;
        }
        else if (x < 5 && device_ptr[x] <= real_vec[x]){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
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
#ifndef T2
#endif
    return failcode;
}