++
#include "acc_testsuite.h"
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(0));

    float *a = (float*) malloc(SIZE * sizeof(float));
    float *b = (float*) malloc(SIZE * sizeof(float));
    float *c = (float*) malloc(SIZE * sizeof(float));

    for(int i=0; i<SIZE; i++) {
        a[i] = rand()/(float)RAND_MAX;
        b[i] = rand()/(float)RAND_MAX;
    }

    #pragma acc data copyin(a[0:SIZE], b[0:SIZE]) copyout(c[0:SIZE])
    {
        #pragma acc parallel loop worker
        for(int i=0; i<SIZE; i++) {
            c[i] = a[i] + b[i];
        }
    }

    for(int i=0;i<SIZE;i++) {
        if(abs(c[i] - (a[i] + b[i])) > 0.00001) {
            err = 1;
            break;
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