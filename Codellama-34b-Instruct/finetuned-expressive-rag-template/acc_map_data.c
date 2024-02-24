#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    int *host_data = (int *)malloc(sizeof(int));
    *host_data = rand() % 100;

    int *device_data = (int *)acc_malloc(sizeof(int));

    acc_map_data(host_data, device_data, sizeof(int));

    int *host_data_copy = (int *)malloc(sizeof(int));
    acc_copyout(host_data_copy, sizeof(int));

    if (*host_data_copy != *host_data){
        err = 1;
    }

    acc_unmap_data(host_data);
    acc_free(device_data);
    free(host_data);
    free(host_data_copy);

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