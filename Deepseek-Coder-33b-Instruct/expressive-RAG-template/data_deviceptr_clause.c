#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:data deviceptr clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_ptr, *device_ptr;
    int size = 100;
    int i;

    // Allocate memory on the host
    host_ptr = (int*)malloc(size * sizeof(int));
    if(host_ptr == NULL) {
        printf("Memory allocation failed on host\n");
        return 1;
    }

    // Initialize host data
    for(i = 0; i < size; i++) {
        host_ptr[i] = i;
    }

    // Allocate memory on the device
    device_ptr = (int*)acc_malloc(size * sizeof(int));
    if(device_ptr == NULL) {
        printf("Memory allocation failed on device\n");
        return 1;
    }

    // Copy data from host to device
    #pragma acc data copyin(host_ptr[0:size]) copyout(device_ptr[0:size])
    {
        #pragma acc kernels
        for(i = 0; i < size; i++) {
            device_ptr[i] = host_ptr[i];
        }
    }

    // Verify the data on the device
    for(i = 0; i < size; i++) {
        if(device_ptr[i] != host_ptr[i]) {
            printf("Data verification failed at index %d\n", i);
            err = 1;
            break;
        }
    }

    // Free memory
    free(host_ptr);
    acc_free(device_ptr);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}