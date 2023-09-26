#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set the default async mode to true
    acc_set_default_async(true);

    // Create a data array
    int data[10];

    // Initialize the data array with random values
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Create a host array
    int host[10];

    // Copy the data array to the host array
    acc_copy(host, data, 10);

    // Check if the data array is equal to the host array
    for (int i = 0; i < 10; i++) {
        if (data[i] != host[i]) {
            err = 1;
            break;
        }
    }

    // Set the default async mode to false
    acc_set_default_async(false);

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