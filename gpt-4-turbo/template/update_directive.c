#include "acc_testsuite.h"
#ifndef T1
//T1:update,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int* a = (int*)malloc(size * sizeof(int));
    int* host_copy = (int*)malloc(size * sizeof(int));

    // Initialize data and a host copy for validation
    for (int i = 0; i < size; ++i){
        a[i] = rand() % 100;
        host_copy[i] = a[i];
    }

    // Use OpenACC to offload the computation
    #pragma acc data copy(a[0:size])
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i){
            a[i] += 1; // Simple computation to modify the data
        }

        // Update the host with the modified data
        #pragma acc update host(a[0:size])
    }

    // Check if the update was successful
    for (int i = 0; i < size; ++i){
        if (a[i] != host_copy[i] + 1){
            err++;
        }
    }

    free(a);
    free(host_copy);
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