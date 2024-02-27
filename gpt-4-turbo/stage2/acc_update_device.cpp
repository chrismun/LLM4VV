#include <openacc.h>
#include <iostream>
#include <stdlib.h>

// For simplicity, assume SEED and NUM_TEST_CALLS are defined. Typically, these would be passed through compilation flags or defined elsewhere.
#define SEED 123
#define NUM_TEST_CALLS 10

int test_acc_update_device(){
    int err = 0;
    srand(SEED);

    // 1. Initialize some data on the host.
    constexpr int size = 1024;
    int* host_array = new int[size];
    for(int i = 0; i < size; i++) {
        host_array[i] = rand();
    }

    // 2. Copy this data to the device, making it present in the device memory.
    #pragma acc enter data copyin(host_array[0:size])

    // 3. Modify the original data on the host.
    for(int i = 0; i < size; i++) {
        host_array[i] *= 2;
    }

    // 4. Use `acc_update_device` to update the device's copy of the data.
    acc_update_device(host_array, size * sizeof(int));

    // Prepare a different array to fetch the updated data from device
    int* new_host_array = new int[size];

    // 5. Copy the updated data back from the device to a different host array.
    #pragma acc exit data copyout(new_host_array[0:size])

    // 6. Compare the modified host array with the one fetched back from the device to ensure the update was performed correctly.
    for(int i = 0; i < size; i++) {
        if(new_host_array[i] != host_array[i]){
            err++;
            break;
        }
    }

    // Clean up
    delete[] host_array;
    delete[] new_host_array;
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_update_device();
    }
    if (failed != 0){
        failcode = (1 << 0);
    }

    return failcode;
}