#include "acc_testsuite.h"
#ifndef T1
// T1:acc free, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    float *a;
    int n = 1024;
    a = (float*) acc_malloc(n*sizeof(float));
    if (a == NULL){
        return 1;    // err = 1 if malloc fails
    }
    #pragma acc parallel loop present(a[0:n])
    for (int i = 0; i < n; i++){
        a[i] = (float) i;
    }
    
    acc_free(a);
    if (acc_get_device_type() == acc_device_nvidia){
        if (acc_is_present(a, n*sizeof(float))){
            err = 1;  // err = 1 if memory is not freed
        }
    }
    else{
        if (acc_is_present(a, n*sizeof(float))){
            err = 1;  // err = 1 if memory is not freed
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