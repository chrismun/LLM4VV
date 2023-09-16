#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct auto clause,V:2.7-3.3
int test1(){
    int err = 0;
    int length = 1000;
    srand(SEED);
    double *a = (double*)malloc(sizeof(double) * length);
    double *b = (double*)malloc(sizeof(double) * length);
    double *c = (double*)malloc(sizeof(double) * length);

    // Initialize vectors a and b
    for(int i = 0; i < length; i++) {
        a[i] = rand() / (double)RAND_MAX;
        b[i] = rand() / (double)RAND_MAX;
    }
    
    #pragma acc parallel loop auto
    for(int i = 0; i < length; i++) {
        c[i] = a[i] + b[i];
    }

    // Check results
    for(int i = 0; i < length; i++) {
        if(fabs(c[i] - (a[i] + b[i])) > 1e-5) {
            err = 1;
            break;
        }
    }

    // Clean up
    free(a);
    free(b);
    free(c);

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