#include <stdio.h>
#include <stdlib.h>

// Assuming definitions for a simplified testing environment
#define SEED 123
#define NUM_TEST_CALLS 1

#ifndef T1
// T1:update directive, V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 10;
    int *a = (int*) malloc(size * sizeof(int));
    int *b = (int*) malloc(size * sizeof(int));

    // Initialize a and b on host
    for (int i = 0; i < size; ++i) {
        a[i] = i;
        b[i] = -1; // Use -1 to verify the update
    }

    #pragma acc data copyout(a[0:size]) // Copying 'a' out to device to modify it there
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i) {
            a[i] += 10; // Modify the device copy
        }

        // Update the host array 'a' with device modifications
        #pragma acc update host(a[0:size])
    }

    // Verify the update back to host
    for (int i = 0; i < size; ++i) {
        if (a[i] != i + 10) {
            err++;
            break;
        }
    }

    // Modify the host array and update the device copy
    for (int i = 0; i < size; ++i) {
        b[i] = i + 20;
    }
    
    #pragma acc data copyin(b[0:size])
    {
        // Before update
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i) {
            b[i] -= 1; // Perform a dummy operation
        }

        // Update the device copy with new values of 'b'
        #pragma acc update device(b[0:size])
        
        #pragma acc parallel loop
        for(int i = 0; i < size; ++i){
            if(b[i] != i + 20) //Check if the device array 'b' was correctly updated from host
                err++;
        }
    }

    free(a);
    free(b);

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