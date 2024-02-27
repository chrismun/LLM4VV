#include "acc_testsuite.h"
#ifndef T1
//T1:{data.constructs,data.copy},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a_host = (int *)malloc(size * sizeof(int));
    int *a_host_copy = (int *)malloc(size * sizeof(int));

    // Initialize the array with random values and prepare a copy for verification
    for(int i = 0; i < size; ++i){
        a_host[i] = rand() % 100;
        a_host_copy[i] = a_host[i];
    }

    // Utilizing OpenACC to perform computations on the array with the copy clause
    #pragma acc parallel loop copy(a_host[0:size])
    for(int i = 0; i < size; ++i){
        a_host[i] += 5; // Simple computation to verify the data was copied and modified on the device
    }

    // Verify the computation result
    for(int i = 0; i < size; ++i){
        if (a_host_copy[i] + 5 != a_host[i]){
            err += 1; // Increment error if the computation does not match
        }
    }

    free(a_host);
    free(a_host_copy);
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