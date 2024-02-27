#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct reduction clause,V:2.7-3.3
#define SEED 123
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1000;
    int a[size];
    int sum = 0;
    int expected_sum = 0;

    // Initialize array with random values and calculate expected sum
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        expected_sum += a[i];
    }

    // Use OpenACC to perform reduction on the array
    #pragma acc data copyin(a)
    {
      #pragma acc parallel loop reduction(+:sum)
      for (int i = 0; i < size; ++i) {
            sum += a[i];
      }
    }

    // Check if the calculated sum matches the expected sum
    if (sum != expected_sum) {
        ++err;
        printf("Test Failed: Expected sum = %d, Calculated sum = %d\n", expected_sum, sum);
    }else{
        printf("Test Passed: Expected sum = %d, Calculated sum = %d\n", expected_sum, sum);
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