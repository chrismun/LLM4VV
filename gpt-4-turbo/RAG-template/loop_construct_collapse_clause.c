#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:parallel,loop,collapse,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int dim1 = 100, dim2 = 100; // Matrix dimensions
    int a[dim1][dim2];
    int b[dim1][dim2];
    int result[dim1][dim2];

    // Initialize matrices
    for (int i = 0; i < dim1; i++){
        for (int j = 0; j < dim2; j++){
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
            result[i][j] = 0; // setting initial value to 0.
        }
    }

    #pragma acc data copyin(a, b) copy(result)
    {
        #pragma acc parallel loop collapse(2)
        for (int i = 0; i < dim1; i++){
            for (int j = 0; j < dim2; j++){
                result[i][j] = a[i][j] + b[i][j];
            }
        }
    }

    // Verification
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
            if (result[i][j] != a[i][j] + b[i][j]){
                err++;
                break;
            }
        }
    }

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