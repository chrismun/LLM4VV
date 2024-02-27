#include <openacc.h>
#include <iostream>
#include <cstdlib> // For srand and rand
#include <ctime> // For the SEED based on time

// Assuming acc_testsuite.h defines these, since it was included in the given template
// If not, you should define SEED, NUM_TEST_CALLS appropriately
#define SEED (unsigned)time(NULL)
#define NUM_TEST_CALLS 100

#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Set a random async queue number (assuming the implementation supports at least 10 queues)
    int async_queue = rand() % 10 + 1; // 1 - 10
    acc_set_default_async(async_queue);

    // Now, use a simple OpenACC parallel region without specifying the async queue explicitly
    #pragma acc parallel num_gangs(1) async
    {
        // If implementation is correct, this will run on 'async_queue'
        // Add dummy operation to avoid empty region
        int temp = 0;
        temp += 1;
    }

    // Ensure everything in 'async_queue' has finished
    acc_wait(async_queue);

    // Resetting to default queue
    acc_set_default_async(acc_async_sync);

    // Test complete; 'err' remains 0 upon success
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    if (failcode == 0) {
        std::cout << "Test Passed: acc_set_default_async seems to work correctly." << std::endl;
    } else {
        std::cout << "Test Failed: acc_set_default_async does not work as expected." << std::endl;
    }
    return failcode;
}