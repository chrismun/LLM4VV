#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define n 10000
#define SEED 42
#define PRECISION 0.00001

typedef float real_t;

#ifndef T1
// T1:kernels,data,data-region,map,V:1.0-2.7
int test_map_data(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t)); // Output array

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0; // Initialize output array
    }

    // Use map to allocate data on the device and transfer inputs and outputs
    #pragma acc data map(to: a[0:n], b[0:n]) map(from: c[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x]; // Simple computation
            }
        }
    }

    // Validate the results
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = test_map_data();
    if (failed != 0){
        failcode = failcode + (1 << 0);
        printf("Map data test failed with %d errors.\n", failed);
    } else {
        printf("Map data test passed.\n");
    }
#endif

    return failcode;
}