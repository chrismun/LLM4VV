#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a parallel region with 4 threads
    #pragma acc parallel num_threads(4)
    {
        // Create a loop with 10 iterations
        for (int i = 0; i < 10; i++) {
            // Create a random number between 0 and 10
            int random_number = rand() % 10;

            // Print the random number to the console
            printf("Random number: %d\n", random_number);
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