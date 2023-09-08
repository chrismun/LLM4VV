#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy from device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));

    int* host_array = (int*)malloc(n * sizeof(int));
    int* host_array_copy = (int*)malloc(n * sizeof(int));
    int* device_array;

    for (int i = 0; i < n; i++) {
        host_array[i] = rand() % n;
        host_array_copy[i] = 0;
    }

    #pragma acc enter data copyin(host_array[0:n])
    #pragma acc enter data create(device_array[0:n])

    #pragma acc data present(host_array, device_array)
    {
        #pragma acc host_data use_device(device_array)
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int i = 0; i < n; i++) {
                    device_array[i] = host_array[i];
                }
            }
        }

        #pragma acc update self(device_array[0:n])

        #pragma acc memcpy(host_array_copy[0:n], device_array[0:n])

        for (int i = 0; i < n; i++) {
            if (host_array[i] != host_array_copy[i]) {
                err = 1;
                break;
            }
        }
    }

    #pragma acc exit data delete(device_array)
    #pragma acc exit data copyout(host_array[0:n])

    free(host_array);
    free(host_array_copy);

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