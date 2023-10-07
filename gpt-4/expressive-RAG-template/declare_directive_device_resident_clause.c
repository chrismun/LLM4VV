#include "acc_testsuite.h"

#ifndef T1
//T1:declare directive device_resident clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int* value;
    int* device_value;

    value = (int*)malloc(sizeof(int));
    assert(value != NULL);

    #pragma acc declare device_resident(device_value)
    device_value = acc_copyin(value, sizeof(int));
    
    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        #pragma acc loop
        for(int i=0; i<1; i++){
            device_value[i] = i;
        }
    }
    
    acc_copyout(value, sizeof(int));
    
    if (*value != 0){
        err = 1;
    }

    free(value);
    
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