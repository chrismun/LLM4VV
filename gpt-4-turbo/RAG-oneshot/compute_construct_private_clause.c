#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define n 1000
#define NUM_TEST_CALLS 10

int test_private_clause(){
    int err = 0;
    int *result = (int *)malloc(n * sizeof(int));

    // Initializing result array to 0
    for (int x = 0; x < n; ++x){
        result[x] = 0;
    }

    // Parallel region with a private variable 'a'
    #pragma acc parallel num_gangs(n)
    {
        int a = 0; // This variable is private to each gang
        #pragma acc loop private(a)
        for (int x = 0; x < 1; ++x){
            a += 1;
        }
        #pragma acc atomic update
        result[acc_gang_id()] = a;
    }

    // Verification step
    for (int x = 0; x < n; ++x){
        if (result[x] != 1){
            err += 1;
        }
    }

    free(result);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_private_clause();
    }
    if (failed != 0){
        failcode |= 1; // If any of the tests failed, set the failcode's least significant bit
        printf("Private clause tests failed with %d errors.\n", failed);
    } else {
        printf("All private clause tests passed.\n");
    }
    return failcode;
}