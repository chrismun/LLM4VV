#include "acc_testsuite.h"

#ifndef T1
//T1:enter data directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int *host_data = (int*)malloc(n * sizeof(int));
    int *device_data = (int*)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        host_data[i] = rand() % 100;
    }

    #pragma acc data copyin(host_data[0:n]) copyout(device_data[0:n])
    {
        #pragma acc enter data copyin(host_data[0:n]) create(device_data[0:n])
        #pragma acc update device(device_data[0:n])
    }

    for(int i = 0; i < n; i++){
        if(host_data[i] != device_data[i]){
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