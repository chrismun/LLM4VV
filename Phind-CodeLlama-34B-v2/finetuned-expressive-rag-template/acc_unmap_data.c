#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#define acc_unmap_data(data_arg) __acc_unmap_data(data_arg)

int test1(){
    int err = 0;
    srand(SEED);

    int *host_data = (int *)malloc(sizeof(int));
    *host_data = rand() % 100;

    acc_map_data(host_data, sizeof(int));
    acc_unmap_data(host_data);

    free(host_data);

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