#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));
    int *c = (int *)malloc(10 * sizeof(int));

    for (int i = 0; i < 10; i++) {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }

    #pragma acc host_data use_device(a, b)
    {
        for (int i = 0; i < 10; i++) {
            c[i] = a[i] + b[i];
        }
    }

    for (int i = 0; i < 10; i++) {
        if (c[i] != a[i] + b[i]) {
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