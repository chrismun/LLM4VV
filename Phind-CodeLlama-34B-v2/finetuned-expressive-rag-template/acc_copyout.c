#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 123

int test1(){
    int err = 0;
    srand(SEED);

    int *a, *b, *c;
    int n = 1024;
    a = (int*)malloc(n * sizeof(int));
    b = (int*)malloc(n * sizeof(int));
    c = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++){
        a[i] = rand() % 100;
        b[i] = 0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data create(b[0:n])

    #pragma acc kernels present(a[0:n], b[0:n])
    {
        for (int i = 0; i < n; i++){
            b[i] = a[i] * 2;
        }
    }

    #pragma acc update self(b[0:n])

    #pragma acc exit data copyout(a[0:n])
    #pragma acc exit data delete(b[0:n])

    for (int i = 0; i < n; i++){
        c[i] = a[i] * 2;
    }

    for (int i = 0; i < n; i++){
        if (b[i] != c[i]){
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