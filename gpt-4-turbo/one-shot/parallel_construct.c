#include <stdlib.h>
#include <stdio.h>
#include <math.h> // For fabs()
#include <openacc.h> // Include OpenACC support

#define n 1024
#define PRECISION 0.00001

// Function to test parallel directive
int test_parallel() {
    int err = 0;
    float *a = (float*)malloc(n * sizeof(float));
    float *b = (float*)malloc(n * sizeof(float));
    
    // Initialize the array
    for (int i = 0; i < n; i++) {
        a[i] = i+1;
        b[i] = 0;
    }
    
    // Use OpenACC parallel directive
    #pragma acc parallel copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc loop
        for (int i = 0; i < n; i++) {
            b[i] = a[i] * a[i];
        }
    }
    
    // Verify the results
    for (int i = 0; i < n; i++) {
        if (fabs(b[i] - (a[i] * a[i])) > PRECISION) {
            err++;
        }
    }
    
    free(a);
    free(b);
    
    return err;
}

int main() {
    int failed = test_parallel();
    if (failed == 0) {
        printf("PASS: The parallel construct was correctly implemented.\n");
    } else {
        printf("FAIL: The parallel construct had %d errors.\n", failed);
    }
    
    return failed;
}