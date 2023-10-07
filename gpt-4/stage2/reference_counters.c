#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:reference counters,V:2.0-2.7*/

int test1(){
    int err = 0;
    srand(SEED);
    int *hostdata = (int *)malloc(10 * sizeof(int));
    int i;

    for (i = 0; i < 10; i++){
        hostdata[i] = i;
    }

    #pragma acc enter data create(hostdata[0:10])

    // Check if data is present in device
    if (!acc_is_present(hostdata, 10 * sizeof(int))){
        err = 1;
    }

    #pragma acc exit data delete(hostdata[0:10])

    // Check if data is not present in device
    if (acc_is_present(hostdata, 10 * sizeof(int))){
        err = 1;
    }

    free(hostdata);
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