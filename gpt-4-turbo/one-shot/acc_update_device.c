#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define n 1024
#define SEED 1234
#define PRECISION 1e-5

typedef float real_t;

int test_update_device(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t)); // To verify update
    real_t *c = (real_t *)malloc(n * sizeof(real_t)); // Modified host array

    // Initialize host array 'a' with random values and copy 'c' as a backup
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = a[x]; // Copy 'a' to 'c'
    }

    // Copy data to device
    #pragma acc data copy(a[0:n])
    {
        // Modify host array 'a'
        for (int x = 0; x < n; ++x){
            a[x] += 1; // Simple modification for testing
        }
        
        // Update device with modified host array 'a'
        #pragma acc update device(a[0:n])
        
        // Copy data back to host array 'b' for verification
        #pragma acc parallel loop copyout(b[0:n])
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }
    }

    // Verify if 'b' (device updated array) matches 'a' (modified host array)
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}

int main(){
    int failcode = 0;
    int failed = test_update_device();

    if (failed != 0){
        failcode = 1;
        printf("Test FAILED with %d errors.\n", failed);
    }else{
        printf("Test PASSED.\n");
    }

    return failcode;
}