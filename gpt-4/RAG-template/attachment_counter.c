#include "acc_testsuite.h"
#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    float *a = (float*)malloc(100 * sizeof(float));
    float *b = (float*)malloc(100 * sizeof(float));
    
    #pragma acc enter data create(a[0:100])
    
    for(int i = 0; i < 100; i++) {
        a[i] = i * 1.0f;
        b[i] = 0.0f;
    }
    
    #pragma acc update device(a[0:100])
    #pragma acc parallel loop copyout(b[0:100])
    for(int i = 0; i < 100; i++) {
        b[i] = a[i];
    }
    
    #pragma acc exit data delete(a[0:100])
    
    for(int i = 0; i < 100; i++) {
        if(fabs(b[i] - i * 1.0f) > 1e-5f) {
            err = 1;
            break;
        }
    }
    
    free(a);
    free(b);

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