#include "acc_testsuite.h"
#ifndef T1
//T1:acc copyout,V:2.7-3.3
int test1(){
    int err = 0;
    
    int *array_host;
    int n = 10000;
    array_host = (int*) malloc(n*sizeof(int));

    // Initialize on the host
    for(int i=0; i<n; i++){
        array_host[i] = i;
    }

    // Use acc copyout to move it to device and do some operations
    #pragma acc data copyout(array_host[0:n])
    {
        #pragma acc parallel loop
        for(int i=0; i<n; i++){
            array_host[i] += 10;
        }
    }

    // Check on the host
    for(int i=0; i<n; i++){
        if(array_host[i] != i+10){
            err = 1;
            break;
        }
    }
    
    free(array_host);

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