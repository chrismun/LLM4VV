#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:data deviceptr clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_data = (int*)malloc(100 * sizeof(int));
    int *device_data = (int*)malloc(100 * sizeof(int));

    // Initialize host data
    for(int i = 0; i < 100; i++) {
        host_data[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(host_data[0:100]) copyout(device_data[0:100])
    {
        #pragma acc update device(device_data[0:100])
    }

    // Verify data
    for(int i = 0; i < 100; i++) {
        if(host_data[i] != device_data[i]) {
            err = 1;
            break;
        }
    }

    free(host_data);
    free(device_data);

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