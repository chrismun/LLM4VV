#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
#define T1

// T1:host_data construct if_present clause, V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 1024;
    int* anArray = (int*)malloc(size * sizeof(int));
    
    // Initialize array and ensure it's present on the device
    for (int i = 0; i < size; ++i){
        anArray[i] = 1; // Initial value
    }
    #pragma acc enter data copyin(anArray[0:size])

    // Use host_data construct with if_present
    #pragma acc host_data use_device(anArray) if_present
    {
        for (int i = 0; i < size; ++i){
            anArray[i] = 2; // Attempt to change value, should reflect on the device
        }
    }

    // Check results
    #pragma acc update host(anArray[0:size])
    for (int i = 0; i < size; ++i){
        if (anArray[i] != 2){
            err++;
        }
    }

    #pragma acc exit data delete(anArray[0:size])
    free(anArray);
    return err;
}

#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}