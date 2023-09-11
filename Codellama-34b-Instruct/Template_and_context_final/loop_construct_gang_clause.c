c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc/acc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int m = 100;
    int k = 100;
    int dim = 1;
    int num_gangs = 10;
    int gang_size = 10;

    // Allocate memory for the arrays
    float *a = (float *)malloc(n * m * k * sizeof(float));
    float *b = (float *)malloc(n * m * k * sizeof(float));
    float *c = (float *)malloc(n * m * k * sizeof(float));

    // Initialize the arrays
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < k; k++) {
                a[i * m * k + j * k + k] = (float)rand() / RAND_MAX;
                b[i * m * k + j * k + k] = (float)rand() / RAND_MAX;
                c[i * m * k + j * k + k] = 0.0f;
            }
        }
    }

    // Set the gang size and number of gangs
    acc_set_gang_size(gang_size);
    acc_set_num_gangs(num_gangs);

    // Create a parallel region with the gang clause
    #pragma acc parallel loop gang(dim:1)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < k; k++) {
                c[i * m * k + j * k + k] = a[i * m * k + j * k + k] + b[i * m * k + j * k + k];
            }
        }
    }

    // Check the results
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < k; k++) {
                if (c[i * m * k + j * k + k] != a[i * m * k + j * k + k] + b[i * m * k + j * k + k]) {
                    err = 1;
                    break;
                }
            }
        }
    }

    // Free the memory
    free(a);
    free(b);
    free(c);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}