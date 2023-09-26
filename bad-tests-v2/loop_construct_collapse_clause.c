#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int i, j, k;
    int arr[N][M];

    // Initialize array
    for (i = 0; i < N; i++){
        for (j = 0; j < M; j++){
            arr[i][j] = i + j;
        }
    }

    // Parallelize with collapse clause
    #pragma acc parallel loop collapse(2)
    for (i = 0; i < N; i++){
        for (j = 0; j < M; j++){
            // Check if each element is correctly calculated
            if (arr[i][j] != i + j){
                err = 1;
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