#include "acc_testsuite.h"

#ifndef T1
#define T1 1
int test1(){
    int err = 0;
    srand(SEED);

    int size = 100;
    int *host_array = (int*)malloc(size * sizeof(int));

    // Map host array to device array
    #pragma acc enter data create(host_array[:size])

    // Unmap device array
    #pragma acc exit data delete(host_array[:size])

    free(host_array);

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