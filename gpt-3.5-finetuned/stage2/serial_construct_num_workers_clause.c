#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct num_workers,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t test_array_1[100003];
    real_t test_array_2[100003];

    for (int x = 0; x < 100003; ++x){
        test_array_1[x] = 0;
    }

    #pragma acc data copy(test_array_1[0:100003], test_array_2[0:100003]) present(test_array_2[0:100003])
    {
        #pragma acc serial num_workers(16)
        {
            #pragma acc loop
            for (int x = 0; x < 100003; ++x){
                test_array_1[x] = test_array_2[x];
            }
        }
    }

    for (int x = 0; x < 100003; ++x){
        if (fabs(test_array_1[x] - test_array_2[x]) > PRECISION){
            err += 1;
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