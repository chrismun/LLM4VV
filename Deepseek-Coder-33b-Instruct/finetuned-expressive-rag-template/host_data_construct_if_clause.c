#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:host_data construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 100;
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = (int*)malloc(N * sizeof(int));

    for(int i = 0; i < N; i++) {
        host_data[i] = i;
        device_data[i] = 0;
    }

    #pragma acc data copyin(host_data[:N]) copyout(device_data[:N])
    {
        #pragma acc host_data use_device(host_data) if(N > 50)
        {
            for(int i = 0; i < N; i++) {
                device_data[i] = host_data[i];
            }
        }
    }

    for(int i = 0; i < N; i++) {
        if(i > 50 && host_data[i] != device_data[i]) {
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