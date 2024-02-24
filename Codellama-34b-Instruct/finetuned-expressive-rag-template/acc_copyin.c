#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 123

int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *d_a = (int *)acc_copyin(a, 10 * sizeof(int));

    if (d_a == NULL){
        err = 1;
        printf("acc_copyin failed to allocate device memory\n");
    }

    for (int x = 0; x < 10; ++x){
        a[x] = rand() % 100;
    }

    acc_copyout(a, 10 * sizeof(int));

    for (int x = 0; x < 10; ++x){
        if (a[x] != d_a[x]){
            err = 1;
            printf("Data mismatch at index %d: host %d, device %d\n", x, a[x], d_a[x]);
        }
    }

    free(a);
    acc_free(d_a);

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