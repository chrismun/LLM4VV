#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1:acc copyin,V:2.7-3.3
int test1() {
    int err = 0;
    srand(42); // Using a fixed seed for reproducibility

    const int size = 1024;
    int* hostArray = (int*)malloc(size * sizeof(int));
    int* deviceArrayCopy = NULL;
    int result = 0;

    // Initialize the array with some values
    for (int i = 0; i < size; ++i) {
        hostArray[i] = rand() % 100;
    }

    // Use acc_copyin to copy data to device
#pragma acc enter data copyin(hostArray[0:size])
    deviceArrayCopy = (int*)acc_copyin(hostArray, size * sizeof(int));

    // Perform a simple computation on the device
#pragma acc parallel loop reduction(+:result) present(hostArray)
    for (int i = 0; i < size; ++i) {
        result += hostArray[i];
    }

    // Validate the computation
    int hostSum = 0;
    for (int i = 0; i < size; ++i) {
        hostSum += hostArray[i];
    }

    if(result != hostSum) {
        printf("Validation failed: Device sum %d does not match host sum %d\n", result, hostSum);
        err = 1; // Error detected
    }

    // Cleanup
#pragma acc exit data delete(hostArray[0:size])
    free(hostArray);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x){ // This is a simple test, so just one call might be enough
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}