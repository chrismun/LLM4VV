#include "acc_testsuite.h"

int test_delete_clause(){
    int err = 0;
    int *host_arr;
    int *device_arr;
    int size = 1024;

    /* allocate memory on host and fill it with data */
    host_arr = (int*)malloc(size * sizeof(int));
    for(int i=0; i<size; i++) {
        host_arr[i] = i+1;
    }

    /* allocate memory on the device and copy the host data */
    #pragma acc data copyin(host_arr[0:size]) create(device_arr[0:size])
    {
        /* copy data from host_arr to device_arr */
        #pragma acc parallel loop
        for(int i=0; i<size; i++) {
            device_arr[i] = host_arr[i];
        }
    }

    /* check if the host_arr is deleted correctly */
    #pragma acc exit data delete(host_arr[0:size])
    if(acc_is_present(host_arr, size*sizeof(int))) {
        printf("Error: host_arr is still present on the device after delete.\n");
        err = 1;
    }

    free(host_arr);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}