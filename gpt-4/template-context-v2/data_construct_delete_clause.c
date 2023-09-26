#include "acc_testsuite.h"
#ifndef T1
//T1:data construct delete clause,V:2.5-3.0
int test1(){
    int err = 0;
    srand(SEED);
    int array[100];
    int i;
    int * dev_ptr;

    for(i = 0; i < 100; i++) {
        array[i] = i;
    }

    #pragma acc enter data create(array[:100])
    dev_ptr = acc_deviceptr(array);

    #pragma acc exit data delete(array[:50])
    
    if((int*) acc_deviceptr(array) != dev_ptr) {
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