#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEED 12345
#define n 100
#define PRECISION 0.00001

// A simple real type definition
typedef float real_t;

// Test for OpenACC firstprivate clause
int test_firstprivate(){
    int err = 0;
    real_t *output = (real_t *)malloc(n * sizeof(real_t));
    real_t initialValue = 5.0; // Initial value to be privatized

    // Initialize output array
    for (int i = 0; i < n; ++i){
        output[i] = 0;
    }

    #pragma acc parallel num_gangs(1) vector_length(1) copyout(output[0:n]) firstprivate(initialValue)
    {
        #pragma acc loop
        for(int i = 0; i < n; ++i){
            // Each thread should have its own private copy of initialValue
            output[i] = initialValue;
        }
    }

    // Validate that the initialValue was correctly used in the computation
    for (int i = 0; i < n; ++i){
        if (fabs(output[i] - initialValue) > PRECISION){
            err += 1;
        }
    }

    free(output);
    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = test_firstprivate();
    if(failed != 0){
        failcode = failcode + 1;
    }
    
    if(failcode == 0){
        printf("PASS: OpenACC firstprivate clause test\n");
    } else {
        printf("FAIL: OpenACC firstprivate clause test\n");
    }

    return failcode;
}