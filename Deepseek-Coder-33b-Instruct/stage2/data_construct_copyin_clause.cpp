#include <stdlib.h>
#include <iostream>
#include <openacc.h>

#ifndef T1
//T1:data construct copyin clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 100;
    int host_data[size];
    int device_data[size];

    // Initialize host data
    for(int i = 0; i < size; i++) {
        host_data[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(host_data)
    {
        #pragma acc kernels
        for(int i = 0; i < size; i++) {
            device_data[i] = host_data[i];
        }
    }

    // Check if data was correctly copied
    for(int i = 0; i < size; i++) {
        if(device_data[i] != host_data[i]) {
            err = 1;
            break;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}