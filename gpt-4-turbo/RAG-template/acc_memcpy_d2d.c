#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <string.h> // For memset & memcmp

// Adjust the following constants as per your testing environment
#define SEED 12345
#define NUM_TEST_CALLS 10

int test_acc_memcpy_d2d(){
    int err = 0;
    const size_t bytes = 1024; // Size of the data array in bytes
    srand(SEED);

    // Allocate memory on host for testing purposes
    int *host_array_src = (int*)malloc(bytes);
    int *host_array_dest = (int*)malloc(bytes);
    
    // Initialize source array
    for (size_t i = 0; i < bytes/sizeof(int); ++i){
        host_array_src[i] = rand();
    }
    // Initialize destination array to zeros
    memset(host_array_dest, 0, bytes);

    // Assuming at least two devices of the same type are available.
    int num_devices = acc_get_num_devices(acc_get_device_type());
    if (num_devices < 2) {
        printf("Not enough devices for test, ensure at least two devices are available.\n");
        free(host_array_src);
        free(host_array_dest);
        return 1;
    }

    int dev_num_src = 0; // Assuming first device as source
    int dev_num_dest = 1; // Assuming second device as destination, change as needed

    // Ensure we have valid device numbers, else adjust them based on the actual environment.
    if (num_devices <= dev_num_dest) {
        dev_num_dest = num_devices - 1;
    }

    // Initialize device and allocate memory
    acc_set_device_num(dev_num_src, acc_get_device_type());
    int *device_array_src = (int*)acc_malloc(bytes);

    acc_set_device_num(dev_num_dest, acc_get_device_type());
    int*device_array_dest = (int*)acc_malloc(bytes);
    
    // Copy host data to source device
    acc_memcpy_to_device(device_array_src, host_array_src, bytes);

    // Perform device to device copy
    acc_memcpy_d2d(device_array_dest, device_array_src, bytes, dev_num_dest, dev_num_src);

    // Copy data back to host from destination device to verify
    acc_memcpy_from_device(host_array_dest, device_array_dest, bytes);

    // Verify data
    if (memcmp(host_array_src, host_array_dest, bytes) != 0) {
        printf("Data mismatch detected. `acc_memcpy_d2d` implementation may be incorrect.\n");
        err = 1;
    }

    acc_free(device_array_src);
    acc_free(device_array_dest);
    free(host_array_src);
    free(host_array_dest);

    return err;
}

int main(){
    int failcode = 0;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        if (test_acc_memcpy_d2d() != 0){
            failcode = 1; // Indicate a failure
            break;
        }
    }
    
    if (failcode == 0) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed.\n");
    }

    return failcode;
}