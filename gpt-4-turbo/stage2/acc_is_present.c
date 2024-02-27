#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h> // Including OpenACC library

#ifndef T1
// T1:acc_is_present, V:2.7-3.3
int test1(){
    int err = 0;
    srand(42); // Not quite necessary for this test, but included for consistency
    
    int data_size = 10;
    double *data = (double*)malloc(data_size * sizeof(double)); // Allocate host memory

    // Ensuring data is present on the device
    #pragma acc enter data create(data[:data_size])

    // Test if data is present on the device using acc_is_present
    if(!acc_is_present(data, data_size * sizeof(double))){
        printf("Data is not accessible from the current device.\n");
        err = 1; // Set error if data not present
    } else {
        printf("Data is accessible from the current device.\n");
    }
    
    // Cleanup
    #pragma acc exit data delete(data[:data_size])
    free(data);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x){ // Since this is a deterministic test, no need for NUM_TEST_CALLS
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}