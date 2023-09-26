#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct device_type clause,V:2.7-3.3
int test1(){
    int err = 0;
    float a[1000];
    float b[1000];

    srand((unsigned int)time(NULL));

    // Initialize arrays
    for (int i = 0; i < 1000; i++) {
        a[i] = rand() % 1000;
        b[i] = 0.0;
    }

    #pragma acc data copy(a), copyout(b)
    {
        #pragma acc parallel loop device_type(nvidia, host)
        for (int i=0; i<1000; i++) {
            b[i] += a[i];
        }
    }

    for(int i=0; i<1000; i++){
      if(b[i] != a[i]) {
            err = 1;
            break;
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