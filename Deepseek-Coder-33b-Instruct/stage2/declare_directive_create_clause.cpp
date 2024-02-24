#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_data = (int*)malloc(100 * sizeof(int));
    int *device_data;

    #pragma acc data create(device_data[0:100])
    {
        device_data = (int*)acc_malloc(100 * sizeof(int));

        // Initialize host_data and device_data
        for(int i = 0; i < 100; i++) {
            host_data[i] = i;
            device_data[i] = i;
        }

        // Verify that the data was correctly copied
        for(int i = 0; i < 100; i++) {
            if(host_data[i] != device_data[i]) {
                err = 1;
                break;
            }
        }

        // Free the device memory
        acc_free(device_data);
    }

    free(host_data);

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