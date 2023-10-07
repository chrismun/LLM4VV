#include "openacc_testsuite.h"
#include <math.h>

#define TOLERANCE 0.0001
#define NUM_TRIALS 100

int test_detach_clause()
{
    int error_count = 0;
    float *a = (float*)malloc(NUM_TRIALS * sizeof(float));
    float *b = (float*)malloc(NUM_TRIALS * sizeof(float));

    // Initialize input and set output to zero
    for(int i = 0; i < NUM_TRIALS; ++i){
        a[i] = rand() / (float)(RAND_MAX);
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:NUM_TRIALS]) copyout(b[0:NUM_TRIALS])
    {
        #pragma acc parallel loop detach(b)
        for(int i = 0; i < NUM_TRIALS; ++i){
            b[i] = sqrtf(a[i]);
        }
    }

    // Check results
    for(int i = 0; i < NUM_TRIALS; ++i){
        if(fabs(b[i] - sqrtf(a[i])) > TOLERANCE){
            error_count += 1;
        }
    }

    free(a);
    free(b);

    return error_count;
}

int main()
{
    // Intitalize random seed
    srand(153);

    int total_errors = 0;

    for(int i = 0; i < NUM_TRIALS; ++i) {
        total_errors += test_detach_clause();
    }

    if(total_errors != 0){
        printf("Detected %d errors testing detach clause.\n", total_errors);
    } else {
        printf("Detach clause implementation: PASS\n");
    }

    return total_errors;
}