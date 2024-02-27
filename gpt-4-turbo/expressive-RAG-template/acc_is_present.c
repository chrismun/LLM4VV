#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc is present,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    // Allocated data
    int *data = (int *)malloc(sizeof(int));
    if (!data) {
        perror("Failed to allocate memory");
        exit(1);
    }
    *data = rand(); // Initialize with a random value

    // Move data to the device
    #pragma acc enter data copyin(data[0:1])

    // Check if data is present on the device
    if (!acc_is_present(data, sizeof(int))) {
        fprintf(stderr, "Data is not present on the device as expected.\n");
        err = 1; // Indicate test failure
    }

    // Freeing resources
    #pragma acc exit data delete(data[0:1])
    free(data);
    
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
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}