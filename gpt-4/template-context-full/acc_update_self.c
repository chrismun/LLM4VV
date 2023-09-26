#include "acc_testsuite.h"
#include <stdlib.h>

/* acc_update_self test, Version: 2.0-2.7 */
int test1(){
    int err = 0;
    srand(SEED);
    int *host_data, *device_data;
    size_t n=100; // Or choose any suitable value
    
    // Allocate memory for host and device data
    host_data = (int*) malloc(n*sizeof(int));
    device_data = (int*) malloc(n*sizeof(int));

    // Initialize host data
    for(size_t i=0; i<n; ++i) {
        host_data[i] = rand();
    }

    // Copy host_data to device_data on the device
    #pragma acc enter data copyin(host_data[0:n])
    #pragma acc parallel loop present(host_data)
    for(size_t i=0; i<n; ++i) {
        device_data[i] = host_data[i];
    }

    // Modify the host_data
    for(size_t i=0; i<n; ++i) {
        host_data[i] = rand();
    }

    // Call acc_update_self to copy data from device to the host
    acc_update_self(device_data, n*sizeof(int));
    
    // Check if the host_data is correctly updated
    for(size_t i=0; i<n; ++i) {
        if (host_data[i] != device_data[i]){
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(host_data)
    free(host_data);
    free(device_data);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}