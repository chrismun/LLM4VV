#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
// T1:predetermined_data_attributes, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Test for private loop variable
    int loop_sum = 0;
    #pragma acc parallel loop reduction(+:loop_sum)
    for(int i = 0; i < 100; ++i){
        loop_sum += 1;
    }
    // If loop_sum is 100, then the loop variable 'i' was correctly considered private.
    if(loop_sum != 100){
        err += 1;
    }

    // Test for variables in a block executed in vector-partitioned mode
    int block_var = 0;
    #pragma acc parallel vector_length(4)
    {
        int local_var = 1; // Should be private to each vector lane
        #pragma acc loop vector reduction(+:block_var)
        for(int j = 0; j < 4; ++j){
            block_var += local_var;
        }
    }
    // If block_var is 4, then the local_var inside the block was correctly considered private to each vector lane.
    if(block_var != 4){
        err += 1;
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
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}