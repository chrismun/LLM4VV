#include "acc_testsuite.h"
#ifndef T1
//T1:variable implicit data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* arr = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }

    // Create a compute construct with a variable implicit data attribute
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        int* p = &arr[i];
        #pragma acc data implicit(p)
        {
            // Do some computation on the data
            *p += 1;
        }
    }

    // Check that the data has been updated correctly
    for (int i = 0; i < 10; i++) {
        if (arr[i] != i + 1) {
            err = 1;
            break;
        }
    }

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
    return failcode;
}