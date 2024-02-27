#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 123
#define NUM_TEST_CALLS 10

// T1:attachment counter, V:2.7-3.3
int test1(){
    int err = 0;
    int *host_array;
    int *device_ptr;
    size_t array_size = 1024; // Size of the array
    host_array = (int*) malloc(array_size * sizeof(int));

    // Initialize host array
    for(size_t i = 0; i < array_size; ++i){
        host_array[i] = rand() % 100;
    }

    // Allocate memory on the device and attach host_array to the device pointer
#pragma acc enter data create(device_ptr[0:array_size])
#pragma acc enter data copyin(host_array[0:array_size])

    // First check: Ensure data is correctly copied to the device
#pragma acc parallel present(device_ptr[0:array_size])
    {
        for(size_t i = 0; i < array_size; ++i){
            if (device_ptr[i] != host_array[i]){
                err++;
            }
        }
    }

    // Trying to reattach the same array. As per OpenACC, this should not lead to any errors but increment the attachment counter
#pragma acc enter data copyin(host_array[0:array_size])

    // Detach the array once, the attachment counter should decrease but not lead to detachment due to the initial increment
#pragma acc exit data delete(device_ptr[0:array_size])

    // Test the array is still on the device by trying to use it
#pragma acc parallel present(device_ptr[0:array_size])
    {
        // If the data is still present, no error
        // This checks indirectly if the attachment counter logic works
    }

    // Finally, actually detach the data. This should detach the array completely.
#pragma acc exit data delete(device_ptr[0:array_size]) copyout(host_array[0:array_size])
    
    // Clean up
    free(host_array);

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    srand(SEED);
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}