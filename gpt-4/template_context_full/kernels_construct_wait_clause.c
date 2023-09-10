#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:kernels construct wait clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    int num_items = 1000;
    int *arr = (int*) malloc(sizeof(int)*num_items);

    for(int i = 0; i < num_items; i++) {
        arr[i] = 1;
    }

    #pragma acc data copy(arr[0:num_items]) 
    {
        #pragma acc kernels async
        for(int i = 0; i < num_items; i++) {
            arr[i] += 1;
        }
        
        #pragma acc wait
        #pragma acc kernels async
        for(int i = 0; i < num_items; i++) {
            arr[i] -= 1;
        }
    }

    #pragma acc wait
    
    for(int i = 0; i < num_items; i++) {
        if(arr[i] != 1){
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