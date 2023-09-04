#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);
    int *c = (int *)malloc(sizeof(int) * 10);

    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = i;
    }

    #pragma acc data copy(a[0:10], b[0:10], c[0:10])
    {
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            a[i] = b[i] + c[i];
        }
    }

    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i] + c[i]) {
            err = 1;
            break;
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