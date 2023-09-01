#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

#pragma acc routine
int test1(){
    int err = 0;
    srand(SEED);

    // Generate a random number between 0 and 100
    int random_number = rand() % 100;

    // If the random number is less than 50, shutdown the device
    if (random_number < 50){
        #pragma acc shutdown
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Call the test function 100 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }

    // Check if any of the calls failed
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}