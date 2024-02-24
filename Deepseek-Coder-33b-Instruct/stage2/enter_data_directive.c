#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:enter data directive,V:2.7-3.3
int test1(){
    int err = 0;
    int N = 100;
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = (int*)malloc(N * sizeof(int));

    // Initialize host data
    for(int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(host_data[0:N]) copyout(device_data[0:N])
    {
        // Enter data directive
        #pragma acc enter data copyin(host_data[0:N])

        // Copy data from host to device
        #pragma acc update device(device_data[0:N])

        // Exit data directive
        #pragma acc exit data copyout(device_data[0:N])
    }

    // Check if data was copied correctly
    for(int i = 0; i < N; i++) {
        if(host_data[i] != device_data[i]) {
            err = 1;
            break;
        }
    }

    free(host_data);
    free(device_data);

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