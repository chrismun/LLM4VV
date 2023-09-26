#include "acc_testsuite.h"

// device array that will be declared. Same size as the host array
float *dev_array;

#ifndef TEST1
/*Test1: Declare directive,V:2.0-2.7*/

//Test function
int test1(){
    int err = 0;
    srand(SEED);
    
    int size = 1024;
    float* host_array = new float[size];

    // Populate array with random floats
    for(int i = 0; i < size; i++){
        host_array[i] = rand() / (float)RAND_MAX;
    }

    // Assign values to the device array in parallel
    #pragma acc parallel loop
    for(int i = 0; i < size; i++){
        dev_array[i] = host_array[i];
    }

    // Copy device array to host to check assigned values
    float* check_array = new float[size];
    #pragma acc update self(check_array[0:size])

    // Check assigned values
    for(int i = 0; i< size; i++){
        if (fabs(check_array[i] - host_array[i]) > PRECISION){
            err = 1;
        }
    }

    delete[] host_array;
    delete[] check_array;
    
    return err;
}
#endif

int main(){
    
    #pragma acc declare create(dev_array[1024])

    int failcode = 0;
    int failed;

    #ifndef TEST1
        failed = 0;
        for (int x = 0; x < NUM_TEST_CALLS; ++x){
            failed = failed + test1();
        }
        if (failed != 0){
            failcode = failcode + (1 << 0);
        }
    #endif

    #pragma acc exit data delete(dev_array)
    
    return failcode;
}