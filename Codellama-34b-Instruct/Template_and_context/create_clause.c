#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int*)acc_malloc(sizeof(int));
    int *b = (int*)acc_malloc(sizeof(int));
    int *c = (int*)acc_malloc(sizeof(int));

    #pragma acc create(a[0:10], b[0:10], c[0:10])

    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = i;
    }

    #pragma acc update(a[0:10], b[0:10], c[0:10])

    for (int i = 0; i < 10; i++) {
        if (a[i] != i || b[i] != i || c[i] != i) {
            err = 1;
            break;
        }
    }

    #pragma acc free(a, b, c)

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