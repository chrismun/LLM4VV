#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
#define SEED 42
#define NUM_TEST_CALLS 10
//T1:{feature},V:2.7-3.3

int array_length = 1024;
float array[1024]  __attribute__((openacc device_resident));

void initialize_array() {
    #pragma acc parallel loop
    for (int i = 0; i < array_length; ++i) {
        array[i] = i * 2.0f;
    }
}

int test1(){
    int err = 0;
    srand(SEED);

    initialize_array();

    float sum = 0.0f;
    #pragma acc parallel loop reduction(+:sum)
    for(int i = 0; i < array_length; ++i) {
        sum += array[i];
    }

    float expected_sum = 0.0f;
    for (int i = 0; i < array_length; ++i) {
        expected_sum += i * 2.0f;
    }

    if (abs(sum - expected_sum) > 0.01f) {
        printf("Test failed: Sum was %f but expected %f\n", sum, expected_sum);
        err = 1;
    }

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
    if(failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }
    return failcode;
}