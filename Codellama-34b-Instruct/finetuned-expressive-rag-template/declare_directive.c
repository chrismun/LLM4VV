#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:declare directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));

    for (int i = 0; i < 10; i++) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    #pragma acc declare create(a[0:10])
    #pragma acc parallel loop present(a, b)
    for (int i = 0; i < 10; i++) {
        b[i] = a[i];
    }

    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i]) {
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