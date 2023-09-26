#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct detach clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    int arr[1000], res = 0;
    srand(SEED);

    #pragma acc enter data create(arr[:1000])
    #pragma acc parallel loop present(arr[:1000])
    for (int i=0; i<1000; i++){
        arr[i] = rand() % 1000;
    }
    #pragma acc exit data detach(arr)

    bool check_status = acc_is_present(arr, 1000 * sizeof(int));
    if (check_status){
        #pragma acc parallel loop present(arr[:1000])
        for (int i=0; i<1000; i++){
            res += arr[i];
        }
        #pragma acc exit data delete(arr)
        acc_detach(arr);
        err = 1;
    }
    if (res != 0){
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