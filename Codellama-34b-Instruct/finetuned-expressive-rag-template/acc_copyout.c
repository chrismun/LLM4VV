#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 123

int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));

    for (int x = 0; x < 10; ++x){
        a[x] = rand() % 100;
        b[x] = 0;
    }

    #pragma acc enter data copyin(a[0:10])
    #pragma acc kernels present(a[0:10])
    {
        for (int x = 0; x < 10; ++x){
            a[x] += 1;
        }
    }

    #pragma acc update host(a[0:10])

    for (int x = 0; x < 10; ++x){
        b[x] = a[x];
    }

    #pragma acc exit data delete(a[0:10])

    for (int x = 0; x < 10; ++x){
        if (a[x] != b[x]){
            err += 1;
        }
    }

    free(a);
    free(b);

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