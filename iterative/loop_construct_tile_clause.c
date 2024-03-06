#include "acc_testsuite.h"

#define SIZE 1000

int test1(){
    int err = 0;
    int i, j;
    int *a = (int*)malloc(SIZE * sizeof(int));
    int sum = 0, sum_acc = 0;

    srand(SEED);
    for (i = 0; i < SIZE; ++i) {
        a[i] = rand() % 100;
    }

    #pragma acc data copyin(a[0:SIZE])
    {
        #pragma acc parallel loop tile(32) reduction(+:sum)
        for (i = 0; i < SIZE; ++i) {
            sum += a[i];
        }
    }

    for (j = 0; j < SIZE; ++j) {
        sum_acc += a[j];
    }

    if (sum != sum_acc) {
        err++;
        printf("Error: sum = %d, sum_acc = %d\n", sum, sum_acc);
    }

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