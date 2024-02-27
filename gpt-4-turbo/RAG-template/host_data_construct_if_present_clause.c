#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef T1
// T1:{host_data},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize two separate arrays
    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; ++i){
        a[i] = rand() / (RAND_MAX / 100);
        b[i] = rand() / (RAND_MAX / 100);
    }

    // Only copy "a" to the device to ensure it's present
    #pragma acc enter data copyin(a[0:10])

    // Use acc host_data with if_present clause
    #pragma acc host_data use_device(a, b) if_present
    {
        // Assuming an external device API that requires pointers to device memory
        // Here, we simulate device operation by modifying the values in "a" and attempting the same with "b"
        for (int i = 0; i < 10; ++i){
            a[i] *= 2; // This operation should succeed as "a" is present on the device
            if (acc_is_present(b, 10 * sizeof(int))) {
                b[i] *= 2; // This operation should not occur, as "b" isn't present
            }
        }
    }
    
    #pragma acc exit data copyout(a[0:10])
    
    // Validate results
    for (int i = 0; i < 10; i++) {
        if (a[i] != 2 * (a[i] / 2)) {
            err++;
            break;
        }
        if (b[i] == 2 * (b[i] / 2)) {
            // If "b" has been modified, that's an error, as it shouldn't be present on the device.
            err++;
            break;
        }
    }

    free(a);
    free(b);

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