#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
#define T1
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
    #pragma acc data copyin(host_data[:N]) copyout(device_data[:N])
    {
        #pragma acc host_data use_device(host_data)
        {
            // Copy data from host to device
            for(int i = 0; i < N; i++) {
                device_data[i] = host_data[i];
            }
        }
    }

    // Verify data
    for(int i = 0; i < N; i++) {
        if(device_data[i] != host_data[i]) {
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