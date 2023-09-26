#include "acc_testsuite.h"

float array[100];
float test_array[100];

// Kernel function for adding 10 to each element
#pragma acc routine
void add_ten(float *arr)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if(idx < 100)
    {
        arr[idx] += 10.0;
    }
}

#ifndef T1
// Test to check if array is copied correctly using acc copyin

int test1() {
    int err = 0;
    srand(10);

    // Fill array with elements
    for(int i=0; i<100; i++) 
    {
        array[i] = (float) rand() / (float) RAND_MAX;
        test_array[i] = array[i];
    }

    // Copy array to device memory
    #pragma acc data copyin(array[0:100])
    {
        add_ten(array);
    }

    // Add ten to elements on CPU as well for comparison
    for(int i=0; i<100; i++)
    {
        test_array[i] += 10.0;
    }

    // Check if both arrays are equivalent
    for(int i=0; i<100; i++)
    {
        if(abs(array[i] - test_array[i]) > 1e-5) {
            err = 1;
            break;
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