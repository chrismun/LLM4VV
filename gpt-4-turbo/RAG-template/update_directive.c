#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100
#define SEED 42
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;

    // Allocate and initialize an array on the host
    int *a = (int*) malloc(N * sizeof(int));
    for(int i = 0; i < N; ++i){
        a[i] = i;
    }

    // Copy data to the device and modify it
#pragma acc data copy(a[0:N])
    {
#pragma acc parallel loop
        for(int i = 0; i < N; ++i){
            a[i] += 1;
        }
        
        // Use update directive to copy modified data back to host
#pragma acc update host(a[0:N])
    }
    
    // Modify the array on the host
    for(int i = 0; i < N; ++i){
        a[i] += 1;
    }
    
    // Copy back the modified data from host to device
#pragma acc data copy(a[0:N])
    {
        // Use update directive to synchronize device memory with the latest host data
#pragma acc update device(a[0:N])
        
#pragma acc parallel loop
        for(int i = 0; i < N; ++i){
            // Verify if updates from host are reflected on device
            if(a[i] != i + 2){
                err += 1;
            }
        }
    }

    free(a);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
        printf("Test FAILED\n");
    } else {
        printf("All tests PASSED\n");
    }
    return failcode;
}