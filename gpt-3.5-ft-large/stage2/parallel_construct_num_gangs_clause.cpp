#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() == acc_device_nvidia){
        #pragma acc parallel num_gangs(1024)
        {
            atomicAdd(&nvidia_num_gangs_test1[0], 1);
        }
        if (nvidia_num_gangs_test1[0] - 1024 > PRECISION)
            err += 1;

        #pragma acc parallel num_gangs(16, 16, 4)
        {
            atomicAdd(&nvidia_num_gangs_test2[0], 1);
        }
        if (nvidia_num_gangs_test2[0] - 16 > PRECISION)
            err += 1;
        if (nvidia_num_gangs_test2[1] - 16 > PRECISION)
            err += 1;
        if (nvidia_num_gangs_test2[2] - 4 > PRECISION)
            err += 1;

    }
    else if (acc_get_device_type() == acc_device_radeon){
        #pragma acc parallel num_gangs(1024)
        {
            atomic_add(&nvidia_num_gangs_test1[0], 1);
        }
        if (radeon_num_gangs_test1[0] - 1024 > PRECISION)
            err += 1;

        #pragma acc parallel num_gangs(16, 16, 4)
        {
            atomic_add(&nvidia_num_gangs_test2[0], 1);
        }
        if (radeon_num_gangs_test2[0] - 16 > PRECISION)
            err += 1;
        if (radeon_num_gangs_test2[1] - 16 > PRECISION)
            err += 1;
        if (radeon_num_gangs_test2[2] - 4 > PRECISION)
            err += 1;
    }

    return err;
}
#endif

using namespace std;
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