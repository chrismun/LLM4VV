#include "acc_testsuite.h"
#ifndef T1
#define N 24576
//T1:wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    float *a = (float*)malloc(N * sizeof(float));
    float *b = (float*)malloc(N * sizeof(float));

    for(int i = 0; i < N; i++) {
        a[i] = (float)rand() / (float)RAND_MAX;
        b[i] = (float)rand() / (float)RAND_MAX;
    }

    #pragma acc data copyin(a[0:N]) copyout(b[0:N]) 
    {
        #pragma acc parallel loop
        for(int i = 0; i < N; i++) {
            b[i] = a[i] * a[i];
        }
        #pragma acc wait 
    }

    for(int i = 0; i < N; i++) {
        if(fabs(b[i] - (a[i]*a[i])) > 1e-5) {
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