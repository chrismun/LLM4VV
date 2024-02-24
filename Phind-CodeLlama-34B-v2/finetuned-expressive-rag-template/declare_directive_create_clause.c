#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a;
    int n = 10;

    #pragma acc declare create(a[0:n])
    {
        a = (int*)malloc(n * sizeof(int));
        if (a == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        for (int i = 0; i < n; i++) {
            a[i] = i;
        }

        #pragma acc parallel loop present(a[0:n])
        for (int i = 0; i < n; i++) {
            a[i] += 1;
        }

        for (int i = 0; i < n; i++) {
            if (a[i] != i + 1) {
                fprintf(stderr, "Incorrect result at a[%d] = %d, expected %d\n", i, a[i], i + 1);
                err = 1;
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