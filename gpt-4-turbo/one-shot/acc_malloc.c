#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:runtime, data, data-region, V:1.0-2.7
int test1(){
    int err = 0;
    real_t *a_device;
    real_t *a_host;
    int n = 1024;
    srand(SEED);

    a_host = (real_t *)malloc(n * sizeof(real_t));
    for (int i = 0; i < n; i++) {
        a_host[i] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data create(a_device[0:n])
    a_device = (real_t *)acc_malloc(n * sizeof(real_t));

    if (a_device == NULL) {
        printf("acc_malloc failed to allocate memory on the device.\n");
        err++;
    } else {
        // Copy data to the device
        #pragma acc update device(a_device[0:n]) 
        for(int i = 0; i < n; i++) {
            if (fabs(a_device[i] - a_host[i]) > PRECISION) {
                err++;
            }
        }

        // Free the allocated memory
        acc_free(a_device);
        #pragma acc exit data delete(a_device[0:n])
    }
    
    free(a_host);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;

#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }

    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    if (failcode) {
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }

    return failcode;
}