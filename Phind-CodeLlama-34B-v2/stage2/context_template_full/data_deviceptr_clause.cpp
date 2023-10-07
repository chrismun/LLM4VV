#include <iostream>
#include <cstdlib>
#include <cassert>
#include "acc_testsuite.h"

#ifndef T1
/*T1:data deviceptr clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int N = 100;
    int *host_array = new int[N];
    int *device_array;

    for (int i = 0; i < N; i++) {
        host_array[i] = rand() % 100;
    }

    #pragma acc enter data copyin(host_array[0:N])
    #pragma acc data deviceptr(device_array)
    {
        #pragma acc host_data use_device(device_array)
        {
            device_array = host_array;
        }

        #pragma acc parallel present(device_array[0:N])
        {
            for (int i = 0; i < N; i++) {
                device_array[i] *= 2;
            }
        }

        #pragma acc update host(host_array[0:N])
    }
    #pragma acc exit data delete(device_array)

    for (int i = 0; i < N; i++) {
        if (host_array[i] != (rand() % 100) * 2) {
            err = 1;
            break;
        }
    }

    delete[] host_array;

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