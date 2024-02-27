#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 5
#endif

//T1:wait directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *data_host;
    int *data_device;
    size_t num_elements = 1024;
    size_t i;

    data_host = (int*)malloc(num_elements*sizeof(int));
    data_device = (int*)acc_malloc(num_elements*sizeof(int));

    if (data_host == NULL || data_device == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize the host array with random data
    for (i = 0; i < num_elements; ++i) {
        data_host[i] = rand() % 100;
    }

    // Copy the data to the device and perform an operation
    // asynchronously using an async clause
    int async_handle = 1;
    #pragma acc data copy(data_device[0:num_elements])
    {
        #pragma acc parallel loop async(async_handle)
        for (i = 0; i < num_elements; ++i) {
            data_device[i] = data_host[i] * 2;
        }

        // Here's our focus: wait for the asynchronous operation to complete
        #pragma acc wait(async_handle)

        // Copy the data back to the host and verify
        #pragma acc update host(data_host[0:num_elements])
    }

    // Verification
    for (i = 0; i < num_elements; i++) {
        if (data_host[i] != data_device[i]) {
            err += 1; // We expect the doubled values
        }
    }

    acc_free(data_device);
    free(data_host);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }

    if (failcode != 0) {
        printf("Test failed with error code %d\n", failcode);
    } else {
        printf("All tests passed successfully.\n");
    }
    
    return failcode;
}