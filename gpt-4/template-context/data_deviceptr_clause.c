#include "acc_testsuite.h"
#include<stdlib.h>

#ifndef T1
//T1:data deviceptr clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Declaring and initializing a pointer in the host
    int* h_ptr = (int*) malloc(100 * sizeof(int));

    // Initializing the pointer with data
    for (int i = 0; i < 100; i++) {
        h_ptr[i] = i;
    }

    // Declaring a pointer that will act as a device pointer
    int* d_ptr;

    // Allocating memory in the device and updating 'd_ptr' 
    // to point to the allocated memmory
    #pragma acc enter data create(d_ptr[0:100])
    #pragma acc update device(d_ptr[0:100])

    d_ptr = h_ptr;

    // Using 'deviceptr' clause to specify that 'd_ptr' is a device pointer
    #pragma acc enter data deviceptr(d_ptr)

    // Checking if the operation was successful
    #pragma acc parallel loop deviceptr(d_ptr)
    for (int i = 0; i < 100; i++) {
        if(d_ptr[i] != i) {
            err = 1;
            break;
        }
    }

    // Freeing memory on the device
    #pragma acc exit data delete(d_ptr)

    // Freeing memory on the host
    free(h_ptr);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}