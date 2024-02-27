#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
// T1:data present clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *data;
    int data_size = 1024;
    srand(SEED);

    // Allocate memory 
    data = (int*)malloc(data_size * sizeof(int));

    // Initialize data
    for(int i = 0; i < data_size; ++i) {
        data[i] = rand() % 100;
    }

    // Create initial data region on the device
    #pragma acc enter data copyin(data[0:data_size])

    // Attempt to use the present clause to ensure data is already on device
    #pragma acc parallel present(data[0:data_size])
    {
        // Dummy operation to verify presence
        for(int i = 0; i < data_size; ++i) {
            data[i] += 1;
        }
    }

    // Attempt to use data in a new region without re-specifying it should fail if not present
    #pragma acc parallel present(data[0:data_size])
    {
        // Further dummy operation to catch potential error if data is not present
        for(int i = 0; i < data_size; ++i) {
            data[i] -= 1;
        }
    }

    // Cleanup: Exit data region 
    #pragma acc exit data delete(data[0:data_size])

    free(data);

    // If no errors occurred up to this point, err remains 0 indicating success
    return err;
}
#endif

// Define necessary constants if not in acc_testsuite.h
#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}