#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024
#define PRECISION 1e-5

// Helper function to check arrays for equality
int check_array(float *a, float *b, int n) {
    for (int i = 0; i < n; i++) {
        if (fabs(a[i] - b[i]) > PRECISION) return 1;
    }
    return 0;
}

// Test for loop variable predetermined to be private
int test_loop_variable_private() {
    int errors = 0;
    float a[NUM_ELEMENTS], b[NUM_ELEMENTS];

    #pragma acc parallel loop
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        a[i] = i * 1.0f;
    }

    #pragma acc parallel loop
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        b[i] = a[i];
    }

    errors = check_array(a, b, NUM_ELEMENTS);
    return errors;
}

// Test for variable scope and predetermined attributes
int test_variable_scope() {
    int errors = 0;
    float a[NUM_ELEMENTS], c[NUM_ELEMENTS];
    float b = 2.0f;

    // Demonstrating scope-wise predetermined variable attributes
    #pragma acc parallel
    {
        float d = 3.0f; // Should be private to each worker
        #pragma acc loop
        for (int i = 0; i < NUM_ELEMENTS; i++) {
            a[i] = b * d; // Each iteration has its own 'd'
        }
    }

    // Single worker mode, 'e' should be shared across the loop
    #pragma acc parallel
    {
        float e = 4.0f; // Given the context, 'e' is private to gang but shared across workers
        #pragma acc loop
        for (int i = 0; i < NUM_ELEMENTS; i++) {
            c[i] = a[i] + e;
        }
    }

    // 'a' array should have been modified to b*d for each element.
    // 'c' array should be a[i] + e for each element.
    // Here 'e' and 'b*d' are constants, hence we expect uniform modification.

    float expected_a_val = b * 3.0f; // b*d
    float expected_c_val = expected_a_val + 4.0f; // a[i] + e
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        if (fabs(a[i] - expected_a_val) > PRECISION) errors += 1;
        if (fabs(c[i] - expected_c_val) > PRECISION) errors += 1;
    }

    return errors;
}

int main() {
    int failcode = 0;

    if (test_loop_variable_private() != 0) {
        printf("Test for loop variable private failed\n");
        failcode |= 1;
    } else {
        printf("Test for loop variable private passed\n");
    }

    if (test_variable_scope() != 0) {
        printf("Test for variable scope and attributes failed\n");
        failcode |= 2;
    } else {
        printf("Test for variable scope and attributes passed\n");
    }

    return failcode;
}