#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    int data[10];
    int *d_data;

    for (int i = 0; i < 10; i++) {
        data[i] = rand() % 100;
    }

    d_data = (int *)acc_create(data, 10 * sizeof(int));

    if (d_data == NULL) {
        err = 1;
    }

    acc_delete(d_data, 10 * sizeof(int));

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