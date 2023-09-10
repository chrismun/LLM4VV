#include "acc_testsuite.h"
#ifndef T1
/*T1:loop construct tile clause,V:2.0-2.7*/
int test1(){
    int rows = 16, cols = 16;
    int err = 0;
    int a[rows][cols], b[rows][cols];

    // Initialize the array with some values.
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            a[i][j] = i * cols + j;
            b[i][j] = 0;
        }
    }

    // Perform a parallel computation on the array using tile clause.
    #pragma acc parallel loop tile(4,4)
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            b[i][j] = a[i][j] + 1;
        }
    }

    // Check if computations were performed correctly.
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if (b[i][j] != a[i][j] + 1) {
                err = 1;
            }
        }
    }

    return err;
}
#endif

int main(){
    int failed;
    int failcode = 0;
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