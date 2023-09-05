#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* data = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Create an OpenACC region with the exit data directive
    #pragma acc enter data copyin(data[0:10])
    #pragma acc exit data delete(data[0:10])

    // Check that the data has been deleted
    for (int i = 0; i < 10; i++) {
        if (data[i] != 0) {
            err = 1;
            break;
        }
    }

    // Free the memory
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