#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define SEED 12345
#define n 1024
#define PRECISION 0.0001

int test_reduction() {
    int err = 0;
    srand(SEED);
    float *a = (float *)malloc(n * sizeof(float));
    float total_sum = 0.0f, reduced_sum = 0.0f;

    // Initialize array with random values and compute the total sum for verification
    for (int i = 0; i < n; ++i) {
        a[i] = rand() / (float)(RAND_MAX / 10);
        total_sum += a[i];
    }

    // Compute sum using OpenACC reduction
    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel loop reduction(+:reduced_sum)
        for (int i = 0; i < n; ++i) {
            reduced_sum += a[i];
        }
    }

    // Check if the reduced sum matches the directly computed total sum
    if (fabs(reduced_sum - total_sum) > PRECISION) {
        err = 1;
    }

    free(a);
    return err;
}

int main() {
    int failcode = 0;
    int failed = test_reduction();
    
    if (failed) {
        failcode = 1; // Mark failcode as 1 to indicate the test failed
        printf("The test for OpenACC loop construct reduction clause failed.\n");
    } else {
        printf("The test for OpenACC loop construct reduction clause succeeded.\n");
    }

    return failcode;
}