#include "openacc.h"
#include <stdio.h>
#include <stdlib.h>

// Test routine
#pragma acc routine
void test_routine(double *val) {
   *val = *val * 2.0;
}

int main()
{
    double *h_val = (double*) malloc(sizeof(double));
    *h_val = 5.0; // Initialize value

    double *d_val;
    d_val = acc_copyin(h_val, sizeof(double)); // Move value to device

    #pragma acc parallel present(d_val)
    {
        test_routine(d_val); // Call routine in parallel region
    }

    acc_copyout(h_val, sizeof(double)); // Move value back to host

    // Check result
    if (*h_val != 10.0) {
        printf("Error: result is %f, expected 10.0\n", *h_val);
        return 1;
    }
    
    printf("Test passed!\n");
    return 0;
}