#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:acc map data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(42); // Using a fixed seed for reproducibility

    // Define the size of the array
    size_t n = 1024;
    size_t bytes = n * sizeof(int);

    // Allocate host memory
    int* host_array = (int*)malloc(bytes);
    if (host_array == NULL) {
        fprintf(stderr, "Failed to allocate host memory.\n");
        return 1;
    }

    // Initialize host memory
    for(size_t i = 0; i < n; i++) {
        host_array[i] = rand() % 100; // Random numbers between 0 and 99
    }

    // Allocate device memory
    int* device_array = (int*)acc_malloc(bytes);
    if (device_array == NULL) {
        free(host_array);
        fprintf(stderr, "Failed to allocate device memory.\n");
        return 1;
    }

    // Map the host memory to the device memory
    acc_map_data(host_array, device_array, bytes);

    // Use OpenACC directives to modify the data on the device
    #pragma acc parallel loop present(host_array[0:n])
    for (size_t i = 0; i < n; i++) {
        host_array[i] += 1; // Increment each element by 1
    }

    // Copy data back to the host to check correctness
    acc_memcpy_from_device(host_array, device_array, bytes);

    // Check the results
    for (size_t i = 0; i < n; i++) {
        if (host_array[i] != ((rand() % 100) + 1)) {
            err++;
        }
    }

    // Cleanup
    acc_unmap_data(host_array);
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
    for (int x = 0; x < 1; ++x){ // Assuming NUM_TEST_CALLS can be simplified for this example
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}