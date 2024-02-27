#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#ifndef T1
// T1: declare directive, V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 1024;
    int host_array[1]; // Array to copy a single element back from device for verification
    srand(42);

    #pragma acc declare create(host_array[0:size]) // Array declared with the create clause

    #pragma acc parallel loop copyout(host_array[0:1])
    for (int i = 0; i < size; ++i) {
        host_array[i] = i * 2; // Simple operation: double the index value
    }

    // Copying back the first element for verification
    if (host_array[0] != 0) { // Since host_array[0] should have been doubled (0 * 2 = 0)
        err += 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x){ // For simplicity, let's call the test once
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }
    return failcode;
}