#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int sum = 0;
    int arr[10];

    // Implicitly determined data attributes
    #pragma acc parallel loop reduction(+:sum)
    for(int i=0; i<10; i++){
        sum += arr[i];
    }

    // Check if the data attributes are correctly determined
    // sum should be private to the parallel loop construct
    // arr should be copied to the GPU

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