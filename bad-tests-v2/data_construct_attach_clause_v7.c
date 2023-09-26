#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
int test1(){
    int err = 0;
    srand(SEED);
    int n = 100;
    float *arr = (float*) malloc(n * sizeof(float));

    // Fill the array with random floats
    for(int i = 0; i < n; i++) {
        arr[i] = (float)rand()/(float)(RAND_MAX);
    }

    // Enter data and create clause
    #pragma acc enter data create(arr[0:n])

    #pragma acc parallel loop attach(arr)
    for(int i = 0; i < n; i++) {
        if(arr[i] != (float)rand()/(float)(RAND_MAX)){
            err = 1;
        }
    }

    #pragma acc exit data delete(arr)

    // Free the memory
    free(arr);

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

    // Return the failure code
    return failcode;
}