#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:acc_update_device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    // Create array in local memory
    size_t arraySize = 10;
    int *localArray = (int*) malloc(arraySize * sizeof(int));

    // Initialize array with random values
    for(int i = 0; i < arraySize; ++i) {
        localArray[i] = rand();
    }

    // Transfer array to device with copyin directive
    #pragma acc enter data copyin(localArray[0:arraySize])

    // Update one value in local array
    localArray[0] = rand();

    // Call acc_update_device to update value from local to device memory
    acc_update_device(localArray, arraySize * sizeof(int));

    // Test that values are updated in device memory
    int *deviceArray = NULL;
    #pragma acc parallel loop present(localArray[0:arraySize]) private(deviceArray)
    for(int i = 0; i < arraySize; ++i) {
        deviceArray[i] = localArray[i];
    }

    // Return an error if values do not match
    if(deviceArray[0] != localArray[0]) {
        err = 1;
    }

    // Free allocated memory
    #pragma acc exit data delete(localArray[0:arraySize])
    free(localArray);

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