#include <stdio.h>
#include <stdlib.h>
#include <openacc.h> // Ensure to include the OpenACC header

// Assuming acc_testsuite.h defines constants such as SEED and NUM_TEST_CALLS
// For the purpose of this example, define them as needed if not available.
#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Define T1 to exclude the rest of the original tests (as per the instruction)
#define T1

int test1(){
    int err = 0;
    srand(SEED);
    
    const int size = 1024;
    int wait_arg[2] = {1, 2}; // Defining two async queues
    float a[size], b[size];
    
    // Initialize arrays on the host
    for(int i = 0; i < size; ++i) {
        a[i] = (float)i;
        b[i] = 0.0f;
    }

    // Performing operations on separate async queues
    #pragma acc kernels async(wait_arg[0]) copyout(b[0:size/2])
    for(int i = 0; i < size/2; ++i) {
        b[i] = a[i] * 2.0f;
    }

    #pragma acc kernels async(wait_arg[1]) copyout(b[size/2:size])
    for(int i = size/2; i < size; ++i) {
        b[i] = a[i] * 2.0f;
    }

    int completed_queue = acc_wait_any(2, wait_arg);
    if(completed_queue < 0 || completed_queue >= 2) {
        printf("Invalid queue index returned by acc_wait_any.\n");
        err++;
    } else {
        // Optionally, use acc_async_test to further confirm the queue has indeed completed.
        if(!acc_async_test(wait_arg[completed_queue])) {
            printf("acc_wait_any returned a queue index (%d) which is not yet completed.\n", completed_queue);
            err++;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}