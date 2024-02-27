#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
// T1:acc_free,V:2.7-3.3
int test1(){
    int err = 0;
    srand(42); // Use a fixed seed for reproducibility

    size_t num_bytes = sizeof(float) * 100; // Allocate space for 100 floats
    float* data_dev = (float*)acc_malloc(num_bytes); // Allocate memory on the device

    // Check if acc_malloc was successful
    if (data_dev == NULL) {
        printf("acc_malloc failed to allocate device memory.\n");
        return ++err;
    }

    // Ideally, put some data and process it here to further validate, but for this test, we focus on acc_free

    acc_free(data_dev); // Free the allocated memory

    // Unfortunately, acc_free does not return a value that allows us to directly check for success.
    // However, attempting to access or free the memory again might indicate failure if the implementation is incorrect.

    // This test checks if acc_free works by seeing if the program can run to completion without runtime errors.
    // In a more robust testing framework, you might check device memory usage before and after to confirm freeing.

    return err; // err is 0 if everything went as expected
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x){ // Reduced iterations as memory allocation/free might not need repetitions for this simple test
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    if (failcode == 0) {
        printf("Test PASSED\n");
    } else {
        printf("Test FAILED\n");
    }

    return failcode;
}