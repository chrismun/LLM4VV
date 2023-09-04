#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set the default async mode to true
    acc_set_default_async(true);

    // Create a data region with a random size
    int size = rand() % 1000;
    int* data = (int*)malloc(size * sizeof(int));

    // Initialize the data region with random values
    for (int i = 0; i < size; i++) {
        data[i] = rand();
    }

    // Create a copy of the data region
    int* data_copy = (int*)malloc(size * sizeof(int));
    memcpy(data_copy, data, size * sizeof(int));

    // Set the default async mode to false
    acc_set_default_async(false);

    // Create a new data region with the same size as the original data region
    int* new_data = (int*)malloc(size * sizeof(int));

    // Copy the data from the original data region to the new data region
    memcpy(new_data, data, size * sizeof(int));

    // Check if the data in the new data region is the same as the original data region
    for (int i = 0; i < size; i++) {
        if (new_data[i] != data_copy[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory allocated for the data regions
    free(data);
    free(data_copy);
    free(new_data);

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