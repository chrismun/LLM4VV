#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:host_data construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 100;
    int data[N];
    int data_copy[N];

    // Initialize data on the host
    for(int i = 0; i < N; i++) {
        data[i] = i;
        data_copy[i] = 0;
    }

    // Copy data to the device
    #pragma acc data copyin(data)
    {
        // Copy data back to the host
        #pragma acc host_data use_device(data) if(0)
        {
            for(int i = 0; i < N; i++) {
                data_copy[i] = data[i];
            }
        }
    }

    // Check if the data was copied back correctly
    for(int i = 0; i < N; i++) {
        if(data_copy[i] != 0) {
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
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}