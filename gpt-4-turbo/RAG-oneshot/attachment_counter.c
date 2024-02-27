#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef ATTACH_COUNTER_TEST
// ATTACH_COUNTER_TEST:kernel,data,data-region,V:1.0-2.7
int test_attachment_counter() {
    int err = 0;
    real_t* hostArray = (real_t*)malloc(n * sizeof(real_t));
    real_t* deviceArray;
    real_t scalar = 5.0;

    for (int x = 0; x < n; ++x) {
        hostArray[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    
    #pragma acc enter data copyin(hostArray[0:n])
    deviceArray = hostArray;

    // Perform multiple attach operations
    for (int attach = 0; attach < 3; ++attach) {
        #pragma acc update device(deviceArray[0:n]) 
    }
    
    // Perform computation to check if data is indeed on device
    #pragma acc parallel loop present(deviceArray[0:n])
    for (int x = 0; x < n; ++x) {
        deviceArray[x] = deviceArray[x] * scalar;
    }
    
    // Detach operations
    for (int detach = 0; detach < 3; ++detach) {
        #pragma acc exit data delete(deviceArray[0:n])
    }

    // Bringing data back to check results
    #pragma acc update host(hostArray[0:n])

    for (int x = 0; x < n; ++x) {
        if (fabs(hostArray[x] - (rand() / (real_t)(RAND_MAX / 10)) * scalar) > PRECISION) {
            err += 1;
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

    failed = test_attachment_counter();
    if (failed != 0) {
        failcode = 1;
    }
    
    if(failcode == 0){
        printf("PASSED: Attachment counter behavior matches OpenACC specification.\n");
    } else {
        printf("FAILED: Discrepancies found in attachment counter behavior.\n");
    }

    return failcode;
}