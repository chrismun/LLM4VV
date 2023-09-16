#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define SIZE 100
#define NUM_TEST_CALLS 10

// Test function
int test_copyout(){
    int err = 0;
    int data[SIZE];

    // Initialize data on host
    for(int i = 0; i < SIZE; i++){
        data[i] = i;
    }

    // Compute region where data is manipulated on device
    #pragma acc parallel copyout(data)
    {
        #pragma acc loop
        for(int i = 0; i < SIZE; i++){
            data[i] = i * 2;
        }
    }

    // Check if data has been copied back to host
    for(int i = 0; i < SIZE; i++){
        if(data[i] != i * 2) {
            err = 1;
            break;
        }
    }

    return err;
}

// Main function
int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_copyout();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    if(failcode == 0) {
        printf("OpenACC copyout test: Passed\n");
    } else {
        printf("OpenACC copyout test: Failed\n");
    }

    return failcode;
}