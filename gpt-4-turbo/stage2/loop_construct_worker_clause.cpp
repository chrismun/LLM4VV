#include <iostream>
#include <cstdlib>
#include <cstring> // For memset

#define SEED 123
#define NUM_TEST_CALLS 10

// Utility to set up the testing environment
struct acc_testsuite_t {
    static const int n = 1000; // Number of iterations/size of array used for the test
    int *array;

    acc_testsuite_t() : array(new int[n]) {
        std::srand(SEED);
        std::memset(array, 0, sizeof(int) * n);
    }

    ~acc_testsuite_t() {
        delete[] array;
    }
} acc_testsuite;

#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize array to 0
    int *test_array = acc_testsuite.array;
    int n = acc_testsuite.n;
    std::memset(test_array, 0, sizeof(int) * n);

    #pragma acc parallel num_workers(4)
    {
        #pragma acc loop worker
        for (int i = 0; i < n; ++i) {
            test_array[i] = 1;
        }
    }

    // Check that each array element was set to 1, indicating correct parallel execution
    for (int i = 0; i < n; ++i) {
        if (test_array[i] != 1) {
            ++err;
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