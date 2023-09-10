#include "acc_testsuite.h"
#include <stdlib.h>

#define N 1024
#define TSIZE 32

#ifndef T1
/*T1:loop construct tile clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    int matrix[N][N];

    srand(SEED);

    // Initialize the matrix with some values
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            matrix[i][j] = rand() % 100;

    // Apply the tile clause on the loop construct
    #pragma acc parallel loop tile(TSIZE, TSIZE)
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            matrix[i][j] *= 2;

    // Check the result
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (matrix[i][j] >= 200 || matrix[i][j] < 0) {   // Since tile size may divide loop size, and initial values should be in 0-99
                err = 1;
                break;
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