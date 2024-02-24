#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:data construct copy clause,V:2.7-3.3
int test1(){
    int err = 0;
    int n = 100;
    int *host_array = (int*)malloc(n * sizeof(int));
    int *device_array = (int*)malloc(n * sizeof(int));

    // Initialize host array
    for(int i = 0; i < n; i++) {
        host_array[i] = i;
    }

    // Copy host array to device
    #pragma acc data copyin(host_array[0:n]) copyout(device_array[0:n])
    {
        #pragma acc parallel loop
        for(int i = 0; i < n; i++) {
            device_array[i] = host_array[i];
        }
    }

    // Verify that the copy was successful
    for(int i = 0; i < n; i++) {
        if(host_array[i] != device_array[i]) {
            err = 1;
            break;
        }
    }

    free(host_array);
    free(device_array);

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