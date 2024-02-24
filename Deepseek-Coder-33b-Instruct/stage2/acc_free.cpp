#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    int *data_dev = (int*)acc_malloc(NUM_TEST_CALLS * sizeof(int));

    if (data_dev == NULL) {
        err = 1;
    } else {
        acc_free(data_dev);
    }

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