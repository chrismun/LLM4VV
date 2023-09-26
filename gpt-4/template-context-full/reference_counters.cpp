#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>
#include <math.h>

#ifndef T1
/*T1:reference counters,V:2.0-2.7*/
int test1() {
    int err = 0;
    srand(SEED);
   
    // Allocating memory
    int* data = (int*) malloc(100 * sizeof(int));

    // Filling random data
    for(int i = 0; i < 100; i++) {
        data[i] = rand();
    }

    // Transferring data into device memory
    #pragma acc enter data copyin(data[0:100])

    // Check if the data is present on the device.
    if(!acc_is_present(data, 100 * sizeof(int))) {
        printf("Error: Memory is not present on device\n");
        err = 1;
    }

    // Deleting data from device memory with acc_delete. As this is the only call
    // incrementing the dynamic reference counter for this memory section, it should result in
    // that this section is now no longer present on the device.
    acc_delete(data, 100 * sizeof(int));

    // Check if the data is not present on the device anymore.
    if(acc_is_present(data, 100 * sizeof(int))) {
        printf("Error: Memory is still present on device after acc_delete\n");
        err = 1;
    }

    free(data);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for(int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if(failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
  
    return failcode;
}