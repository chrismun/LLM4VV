#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1: data construct no_create clause, V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 1024;
    float *a = new float[size];
    
    // Initialize array
    for(int i = 0; i < size; i++) {
        a[i] = i;
    }

    // Explicitly allocate memory on the device and copy data
    float *a_device = (float *)acc_malloc(size * sizeof(float));
    acc_memcpy_to_device(a_device, a, size * sizeof(float));

    // Use the no_create clause
    #pragma acc data present(a_device[0:size]) no_create(a_device)
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i) {
            a_device[i] *= 2; // Modify the array
        }
    }

    // Copy the data back to the host to verify
    acc_memcpy_from_device(a, a_device, size * sizeof(float));

    // Verification
    for(int i = 0; i < size; i++) {
        if(a[i] != i * 2) { // Check modifications
            err++;
        }
    }

    // Cleanup
    delete[] a;
    acc_free(a_device);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x){ // Assuming NUM_TEST_CALLS is defined as 1 for simplicity
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    // Report overall test result
    if(failcode == 0) {
        std::cout << "Test passed successfully.\n";
    } else {
        std::cout << "Test failed with code: " << failcode << "\n";
    }
    
    return failcode;
}