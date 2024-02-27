#include <stdlib.h>
#include <stdio.h>
#include <math.h> // For fabs()

#define SEED 12345
#define n 100
#define PRECISION 1e-5

typedef float real_t; // Define real_t as a placeholder for the real number type, float here for simplicity.

#ifndef T_SERIAL
// T_SERIAL:serial,V:1.0-3.1
int test_serial(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0; // Initialize to 0.
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc serial 
        {
            // We use a single-thread context (serial) to perform operations.
            for (int x = 0; x < n; ++x){
                b[x] = a[x] + 1; // Increment each element by 1 to test.
            }
        }
    }

    // Verification
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (a[x] + 1)) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T_SERIAL
    failed = 0;
    for (int x = 0; x < 1; ++x){ // Assuming a single test call suffices for clarity and simplicity.
        failed = failed + test_serial();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("Serial construct test passed.\n");
    } else {
        printf("Serial construct test failed.\n");
    }
    return failcode;
}