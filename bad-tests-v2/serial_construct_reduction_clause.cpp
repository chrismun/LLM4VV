#include "acc_testsuite.h"
#include <stdlib.h>
#ifndef T1
/*T1:serial construct reduction clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int* arr = (int*)malloc(100*sizeof(int));
    int reducedVal = 0;
    int expectedVal = 0;

    for(int i = 0; i < 100; i++){
        arr[i] = rand() % 100;
        expectedVal += arr[i];
    }
    
    #pragma acc serial reduction(+:reducedVal)
    for(int i = 0; i < 100; i++){
        reducedVal += arr[i];
    }

    if(reducedVal != expectedVal){
        err = 1;
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