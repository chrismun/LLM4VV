#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:declare directive device_resident clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a, *b, *c;
    int n = 1000;

    a = (int*)malloc(n * sizeof(int));
    b = (int*)malloc(n * sizeof(int));
    c = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc declare device_resident(a, b)

    #pragma acc parallel loop present(a, b, c)
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }

    #pragma acc exit data copyout(c[0:n])

    for (int i = 0; i < n; i++) {
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