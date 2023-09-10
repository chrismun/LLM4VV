#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>
#include <assert.h>

#ifndef T1
/*T1:acc_unmap_data,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate array storage on both host and device
    float *host_array = (float*) malloc(N * sizeof(float));
    assert(host_array != NULL);
    
    float *device_array = (float*) acc_malloc(N * sizeof(float));
    assert(device_array != NULL);

    // Filling in host array
    for (int i = 0; i < N; i++) {
    	host_array[i] = rand() / (float)RAND_MAX;
    }

    // Map host data to device data
    acc_map_data(host_array, device_array, N * sizeof(float));

    // Unmap the data
    acc_unmap_data(host_array);

    // We'll try mapping again. If unmap was successful, this should work.
    // If not, acc_map_data should return an error, which we'll catch and use to set err.
    acc_map_data(host_array, device_array, N * sizeof(float));

    // Clean up
    free(host_array);
    acc_free(device_array);

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