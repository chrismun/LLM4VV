#include "acc_testsuite.h"

//T1:acc update device,V:2.7-3.3
int test_update_device() {
    int err = 0;
    srand(SEED);
    
    int array_size = 100;
    float *a_h = (float*)malloc(array_size * sizeof(float));
    float *a_d = (float*)malloc(array_size * sizeof(float));
    // Initialize host array
    for(int i=0; i<array_size; i++) {
        a_h[i] = rand() / (float)RAND_MAX;
    }

    #pragma acc enter data copyin(a_h[:array_size])
    
    // Copy data from the host to the device
    #pragma acc update device(a_h[:array_size])

    // Retrieve back to host
    #pragma acc update host(a_d[:array_size])

    // Check if the array data on the device matches that on the host
    for(int i=0; i<array_size; i++) {
        if(fabs(a_h[i]-a_d[i]) > 0.1) {
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(a_h[:array_size], a_d[:array_size])

    free(a_h);
    free(a_d);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // test_update_device
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_update_device();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}