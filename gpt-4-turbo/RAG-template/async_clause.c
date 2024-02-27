#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
// T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int array_size = 1000;
    float a[array_size];
    float b[array_size];

    // Initialize arrays
    for(int i = 0; i < array_size; i++){
        a[i] = rand() / (float)RAND_MAX;
        b[i] = 0.0f;
    }

    // Perform parallel operation asynchronously
    #pragma acc parallel loop copyin(a[0:array_size]) copyout(b[0:array_size]) async(1)
    for(int i = 0; i < array_size; i++){
        b[i] = a[i] * 2.0f;
    }

    // Wait for the completion of the asynchronous operations
    #pragma acc wait(1)

    // Verify the result
    for(int i = 0; i < array_size; i++){
        if(b[i] != a[i] * 2.0f){
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
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}