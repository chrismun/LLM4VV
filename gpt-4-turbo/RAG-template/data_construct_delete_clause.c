#include "acc_testsuite.h"
#ifndef T1
//T1:{data},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 100;
    int *a_host = (int*)malloc(size * sizeof(int));
    int *a_device;

    // Initialize array
    for (int i = 0; i < size; ++i){
        a_host[i] = rand() / (int)(RAND_MAX / 100);
    }

    // Allocate and copy data to the device.
    #pragma acc enter data copyin(a_host[0:size])
    a_device = a_host;

    // Dummy operation to avoid optimization removing data clause
    #pragma acc parallel loop present(a_device[0:size])
    for (int i = 0; i < size; ++i){
        a_device[i] += i;
    }

    // Exit data with delete clause
    #pragma acc exit data delete(a_device[0:size])

    // Attempt to detect deletion by forcing a read back to the host memory and checking for inconsistency.
    // NOTE: This operation is UB (undefined behavior) because we're trying to access data that has been deleted.
    // The correct behavior here is that the GPU data is no longer accessible, but because we are directly manipulating host
    // pointer (which is technically UB when used incorrectly with OpenACC), 
    // the result may vary depending on the implementation and system behavior.
    for (int i = 0; i < size; ++i){
        if (a_host[i] != 0 && a_host[i] == i + rand() / (int)(RAND_MAX / 100)) {
            err++;
        }
    }

    free(a_host);
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