#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define n 10000
#define SEED 123
#define PRECISION 1e-5

int test_copyin(){
    int errors = 0;
    srand(SEED);
    float *host_array = (float *)malloc(n * sizeof(float));

    // Initialize array with some values
    for (int i = 0; i < n; ++i){
        host_array[i] = rand() / (float)RAND_MAX;
    }

    // Allocate device memory and copy data from host to device using copyin
    #pragma acc data copyin(host_array[0:n])
    {
        // Parallel region to verify the data is present and correct
        #pragma acc parallel
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                // This operation is just to use the data and check its integrity
                host_array[i] = host_array[i] * 2.0f;
            }
        }
    }

    // Verifying data integrity
    for (int i = 0; i < n; ++i){
        if (fabs(host_array[i] - (rand() / (float)RAND_MAX) * 2.0f) > PRECISION){
            errors += 1;
        }
    }

    free(host_array);
    return errors;
}

int main(){
    int failcode = 0;
    int failed;

    failed = test_copyin();

    if (failed != 0){
        failcode = 1; // Mark as failed
        printf("COPYIN test FAILED with %d errors.\n", failed);
    }else{
        printf("COPYIN test PASSED.\n");
    }

    return failcode;
}