#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    int *a, *b, *c;
    int n = 1024;
    a = (int*)malloc(n * sizeof(int));
    b = (int*)malloc(n * sizeof(int));
    c = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc kernels present(a[0:n], b[0:n])
    {
        for (int i = 0; i < n; i++) {
            a[i] += b[i];
        }
    }

    #pragma acc update self(a[0:n])

    for (int i = 0; i < n; i++) {
        c[i] = a[i];
    }

    for (int i = 0; i < n; i++) {
        if (a[i] != c[i]) {
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(a[0:n], b[0:n])

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