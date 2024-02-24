#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:acc map data,V:2.7-3.3
int test1(){
    int err = 0;
    int size = 100;
    int *host_data = (int*)malloc(size * sizeof(int));
    int *device_data;

    // Initialize host data
    for(int i = 0; i < size; i++) {
        host_data[i] = i;
    }

    // Allocate device memory
    device_data = (int*)acc_malloc(size * sizeof(int));

    // Map host data to device data
    acc_map_data(host_data, device_data, size * sizeof(int));

    // Check if data was correctly mapped
    for(int i = 0; i < size; i++) {
        if(host_data[i] != device_data[i]) {
            err = 1;
            break;
        }
    }

    // Unmap data
    acc_unmap_data(host_data);

    // Free memory
    free(host_data);
    acc_free(device_data);

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