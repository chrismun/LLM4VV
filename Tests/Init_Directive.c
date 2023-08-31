#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize an array with random values
    int arr[10];
    for (int i = 0; i < 10; i++){
        arr[i] = rand();
    }

    // Use the init directive to initialize a variable with the array
    int x;
    #pragma acc init(x, arr)

    // Check that the variable has been initialized correctly
    if (x != arr[0]){
        err = 1;
    }

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