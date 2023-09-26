#include "acc_testsuite.h"

#ifndef T1
/*T1:acc is present,V:2.0-2.7*/
int test1() {
    int error = 0;
    srand(SEED);

    // Create some data
    float* h_data = (float*) malloc(1000 * sizeof(float));

    for(int i=0; i<1000; ++i)
        h_data[i] = rand() / (float)RAND_MAX;

    // Declare variable to hold device data
    float* d_data;

    // Allocate the device memory and copy the host data to the device
    #pragma acc data create(d_data[0:1000])
    {
        memcpy(d_data, h_data, 1000 * sizeof(float));
    }

    // Check if the data is present on the device
    if(!acc_is_present(h_data, 1000 * sizeof(float))){
        error = 1;
    }

    // Free the allocated memory
    free(h_data);

    return error;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if(failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}