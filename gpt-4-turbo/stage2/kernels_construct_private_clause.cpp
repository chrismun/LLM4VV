#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 100

int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int a[size];
    int b[size];
    int c = 5; // Test if this variable remains unchanged

    // Initialize arrays
    for (int i = 0; i < size; i++) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    // Parallel region with private clause
    #pragma acc kernels copyout(b[0:size]) copyin(a[0:size]) private(c)
    for (int i = 0; i < size; i++) {
        c = a[i]; // Modify private variable
        b[i] = c;
    }

    // Verification
    for (int i = 0; i < size; i++) {
        if (b[i] != a[i]) {
            err++;
        }
    }

    // Check if 'c' remains unchanged
    if(c != 5) {
        err++;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    std::cout << "Test " << (failcode ? "FAILED" : "PASSED") << ". Failures: " << failed << std::endl;
    return failcode;
}