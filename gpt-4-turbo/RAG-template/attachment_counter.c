#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Define the array size
    const int array_size = 1024;
    
    // Allocate host arrays
    float *host_array1 = (float *)malloc(sizeof(float) * array_size);
    float *host_array2 = (float *)malloc(sizeof(float) * array_size);

    // Initialize host array
    for(int i = 0; i < array_size; ++i) {
        host_array1[i] = (float)rand() / RAND_MAX;
        host_array2[i] = (float)rand() / RAND_MAX;
    }

    // Allocate device memory and attach host_array1
    #pragma acc enter data copyin(host_array1[0:array_size])
    
    // Attach host_array1 again without detaching to increment the attachment counter
    #pragma acc enter data copyin(host_array1[0:array_size])

    // Attach host_array2 to another segment of device memory
    #pragma acc enter data copyin(host_array2[0:array_size])

    // Modify host_array1 using an OpenACC parallel region
    #pragma acc parallel loop present(host_array1[0:array_size])
    for(int i = 0; i < array_size; ++i) {
        host_array1[i] *= 2.0f;
    }

    // Detach one instance of host_array1
    #pragma acc exit data copyout(host_array1[0:array_size])

    // Attempt to modify host_array1 again, expecting it to be still present
    #pragma acc parallel loop present(host_array1[0:array_size])
    for(int i = 0; i < array_size; ++i) {
        host_array1[i] += 1.0f;
    }

    // Completely detach host_array1
    #pragma acc exit data delete(host_array1[0:array_size])

    // Check if host_array1 modifications are effective
    for(int i = 0; i < array_size; ++i) {
        if (host_array1[i] != ((host_array1[i] * 2.0f) + 1.0f)) {
            err++;
        }
    }

    free(host_array1);
    free(host_array2);

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