#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 123

int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int*)malloc(10 * sizeof(int));
    int *d_a;

    for (int i = 0; i < 10; i++) {
        a[i] = rand() % 100;
    }

    d_a = (int*)acc_copyin(a, 10 * sizeof(int));

    if (d_a != a) {
        err = 1;
    }

    for (int i = 0; i < 10; i++) {
        if (a[i] != d_a[i]) {
            err = 1;
        }
    }

    acc_free(d_a);
    free(a);

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