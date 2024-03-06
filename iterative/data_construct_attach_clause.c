#include "acc_testsuite.h"

#ifndef T1
//T1:data construct attach clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *arr = (int*)malloc(10 * sizeof(int));
    int *dev_arr;

    #pragma acc data create(arr[0:10])
    {
        dev_arr = arr;
        #pragma acc attach(dev_arr)
        {
            // Check if array is attached
            if (acc_is_present(arr, sizeof(int) * 10) == 0) {
                err = 1;
            }
        }
        // Check if array is detached
        if (acc_is_present(arr, sizeof(int) * 10) != 0) {
            err = 1;
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