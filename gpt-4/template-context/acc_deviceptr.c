#include "openacc.h"
#include "acc_testsuite.h"
#ifndef T1
#define SIZE 1024
int test1(){
    int err = 0;
    int *host_data, *device_ptr;
    srand(SEED);

    host_data = (int*) malloc(SIZE * sizeof(int));

    for(int i = 0; i < SIZE; ++i){
        host_data[i] = rand() % 100;
    }

    #pragma acc enter data copyin(host_data[0:SIZE])
    
    device_ptr = (int*) acc_deviceptr(host_data);
    if (device_ptr == NULL){
        err = 1;
        printf("Error: data is not found in the current device memory.\n");
    }

    #pragma acc exit data delete(host_data[0:SIZE])

    free(host_data);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}