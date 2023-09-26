#include "acc_testsuite.h"
#ifndef T1
//T1:cache directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int n = 10000;
    float *a = (float*)malloc(n*sizeof(float));
    float *b = (float*)malloc(n*sizeof(float));

    for (int i = 0; i < n; i++) {
        a[i] = (float) rand() / (float) RAND_MAX;
        b[i] = 0.0f;
    }

    #pragma acc kernels copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc loop
        for(int i = 0; i < n; i++) {
            #pragma acc cache(a[i])
            b[i] = a[i] * 2.0f;
        }
    }

    for(int i = 0; i < n; i++) {
        if(b[i] != a[i] * 2.0f){
            err = 1;
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