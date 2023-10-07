#include "acc_testsuite.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#ifndef T1
/*T1:wait directive,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int num_threads = 4;
    std::vector<std::thread> threads(num_threads);

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread([i]() {
            #pragma acc parallel num_threads(4)
            {
                #pragma acc loop
                for (int j = 0; j < 10000; ++j) {
                    // Some computation
                }
            }
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    #pragma acc wait

    for (auto& th : threads) {
        th.join();
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