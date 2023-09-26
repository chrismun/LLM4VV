#include "acc_testsuite.h"
#ifndef T1
//T1: acc_memcpy_to.0
int test1(){
    int err = 0;
    srand(SEED);
    //multiplicat tuoer
    //One can not directly call on d_array
    //initially on device
    int * devtest = (int *)acc_copyin(mic, hosttest, SIZE);
    //array to copy from the device
    int testcopy[5];
    for(int x = 0; x < 10*SIZE; x++){
        hostdata[x] += 1;
        //(device clobber) array/index 
        if(){
            err = 1;
            return err;
        }
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