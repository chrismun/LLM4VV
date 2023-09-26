#include "acc_testsuite.h"
#ifndef T1
// T1: acc unmap data, V: 2.7-3.3
int test1(){
    int err = 0;
    int length = 1024;
    int *data = (int*)malloc(length * sizeof(int));

    // Initialize data array
    for (int i = 0; i < length; ++i){
        data[i] = i;
    }

    // Map data array to GPU
    #pragma acc enter data copyin(data[0:length])

    // Perform some calculation on the GPU
    #pragma acc parallel loop present(data[0:length])
    for (int i = 0; i < length; ++i){
        data[i] = data[i] * 2;
    }

    // Unmap data array from GPU
    #pragma acc exit data delete(data)

    // Verify calculation on CPU
    for (int i = 0; i < length; ++i){
        if (data[i] != i * 2){
            err = 1;
            break;
        }
    }

    // Free memory
    free(data);

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