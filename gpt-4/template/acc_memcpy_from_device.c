#include "acc_testsuite.h"
#define SIZE 1000

#ifndef T1
int test1(){
    int err = 0;
    int *A_host = (int*) malloc(SIZE * sizeof(int));
    int *A_device = (int*) malloc(SIZE * sizeof(int));

    for (int i = 0; i < SIZE; i++) {
        A_host[i] = i+1;
    }
    
    // Copy from host to device
    #pragma acc enter data copyin(A_host[0:SIZE])
    
    // Copy A back to A_device
    #pragma acc exit data copyout(A_host[0:SIZE]) copyout(A_device[0:SIZE])
    
    // Check if device to host memory copy has worked
    for (int i = 0; i < SIZE; i++) {
        if (A_host[i] != A_device[i]) {
            err = 1;
            break;
        }
    }

    if (A_host) free(A_host);
    if (A_device) free(A_device);
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