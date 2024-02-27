#include <iostream>
#include <stdlib.h>

// Assuming a minimalistic "acc_testsuite.h" for illustration purposes
#ifndef ACC_TESTSUITE_H
#define ACC_TESTSUITE_H

#define SEED 12345
#define NUM_TEST_CALLS 10

#endif // ACC_TESTSUITE_H

#ifndef T1
//T1:loop construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int dataSize = 1000;  // Size of the data array
    int sum = 0;  // The variable to be reduced
    
    // Generate test data
    int* data = new int[dataSize];
    for(int i = 0; i < dataSize; ++i){
        data[i] = rand() % 10;  // Assign random values between 0 and 9
        sum += data[i];  // Expected sum
    }
    
    int result = 0;  // Result of reduction

    // OpenACC parallel region with loop and reduction directive
    #pragma acc parallel copy(result)
    {
        #pragma acc loop reduction(+:result)
        for(int i = 0; i < dataSize; ++i){
            result += data[i];
        }
    }

    // Error check
    if(result != sum) {
        std::cerr << "Error: result(" << result << ") != expected sum(" << sum << ")" << std::endl;
        err = 1;
    }

    delete[] data;
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
    return failcode;
}