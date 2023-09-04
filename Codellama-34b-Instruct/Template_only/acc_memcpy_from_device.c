#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);

    // Initialize the data
    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Copy the data from device to host
    #pragma acc enter data copyin(a[0:10])
    #pragma acc enter data copyin(b[0:10])

    // Copy the data from host to device
    #pragma acc enter data copyout(a[0:10])
    #pragma acc enter data copyout(b[0:10])

    // Verify that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory
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