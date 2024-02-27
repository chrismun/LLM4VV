#include <iostream>
#include <vector>
#include <cstdlib> // For srand() and rand()
#include <ctime> // For time()

// Assuming a test suite header provides these or define them here for completeness
#ifndef acc_testsuite_h
#define acc_testsuite_h
#define SEED time(NULL)
#define NUM_TEST_CALLS 10
#endif

// Presumed vector length for tests (This should be tailored based on target hardware and compiler capabilities)
constexpr int TEST_VECTOR_LENGTH = 64;

int test1(){
    int err = 0;
    srand(SEED);

    const int dataSize = 10000;
    std::vector<int> testData(dataSize, 1); // Initialize a vector with all elements as 1
    int accumulator = 0;

#pragma acc data copyin(testData[0:dataSize])
    {
#pragma acc parallel vector_length(TEST_VECTOR_LENGTH)
        {
            for(int i = 0; i < dataSize; ++i){
#pragma acc atomic update
                accumulator += testData[i];
            }
        }
    }

    // Validate if accumulator is equal to dataSize
    if(accumulator != dataSize){
        std::cerr << "Test failed: Accumulated value is not as expected. Expected: " << dataSize << ", Got: " << accumulator << std::endl;
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    return failcode;
}