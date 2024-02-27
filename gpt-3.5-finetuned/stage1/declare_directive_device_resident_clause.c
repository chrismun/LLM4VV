#include "acc_testsuite.h"
#ifndef T1
#define V1_ON_DEVICE
#endif

#ifndef T1
//T1:declare directive device_resident clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *deviced_memory_pointer;
    long bytes = sizeof(int) * n;

    deviced_memory_pointer = (int *)acc_malloc(bytes);
    if (deviced_memory_pointer == NULL){
        err += 1;
    }

    #pragma acc declare create(p[0:n]) device_resident
    #pragma acc parallel vector_length (16) copyout(p[0:n])
    {
        #pragma acc loop vector
        for (int x = 0; x < n; ++x){
            p[x] = 1;
        }
    }

    #pragma acc declare copyin(p[0:n]) device_resident(deviced_memory_pointer[0:n])
    #pragma acc kerenl loop gang worker vector
    {
        #pragma acc loop vector
        for (int x = 0; x < n; ++x){
            deviced_memory_pointer[x] = p[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (p[x] + 1 != deviced_memory_pointer[x]){
            err += 1;
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}