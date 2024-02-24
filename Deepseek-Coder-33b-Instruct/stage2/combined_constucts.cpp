#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:combined constucts,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a vector of random numbers
    std::vector<int> numbers(10000);
    for(int i = 0; i < numbers.size(); i++){
        numbers[i] = rand() % 100;
    }

    // Use the combined constructs to sum the numbers in parallel
    int sum = 0;
    #pragma acc parallel loop reduction(+:sum)
    for(int i = 0; i < numbers.size(); i++){
        sum += numbers[i];
    }

    // Check the result
    int expected_sum = 0;
    for(int i = 0; i < numbers.size(); i++){
        expected_sum += numbers[i];
    }

    if(sum != expected_sum){
        err = 1;
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