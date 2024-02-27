#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
// T1: data, V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));

    // Initialize array with random data.
    for(int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
    }

    // Use OpenACC data construct to copy data to device and back.
    #pragma acc data copy(a[0:size])
    {
        // Increment each element on the device.
        #pragma acc parallel loop
        for(int i = 0; i < size; ++i) {
            a[i]++;
        }
    }

    // Verify the operation.
    for(int i = 0; i < size; ++i) {
        if (--a[i] % 100 >= 100) { // Subtract to undo increment and check.
            err++; // Error if the original value doesn't match.
        }
    }

    free(a);
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
    if (failcode == 0) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed.\n");
    }
    return failcode;
}