#include "acc_testsuite.h"
#ifndef T1
// T1:kernels construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int n = 100;
    float a[n], b[n], c[n];

    for(int i=0; i<n; i++) {
       a[i] = (float)rand()/(float)(RAND_MAX);
       b[i] = (float)rand()/(float)(RAND_MAX);
    }

    #pragma acc kernels 
    for(int i=0; i<n; i++) {
       c[i] = a[i] + b[i];
    }

    #pragma acc parallel loop
    for(int i=0; i<n; i++) {
        if(fabs(c[i] - a[i] - b[i]) > 1e-5){
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
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}