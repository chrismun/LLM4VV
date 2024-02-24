#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 10;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc data detach(a[0:n])
    {
        #pragma acc parallel loop present(a[0:n])
        for (int i = 0; i < n; i++) {
            a[i] += 1;
        }

        #pragma acc update self(a[0:n])
    }

    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }

    for (int i = 0; i < n; i++) {
        if (b[i] != a[i] + 1) {
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(a[0:n])
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