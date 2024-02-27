#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define SEED 12345
#define n 100
#define PRECISION 1e-7

typedef float real_t; // Adjust as needed for precision tests

// Function to validate the OpenACC "if clause"
int test_if_clause(){
    int err = 0;
    srand(SEED);
    real_t *host_a = (real_t *)malloc(n * sizeof(real_t));
    real_t *host_b = (real_t *)malloc(n * sizeof(real_t));
    real_t *check_b = (real_t *)malloc(n * sizeof(real_t));

    for (int i = 0; i < n; ++i){
        host_a[i] = rand() / (real_t)(RAND_MAX / 10);
        host_b[i] = 0;
        check_b[i] = host_a[i];  // Copy the same values for verification
    }

    // Assume the offloading condition is related to a dynamic factor like 'n'
    // Offload if n > 50 otherwise execute on the host
    int offload_condition = n > 50;

    #pragma acc kernels if(offload_condition) copyin(host_a[0:n]) copyout(host_b[0:n])
    for (int i = 0; i < n; ++i){
        host_b[i] = host_a[i];
    }

    // Perform the operation on the host for verification
    for (int i = 0; i < n; ++i){
        check_b[i] = host_a[i];
    }

    // Compare the results
    for (int i = 0; i < n; ++i){
        if (fabs(host_b[i] - check_b[i]) > PRECISION){
            err++;
        }
    }

    free(host_a);
    free(host_b);
    free(check_b);
    return err;
}

int main(){
    int failcode = 0;
    int failed = test_if_clause();
    if (failed != 0){
        failcode |= 1; // marking test as failed
    }
    if(failcode != 0){
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }
    return failcode;
}