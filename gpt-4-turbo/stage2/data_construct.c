#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10
#define ARRAY_SIZE 100

#ifndef T1
//T1:data construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int host_array[ARRAY_SIZE];

    // Initialize array
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        host_array[i] = i;
    }

    // Data construct with copy clause
    #pragma acc data copy(host_array)
    {
        #pragma acc parallel loop
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            host_array[i] += 1; // Modify the array on device
        }
    }

    // Check modifications; if not reflected back on host, then error
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (host_array[i] != i + 1) {
            err += 1;
            break; // Fail at first error
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