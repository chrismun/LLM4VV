#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a 2D array with random values
    int array[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            array[i][j] = rand() % 100;
        }
    }

    // Create a 2D array with the same dimensions as the input array
    int result[10][10];

    // Use the tile clause to divide the input array into 2D tiles
    #pragma acc parallel loop tile(10, 10)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            result[i][j] = array[i][j];
        }
    }

    // Check that the result array is the same as the input array
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (result[i][j] != array[i][j]) {
                err = 1;
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