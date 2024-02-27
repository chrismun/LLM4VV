#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define SEED 12345
#define n 1024
#define PRECISION 1e-5

int test_num_gangs(){
    int err = 0;
    srand(SEED);
    // Assuming 'n' is substantially large to be distributed among gangs
    float *a = (float *)malloc(n * sizeof(float));

    for (int i = 0; i < n; ++i){
        a[i] = 0.0f; // Initialize array
    }

    int expected_gangs = 64; // Hypothetical number of gangs for testing
    
    #pragma acc parallel num_gangs(expected_gangs)
    {
        int gang_id = acc_get_gang_num(0); // Get the gang ID of this execution
        int work_per_gang = n / expected_gangs;
        int start_idx = gang_id * work_per_gang;
        int end_idx = start_idx + work_per_gang;

        #pragma acc loop
        for (int i = start_idx; i < end_idx; ++i){
            a[i] = gang_id; // Assuming each gang can uniquely set its portion of the array
        }
    }
    
    // Validate - although this isn't bulletproof validation for num_gangs, it checks basic distribution
    for (int i = 0; i < n; i += n / expected_gangs){
        if (a[i] == 0) { // If any part remained unset/zero, it indicates an issue
            err += 1;
        }
    }

    free(a);
    return err;
}

int main(){
    int failcode = 0;
    int failed = test_num_gangs();
    
    if (failed != 0){
        printf("Test failed with %d errors.\n", failed);
        failcode = 1;
    } else {
        printf("Test passed.\n");
    }
    
    return failcode;
}