#include <iostream>
#include <vector>
#include <stdlib.h> // For srand(), rand()
#include <openacc.h> // Required for OpenACC directives

#ifndef T1
// T1: loop construct device_type clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL)); // Initialize random seed.

    const int size = 1024;
    std::vector<float> a(size, 1.0f); // Initialize vector with 1.0

    // Attempt to perform a computation on an unlikely device type to force fallback.
    #pragma acc parallel loop device_type(host)
    for(int i = 0; i < size; ++i){
        a[i] = a[i] + i;
    }

    // Verify the computation happened as expected, indicating it ran on the CPU.
    for(int i = 0; i < size; ++i){
        if(a[i] != 1.0f + i){
            err++;
            break;
        }
    }

    return err; // Returns 0 if no errors, non-zero otherwise
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    const int NUM_TEST_CALLS = 1; // Assuming we want to call the test once for demonstration.
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}