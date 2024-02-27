#include "acc_testsuite.h"
#ifndef T1
//T1:{directive},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int arr[size];
    int sub_size = 256;
    int lower = 100; // Just an example start, ensuring we have a subarray within bounds.
    long sum = 0, correct_sum = 0;
    
    // Initialize array with random data
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100;
        if (i >= lower && i < lower + sub_size) {
            correct_sum += arr[i]; // Pre-calculate the correct sum for verification
        }
    }

    // Using OpenACC to cache the subarray and perform repeated sum
    #pragma acc data copy(arr)
    {
        #pragma acc parallel loop reduction(+:sum)
        for (int repeat = 0; repeat < 100; ++repeat) {
            #pragma acc loop
            #pragma acc cache(arr[lower:sub_size])
            for (int i = lower; i < lower + sub_size; ++i) {
                sum += arr[i];
            }
        }
    }
    
    // Verify if the computed sum matches the expected sum
    if (sum != correct_sum * 100) { // 100 repeats
        err = 1; // Incorrect sum indicates potential issue with cache directive handling
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