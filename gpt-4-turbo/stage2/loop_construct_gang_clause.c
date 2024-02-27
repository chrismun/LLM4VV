#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

//T1:loop construct gang clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1000;
    int* data = (int*)malloc(size * sizeof(int));
    bool* checker = (bool*)malloc(size * sizeof(bool));
    for(int i = 0; i < size; ++i){
        data[i] = -1; // Initialize all elements to -1
        checker[i] = false; // No iteration has been processed
    }

    #pragma acc parallel num_gangs(10) copy(data[0:size])
    {
        #pragma acc loop gang
        for(int i = 0; i < size; ++i){
            data[i] = acc_gang_id(1); // Assign gang id to data
        }
    }

    // Check if data has been distributed across gangs correctly
    for(int i = 0; i < size; ++i){
        if(data[i] >= 0 && data[i] < 10){
            // If gang id is within expected range, mark it as processed
            checker[data[i]] = true;
        } else {
            // Found an unexpected gang id
            err += 1;
        }
    }

    // Check if each gang processed at least some iterations
    for(int i = 0; i < 10; ++i){
        if(!checker[i]){
            // This gang did not process any iteration
            err += 1;
        }
    }

    free(data);
    free(checker);

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}