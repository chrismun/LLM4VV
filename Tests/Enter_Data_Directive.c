#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of integers
    int data[10];
    for (int i = 0; i < 10; i++){
        data[i] = rand();
    }

    // Create a host pointer to the array
    int *host_ptr = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++){
        host_ptr[i] = data[i];
    }

    // Create an OpenACC enter data directive
    #pragma acc enter data create(data)

    // Verify that the data is accessible from the host
    for (int i = 0; i < 10; i++){
        if (host_ptr[i] != data[i]){
            err = 1;
            break;
        }
    }

    // Clean up
    free(host_ptr);

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