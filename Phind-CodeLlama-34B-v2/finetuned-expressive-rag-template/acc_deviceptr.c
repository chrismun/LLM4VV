#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    int *host_data = (int*)malloc(sizeof(int));
    *host_data = rand() % 100;

    int *device_data = (int*)acc_deviceptr(host_data);

    if (device_data == NULL) {
        printf("Device pointer is NULL. This might be because the data is not present in the current device memory.\n");
        err = 1;
    } else if (device_data != host_data) {
        printf("Device pointer does not match the host pointer. This might be because the data is in shared memory.\n");
        err = 1;
    }

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