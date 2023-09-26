#include "acc_testsuite.h"
#define SIZE 1024
#define TSIZE 8

int test() {

    int err = 0;
    float a[SIZE];
    float b[SIZE];
    float c[SIZE];
    float seq[SIZE];
    
    srand(SEED);
    for(int i=0; i<SIZE; i++) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
        seq[i] = a[i] + b[i];
    }

#pragma acc parallel loop tile(TSIZE)
    for(int i=0; i<SIZE; i++) {
        c[i] = a[i] + b[i];
    }

    for(int i=0; i<SIZE; i++) {
        if(c[i] != seq[i]) {
            err = 1;
            break;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}