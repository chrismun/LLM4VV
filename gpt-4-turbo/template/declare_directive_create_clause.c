#include "acc_testsuite.h"
#ifndef T1
//T1:declare,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int n = 10;
    int a[n];
    
    // Initialize array 'a' with random values on the host
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % 100;
    }
  
    // Declare the array 'a' for creation on the device. It should not be initialized.
    #pragma acc enter data create(a[0:n]) 
  
    // Dummy kernel to check if 'a' is properly allocated on the device without initialization
    #pragma acc parallel loop present(a[0:n])
    for (int i = 0; i < n; ++i) {
        a[i] = a[i] + 0; // No actual change, just a dummy operation to prevent compiler optimizations
    }

    // Copy the array back to the host to check its values
    #pragma acc exit data copyout(a[0:n])

    // Verify that the values in 'a' are not initialized
    for (int i = 0; i < n; ++i) {
        if (a[i] != 0) { // Assuming uninitialized memory will not hold the original values
            err++;
        }
    }

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