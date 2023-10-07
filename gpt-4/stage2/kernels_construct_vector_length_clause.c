#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:kernels construct vector_length clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    
    // testing size
    const int size = 10000;

    // generate random integer array in host memory
    int *a = (int*)malloc(size * sizeof(int));
    for(int i=0; i<size; i++) {
        a[i] = rand() % 100;
    }

    // expected result
    int expected_result = 0;
    for(int i=0; i<size; i++) {
        expected_result += a[i];
    }

    // execute the openACC kernels construct on the device with vector_length clause
    int result = 0;
    #pragma acc kernels copy(a[0:size]) vector_length(128)
    {
        for(int i=0; i<size; i++) {
            result += a[i];
        }
    }

    // compare expected result and result from device
    if (expected_result != result) {
        err = 1;
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
    return failcode;
}