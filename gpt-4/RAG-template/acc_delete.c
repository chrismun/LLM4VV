#include "acc_testsuite.h"

#ifndef T1

int test(){
    int err = 0;
    float* a = (float*)malloc(100*sizeof(float));
    float b[100];
    srand(SEED);
 
    #pragma acc enter data create(a[0:100])

    
    #pragma acc parallel loop present(a[0:100])
    for(int n=0; n<100; n++){
        a[n] = rand()%100;
    }

    #pragma acc exit data copyout(a[0:100])
    
    for(int n=0; n<100; n++){
        b[n] = a[n];
    }
    
    #pragma acc enter data create(a[0:100])

    #pragma acc exit data delete(a[0:100])
    
    #pragma acc update host(a[0:100])

    for(int n=0; n<100; n++){
        if (a[n] != 0){
            err = 1;
        }
        if (b[n] != a[n]){
            err = 1;
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
        failed = failed + test();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}