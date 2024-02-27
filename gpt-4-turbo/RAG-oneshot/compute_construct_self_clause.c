#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SEED 12345
#define n 100000
#define PRECISION 0.001

typedef float real_t;

int test_self_clause(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    bool executeOnLocalDevice = true; // Simulating condition for self clause

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel loop copyout(b[0:n]) if(!executeOnLocalDevice) self(executeOnLocalDevice)
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
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
    int failed;

    failed = test_self_clause();
    
    if (failed != 0){
        failcode = 1;
        printf("Test FAILED with %d errors.\n", failed);
    } else {
        printf("Test PASSED.\n");
    }

    return failcode;
}