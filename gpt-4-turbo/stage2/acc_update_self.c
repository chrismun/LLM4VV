#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 42
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

//T1:acc update self,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 100;
    int *hostArray = (int*) malloc(size * sizeof(int));

    // Initialize host array
    for(int i = 0; i < size; i++){
        hostArray[i] = rand() % 100;
    }

    // Allocate and initialize device memory with hostArray's content
#pragma acc enter data copyin(hostArray[0:size])
    
    // Modify array on the device
#pragma acc parallel loop present(hostArray[0:size])
    for(int i = 0; i < size; i++){
        hostArray[i] += 1;
    }

    // Update host array from device
#pragma acc update self(hostArray[0:size])

    // Verify update
    bool update_is_correct = true;
#pragma acc parallel loop reduction(&:update_is_correct) present(hostArray[0:size])
    for(int i = 0; i < size; i++){
        if(hostArray[i] != rand() % 100 + 1){
            update_is_correct = false;
        }
    }
    if(!update_is_correct){
        err += 1;
    }

    // Cleanup
#pragma acc exit data delete(hostArray[0:size])
    free(hostArray);
    
    return err;
}

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
    if (failcode) {
        printf("Test failed!\n");
    } else {
        printf("Test passed!\n");
    }
    return failcode;
}