#include "acc_testsuite.h"

#ifndef T1
// T1: loop construct collapse clause, V: 2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Declare arrays
    int *a, *b, *c;
    int i, j;

    int size = SIZE * SIZE;

    // Allocate memory
    a = (int *)malloc(size * sizeof(int));
    b = (int *)malloc(size * sizeof(int));
    c = (int *)malloc(size * sizeof(int));

    // Initialize arrays
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            a[i * SIZE + j] = (int)rand() / (int)(RAND_MAX / 100);
            b[i * SIZE + j] = (int)rand() / (int)(RAND_MAX / 100);
        }
    }

    // Compute sum of corresponding elements of a and b, and store in c
    #pragma acc parallel loop collapse(2) present(a,b,c)
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            c[i * SIZE + j] = a[i * SIZE + j] + b[i * SIZE + j];
        }
    }

    // Verify results
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            if (c[i * SIZE + j] != a[i * SIZE + j] + b[i * SIZE + j]){
                err = 1;
            }
        }
    }

    // Free memory
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
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}