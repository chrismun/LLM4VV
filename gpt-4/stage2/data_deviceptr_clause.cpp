#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef TEST1
/*TEST1:data deviceptr clause,V:2.0-2.7*/
int test1(){
    int err = 0; // No errors yet
    srand(SEED);

    // Creating host and device data arrays
    int* host_data = (int*) malloc(1024 * sizeof(int));
    int* device_data = (int*) acc_malloc(1024 * sizeof(int));

    // Initializing the data
    for (int i = 0; i < 1024; ++i) {
        host_data[i] = rand()%10;
    }

    // Copying data from host to device
    acc_memcpy_to_device(device_data, host_data, 1024 * sizeof(int));

    // OpenACC parallel region
    #pragma acc data deviceptr(device_data)
    {
        #pragma acc parallel loop
        for(int i=0; i<1024; i++) {
            device_data[i] = device_data[i] + 1;
        }
    }
   
   // Copying data from device to host
   acc_memcpy_from_device(host_data, device_data, 1024 * sizeof(int));

   // Checking the results and setting error if occurs
   for (int i = 0; i < 1024; i++) {
        if (host_data[i] != (rand()%10 + 1)) {
            err = 1; // Error happened
            break;
        }
    }

    // Free the host and device memory
    free(host_data);
    acc_free(device_data);
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