#include <stdlib.h>
#include <time.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:serial construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 100;
    int data[size];
    long long int sum = 0;
    long long int expected_sum = 0;

    // Initialize the array with random numbers
    for(int i = 0; i < size; i++){
        data[i] = rand() % 100;
        expected_sum += data[i];
    }

    // Use the serial construct to sum the array
    #pragma acc serial
    {
        for(int i = 0; i < size; i++){
            sum += data[i];
        }
    }

    // Check if the sum is correct
    if(sum != expected_sum){
        err++;
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