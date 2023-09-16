#include "acc_testsuite.h"

int test_func(){
    int err = 0;
    float* testArray_host;
    float* testArray_device;

    testArray_host = (float*)malloc(100*sizeof(float));
    testArray_device = (float*)malloc(100*sizeof(float));

    // Initialize host array
    for(int i = 0; i < 100; i++) {
        testArray_host[i] = rand() % 100;
    }

    #pragma acc data copyout(testArray_device[0:100])
    {
        #pragma acc kernels async 
        {
            for(int i = 0; i < 100; i++) {
                testArray_device[i] = testArray_host[i] * 2.0; 
            }   
        }
        #pragma acc wait 
    }

    // Verification
    for(int i = 0; i < 100; i++) {
        if(fabs(testArray_device[i] - testArray_host[i]*2.0) > 1e-5) {
            err = 1;
        }
    }

    free(testArray_host);
    free(testArray_device);
    return err;
}

int main(){
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_func();
    }
    return failed;
}