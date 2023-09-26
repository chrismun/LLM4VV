#include "acc_testsuite.h"
#ifndef T1
//T1:cache directive,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    
    int n = 1024;
    float *x = (float *)malloc(n*sizeof(float));
    float *y = (float *)malloc(n*sizeof(float));
    for (int i = 0; i < n; i++) {
        x[i] = rand()/(float)RAND_MAX;
        y[i] = 0.0f;
    }

    #pragma acc data copyin(x[0:n]) copy(y[0:n])
    {
        #pragma acc parallel loop 
        #pragma acc cache(x[0:n], y[0:n]) 
        for (int i = 0; i < n; i++) {
            y[i] = x[i] * x[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (fabs(y[i] - x[i]*x[i]) > PRECISION) {
            err = 1;
            break;
        }
    }

    free(x);
    free(y);

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