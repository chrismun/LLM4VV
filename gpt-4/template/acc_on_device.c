#include "acc_testsuite.h"
#include <openacc.h>

// Define a simple test function
// Test if an array is present on the device after it is declared
int test_acc_is_present(){
    int err = 0;
    const int N = 10000;
    float arr[N];
    
    // Initialize array in host memory
    for(int i = 0; i < N; i++){
        arr[i] = (float)i;
    }
    
    // Check if array is present on device
    if( acc_is_present(arr, N*sizeof(float)) ){
        err = 1;
    }
    
    // Explicitly copy array to device
    #pragma acc enter data copyin(arr)
    
    // Now the array should be present on the device
    if( !acc_is_present(arr, N*sizeof(float)) ){
        err = 1;
    }

    // Remove array from the device
    #pragma acc exit data delete(arr)

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    // Call the test function number of times
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_is_present();
    }
    
    // If any of the test function calls failed, update the failcode
    if (failed != 0){
        failcode += (1 << 0);
    }
    
    return failcode;
}