#include "acc_testsuite.h"
#include <openacc.h>

#define N 1024
#define VECTOR_LENGTH 32

#ifndef T1
/*T1:serial construct vector_length clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize host array
    float* array_host = new float[N];
    for(int i=0;i<N;i++){
        array_host[i] = rand() % 100;
    }

    // Compute on device
    float* array_device = new float[N];
    #pragma acc data copyin(array_host[0:N]) copy(array_device[0:N])
    {
        #pragma acc serial vector_length(VECTOR_LENGTH)
        for(int i=0; i<N; i++){
           array_device[i] = array_host[i];
        }
    }

    // Compare host and device result
    for(int i=0;i<N;i++){
        if(array_host[i] != array_device[i]){
            err = 1;
            break;
        }
    }

    delete[] array_host;
    delete[] array_device;

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