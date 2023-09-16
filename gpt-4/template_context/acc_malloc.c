#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
//T1:acc malloc,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int N = 10000;
    float *device_array;
    
    // Allocate memory on the device
    device_array = (float*)acc_malloc(N * sizeof(float));

    #pragma acc parallel loop present(device_array[0:N])
    for(int i = 0; i < N; i++) {
        device_array[i] = (float)i;
    }

    float *host_array = (float*)malloc(N * sizeof(float));

    #pragma acc update host(host_array[0:N]) from(device_array[0:N])

    for(int i = 0; i < N; i++) {
        if(host_array[i] != (float)i) {
            err = 1;
            break;
        }
    }

    acc_free(device_array);
    free(host_array);

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