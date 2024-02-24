#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:compute construct vector_length clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int N = 1024;
    int vector_length = 16;
    double *a = (double*)malloc(N * sizeof(double));
    double *b = (double*)malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc parallel loop vector_length(vector_length)
    for (int i = 0; i < N; i++) {
        b[i] = a[i] * 2.0;
    }

    for (int i = 0; i < N; i++) {
        if (b[i] != a[i] * 2.0) {
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