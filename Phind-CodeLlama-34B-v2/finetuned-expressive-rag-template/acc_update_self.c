#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));

    for (int i = 0; i < 10; i++) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    #pragma acc enter data copyin(a[0:10])
    #pragma acc update device(a[0:10])

    #pragma acc parallel present(a[0:10])
    {
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            a[i] += 1;
        }
    }

    #pragma acc update self(a[0:10])

    for (int i = 0; i < 10; i++) {
        b[i] = a[i];
    }

    #pragma acc exit data delete(a[0:10])

    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i]) {
            err = 1;
            break;
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