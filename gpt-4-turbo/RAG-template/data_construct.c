#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef T1
//T1:data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int size = 1024;
    int *host_array = (int *) malloc(size * sizeof(int));
    int *initial_data = (int *) malloc(size * sizeof(int));
    
    // Initialize array with random data
    for (int i = 0; i < size; ++i){
        initial_data[i] = rand() % 100;
        host_array[i] = initial_data[i];
    }

    // Offload data and computation to device
    #pragma acc data copy(host_array[0:size])
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i) {
            host_array[i] += 1; // Increment each element by 1
        }
    }

    // Check for errors in modified data
    for (int i = 0; i < size; ++i){
        if (host_array[i] != initial_data[i] + 1){
            err++;
            printf("Mismatch at %d, expected %d, got %d\n", i, initial_data[i] + 1, host_array[i]);
        }
    }
    
    free(host_array);
    free(initial_data);

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