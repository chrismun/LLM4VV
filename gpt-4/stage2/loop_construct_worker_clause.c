#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:loop construct worker clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    unsigned int length = 100;
    int *data = (int*) malloc(length * sizeof(int));

    // initialize the data array
    for(unsigned int i = 0; i < length; i++){
        data[i] = i;
    }

    // Execute loop with worker clause
    #pragma acc parallel loop worker
    for(unsigned int i = 0; i < length; i++){
        data[i] = data[i] + 1;
    }

    // Verify the data
    for(unsigned int i = 0; i < length; i++){
        if(data[i] != i + 1){
            err = 1;
        }
    }

    free(data);

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