#include <iostream>
#include <vector>
#include <openacc.h>
#include <stdlib.h>     // For srand(), rand()

// Assuming SEED and NUM_TEST_CALLS are defined for the context of these tests.
#define SEED 12345
#define NUM_TEST_CALLS 5

//T1:serial construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1000;
    std::vector<int> vec(size, 1); // Initialize a vector with 1000 elements set to 1

    #pragma acc serial copy(vec[0:size]) async
    for (int i = 0; i < size; ++i) {
        // Simulate some work
        vec[i] += i;
    }

    // Use acc_wait to ensure the async operation is complete before verifying
    acc_wait(0);

    for(int i = 0; i < size; ++i) {
        if (vec[i] != i + 1) {
            err = 1; // error if the operation inside async didn't complete as expected
            break;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}