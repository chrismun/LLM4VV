#include "acc_testsuite.h"
#ifndef T1
//T1:exit data directive,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    int i;
    float *a = (float*)malloc(10*sizeof(float));
    
    #pragma acc enter data create(a[0:10])

    for(i = 0; i < 10; i++)
        a[i] = i*1.0f;

    #pragma acc exit data copyout(a[0:10])
    
    // Checking if exit data works well 
    for(i = 0; i < 10; i++) { 
        if(a[i] != i*1.0f){
          err = 1;
          break;
        }
    }

    free(a);
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