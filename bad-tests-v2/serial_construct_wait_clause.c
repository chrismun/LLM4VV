#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct,wait clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int length = 100;
    float * a = (float *)malloc(length * sizeof(float));
    float * b = (float *)malloc(length * sizeof(float));
    float * c = (float *)malloc(length * sizeof(float));
    int i;
    for (i=0; i<length; i++){
        a[i] = rand()/(float)RAND_MAX;
        b[i] = rand()/(float)RAND_MAX;
        c[i] = 0.0;
    }
    
    #pragma acc data copyin(a[0:length], b[0:length]) copyout(c[0:length]) async(1)
    #pragma acc serial present(a[0:length], b[0:length], c[0:length])
    for (i=0; i<length; i++){
        c[i] = a[i] + b[i];
    }
    #pragma acc wait(1)
    for (i=0; i<length; i++){
        if (fabs(c[i] - a[i] - b[i]) > PRECISION){
            err = 1;
        }
    }

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