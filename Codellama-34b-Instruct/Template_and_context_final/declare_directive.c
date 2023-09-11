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

    #pragma acc declare copy(a)
    #pragma acc declare copyin(b)

    *a = 1;
    *b = 2;

    #pragma acc parallel
    {
        *a = 3;
        *b = 4;
    }

    if (*a != 3 || *b != 4){
        err = 1;
    }

    acc_free(a);
    acc_free(b);

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