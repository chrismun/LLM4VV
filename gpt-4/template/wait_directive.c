#include "acc_testsuite.h"
#ifndef T1
//T1:wait directive,V:2.7-3.3
int test1(){
    int err = 0;
    float* a = (float*)malloc(N*sizeof(float));
    float* b = (float*)malloc(N*sizeof(float));

    for(int i=0; i<N; i++) {
        a[i] = (float)rand()/(float)RAND_MAX;
        b[i] = (float)rand()/(float)RAND_MAX;
    }

    #pragma acc parallel loop copy(a[0:N],b[0:N]) async(1)
    for(int i=0; i<N; i++) {
        a[i] = a[i] + b[i];
    }

    #pragma acc parallel loop copy(a[0:N],b[0:N]) async(2)
    for(int i=0; i<N; i++) {
        a[i] = a[i] * b[i];
    }

    #pragma acc wait 

    // Check result
    for(int i=0; i<N; i++) {
        if(a[i] != (a[i] + b[i]) * b[i]) {
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