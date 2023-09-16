#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait async,V:2.7-3.3
int test1(){
    int err = 0;
    float *a, *b;
    int length = 10000;
    int async = 5;

    a = (float *)malloc(length * sizeof(float));
    b = (float *)malloc(length * sizeof(float));

    #pragma acc enter data create(a[0:length], b[0:length])

    srand(SEED);
    #pragma acc parallel loop present(a[0:length]) async(async)
    for(int i = 0; i<length; ++i){
        a[i] = (float)rand()/(float)RAND_MAX;
    }

    #pragma acc parallel loop present(a[0:length], b[0:length]) async(async)
    for(int i = 0; i<length; ++i){
        b[i] = a[i]*2;
    }

    #pragma acc wait(async)

    #pragma acc exit data copyout(b[0:length])

    for(int i=0; i<length; i++)
        if(a[i]*2 != b[i])
            err = 1;

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