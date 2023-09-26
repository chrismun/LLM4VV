#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct delete clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int* hostdata = new int[1024];
    int* devicedata;

    #pragma acc enter data create(devicedata[0:1024])
    devicedata = acc_copyin(hostdata, 1024 * sizeof(int));

    if(devicedata == NULL){
        err = 1;
        return err;
    }

    #pragma acc exit data delete(devicedata[0:1024])

    if(acc_is_present(devicedata, 1024 * sizeof(int))){
        err = 1;
    }

    delete[] hostdata;

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