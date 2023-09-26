#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

int test_acc_deviceptr(){
    int err = 0;
    size_t array_size = 10000;
    int *host_array, *device_ptr;
    
    /* allocate host memory */
    host_array = (int*) malloc(sizeof(int) * array_size);

    /* initialize data */
    for(int i=0; i<array_size; i++){
        host_array[i] = i;
    }

    /* Push data to device and compute */
    #pragma acc enter data copyin(host_array[0:array_size]) create(device_ptr[0:array_size])
    {
        /* compute on device */
        #pragma acc parallel loop present(host_array[0:array_size]) present(device_ptr[0:array_size]) 
        for(int i=0; i<array_size; i++){
            device_ptr[i] = host_array[i] + 1;
        }
    }

    /* Getting device_ptr from acc_deviceptr */
    void *device_ptr_status = acc_deviceptr((void*)device_ptr);

    /* Check if the device pointer is not NULL */
    if(device_ptr_status == NULL) {
        printf("acc_deviceptr failed to get the device pointer\n");
        err = 1;
    }
    #pragma acc exit data delete(host_array[0:array_size], device_ptr[0:array_size])

    /* free host array */
    free(host_array);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    /* calling the test function for NUM_TEST_CALLS times */
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_deviceptr();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}