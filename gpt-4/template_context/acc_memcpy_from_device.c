#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100000
#define SEED 12345
#define NUM_TEST_CALLS 10

int test_memcpy_from_device(){
    int err = 0;
    srand(SEED);

    int *data_host_dest = (int*) malloc(SIZE * sizeof(int));
    int *data_dev_src = (int*) acc_malloc(SIZE * sizeof(int));

    // Initialize device source data
    #pragma acc parallel loop deviceptr(data_dev_src)
    for(int i=0; i<SIZE; i++){
        data_dev_src[i] = rand();
    }

    // Copy from device to host
    acc_memcpy_from_device(data_host_dest, data_dev_src, SIZE * sizeof(int));

    // Verify the copy
    #pragma acc parallel loop deviceptr(data_dev_src)
    for(int i=0; i<SIZE; i++){
        if(data_host_dest[i] != data_dev_src[i]){
            err = 1;
            break;
        }
    }

    free(data_host_dest);
    acc_free(data_dev_src);
    
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_memcpy_from_device();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    if(failcode == 0){
        printf("Test Passed\n");
    }else{
        printf("Test Failed\n");
    }
    return failcode;
}