#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define SEED 12345
#define n 1000
#define PRECISION 0.00001

typedef float real_t;

int test_copy_clause(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = -1; // different initial value to ensure copy operation is tested
    }

    // Test the copy clause
    #pragma acc data copy(a[0:n]) 
    {
        #pragma acc kernels copy(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}

int main(){
    int failcode = 0;
    int failed = test_copy_clause();
    if (failed != 0){
        failcode = 1;
    }
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}