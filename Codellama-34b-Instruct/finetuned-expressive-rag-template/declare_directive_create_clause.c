#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a;
    int n = 100;

    #pragma acc declare create(a[0:n])
    {
        a = (int*)malloc(n * sizeof(int));
        if (a == NULL) {
            fprintf(stderr, "Error allocating memory\n");
            exit(1);
        }

        for (int x = 0; x < n; ++x) {
            a[x] = rand() % n;
        }

        #pragma acc parallel loop present(a[0:n])
        for (int x = 0; x < n; ++x) {
            a[x] = a[x] * 2;
        }

        for (int x = 0; x < n; ++x) {
            if (a[x] != (rand() % n) * 2) {
                err = 1;
                break;
            }
        }

        free(a);
    }

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