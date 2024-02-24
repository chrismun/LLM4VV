#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    int N = 100;
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    #pragma acc data copy(host_data[0:N])
    {
        #pragma acc kernels
        for (int i = 0; i < N; i++) {
            device_data[i] = host_data[i];
        }
    }

    for (int i = 0; i < N; i++) {
        if (host_data[i] != device_data[i]) {
            err++;
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}