#include "acc_testsuite.h"
#include <stdio.h>

//Test1: Basic kernels construct, V: 2.7-2.9
int test1() {
    int err = 0;
    int arraySize = 1024;
    float* a = (float*)malloc(sizeof(float) * arraySize);
    float* b = (float*)malloc(sizeof(float) * arraySize);
    float* c = (float*)malloc(sizeof(float) * arraySize);
    srand(SEED);

    for(int i=0; i<arraySize; i++) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
    }

    #pragma acc kernels copy(a[0:arraySize], b[0:arraySize], c[0:arraySize])
    {
        for(int i=0; i<arraySize; i++) {
            c[i] = a[i] + b[i];
        }
    }

    for(int i=0; i<arraySize; i++) {
        if(fabs((a[i]+b[i]) - c[i]) > PRECISION) {
            err = 1;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
      failed = failed + test1();
    }

    if (failed != 0){
      failcode = failcode + (1 << 0);
    }

    return failcode;
}